#pragma once

#include <android/log.h>

#include "Memory.hpp"
#include "Dobby/dobby.h"

map_t libil2cpp;

void Main() {
    do {
        sleep(1);
        libil2cpp = mapByName("libil2cpp.so");
    } while (!libil2cpp.isValid());


}