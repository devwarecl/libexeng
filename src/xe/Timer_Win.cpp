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

#if defined(EXENG_WINDOWS)
#include <Windows.h>

namespace xe {
    // thin wrapper around GetTickCount
    uint32_t Timer::getTime() {
        return static_cast<uint32_t>(::GetTickCount());
    }
}

#endif  // EXENG_WINDOWS
