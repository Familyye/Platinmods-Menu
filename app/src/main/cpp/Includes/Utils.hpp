#include <android/log.h>

#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "Platinmods", ##__VA_ARGS__)

struct map_t {
    size_t size;
    std::string path;
    uintptr_t start, end;

    bool valid() {
        return (start && end && size);
    }

    map_t() : start(0), end(0), size(0) {}
};

map_t getMap(const char *moduleName) {
    FILE *file = fopen("/proc/self/maps", "r");
    if (file) {
        char line[512];
        while (fgets(line, sizeof(line), file)) {
            map_t memory;
            char name[256];

            sscanf(line,
                   "%x-%x %*s %*llx %*s %*lu %s",
                   &memory.start,
                   &memory.end,
                   name);

            if (!strstr(name, moduleName))
                continue;

            memory.path = name;
            memory.size = memory.end - memory.start;

            if (memory.valid())
                return memory;
        }

        fclose(file);
    }

    return {};
}