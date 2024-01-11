#pragma once

#include <vector>
#include <unistd.h>
#include <sys/mman.h>

#define _PAGE_SIZE (sysconf(_SC_PAGE_SIZE))

#define _PAGE_START(address) (uintptr_t(address) & ~(_PAGE_SIZE - 1))
#define _PAGE_END2(address, size) (_PAGE_START(uintptr_t(address) + size - 1))
#define _PAGE_LEN2(address, size) (_PAGE_END2(address, size) - _PAGE_START(address) + _PAGE_SIZE)

class map_t {
public:
    size_t length;
    bool readable;
    bool writeable;
    bool executable;
    std::string pathname;
    unsigned long long endAddress;
    unsigned long long startAddress;

    map_t() : startAddress(0), endAddress(0), length(0), readable(false), writeable(false), executable(false) {}

    inline bool isValid() const {
        return (startAddress && endAddress && length);
    }

    inline bool isUnknown() const {
        return pathname.empty();
    }

    inline bool contains(uintptr_t address) const {
        return address >= startAddress && address < endAddress;
    }
};

std::vector<map_t> allMaps() {
    std::vector<map_t> allMaps;
    char line[512] = {0};

    FILE *file = fopen("/proc/self/maps", "r");
    if (!file) {
        return allMaps;
    }

    while (fgets(line, sizeof(line), file)) {
        map_t map;

        char perms[5];
        char pathname[256];

        sscanf(line,
               "%llx-%llx %s %*llx %*s %*lu %s",
               &map.startAddress,
               &map.endAddress,
               perms,
               pathname);

        map.pathname = pathname;
        map.readable = perms[0] == 'r';
        map.writeable = perms[1] == 'w';
        map.executable = perms[2] == 'x';
        map.length = map.endAddress - map.startAddress;

        allMaps.push_back(map);
    }

    fclose(file);

    return allMaps;
}

map_t mapByName(const std::string &name) {
    for (auto map : allMaps()) {
        if (map.isValid() && !map.isUnknown() && strstr(map.pathname.c_str(), name.c_str())) {
            return map;
        }
    }

    return {};
}

map_t mapByAddress(uintptr_t address) {
    for (auto map : allMaps()) {
        if (map.isValid() && map.contains(address)) {
            return map;
        }
    }

    return {};
}

void writeMemory(uintptr_t address, const void *buffer, size_t size) {
    map_t map = mapByAddress(address);
    if (!map.isValid())
        return;

    auto protect = [&](int protection) -> void {
        uintptr_t pageStart = _PAGE_START(address);
        uintptr_t pageLen = _PAGE_LEN2(address, size);
        mprotect((void *) pageStart, pageLen, PROT_READ | PROT_WRITE | PROT_EXEC);
    };

    protect(PROT_READ | PROT_WRITE | PROT_EXEC);

    memcpy((void *) address, buffer, size);

    int protection = 0;
    if (map.readable) protection |= PROT_READ;
    if (map.writeable) protection |= PROT_WRITE;
    if (map.executable) protection |= PROT_EXEC;

    protect(protection);
}