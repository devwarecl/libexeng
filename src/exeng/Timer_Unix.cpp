/**
 * @file Timer.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include "Timer.hpp"

#if defined(EXENG_UNIX)
#include <time.h>

namespace exeng {
    uint32_t Timer::getTime() {
        timespec ts;
        
        if (::clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
            return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
        } else {
            return 0;
        }
    }
}

#endif  // EXENG_WINDOWS
