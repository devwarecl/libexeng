/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SYSTEM_LIBRARYPRIVATE_HPP__
#define __EXENG_SYSTEM_LIBRARYPRIVATE_HPP__

#include <exeng/system/Library.hpp>

namespace exeng { namespace system {
    struct Library::Private {
        std::string name;
        void* handle = nullptr;

        FunctionPtr getFunctionPtr(const std::string &name);
        void load(const std::string &name);
        void unload();
    };
}}

#endif	//__EXENG_SYSTEM_LIBRARYPRIVATE_HPP__
