#include <android/log.h>

#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "Platinmods", ##__VA_ARGS__)

class map_t {
public:
    size_t length;
    unsigned long long startAddress;
    unsigned long long endAddress;

    map_t() : startAddress(-1), endAddress(-1), length(-1) {}

    inline bool isValid() const { return (startAddress && endAddress && length); }
};

map_t getMap(const char *name) {
    map_t result {};

    FILE *file = fopen("/proc/self/maps", "r");
    if (file) {
        char line[512];

        while (fgets(line, sizeof(line), file)) {
            if (!strstr(line, name))
                continue;

            map_t map {};
            sscanf(line, "%llx-%llx",
                   &map.startAddress, &map.endAddress);

            map.length = map.endAddress - map.startAddress;

            if (map.isValid())
                result = map;
        }

        fclose(file);
    }

    return result;
}