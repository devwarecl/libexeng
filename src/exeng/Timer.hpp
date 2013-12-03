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

#ifndef __EXENG_TIMER_HPP__
#define __EXENG_TIMER_HPP__

#include <exeng/Config.hpp>
#include <cstdint>

namespace exeng {
    class EXENGAPI Timer {
    public:
        /**
         * @brief Get the current time in milliseconds 
         */
        static uint32_t getTime();
    };

}

#endif  //__EXENG_TIMER_HPP__
