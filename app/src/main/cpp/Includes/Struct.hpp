#include <vector>
#include <dlfcn.h>

struct monoString {
    void *klass;
    void *monitor;
    int length;
    char chars[0];

    static monoString *create(const char *text) {
        void *handle = dlopen("libil2cpp.so", RTLD_LAZY);

        if (handle) {
            void *symbol = dlsym(handle, "il2cpp_string_new");
            if (symbol) {
                return ((monoString *(*)(const char *)) symbol) (text);
            }
        }

        return nullptr;
    }
};