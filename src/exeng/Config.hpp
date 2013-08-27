/**
 * @file Config.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_CONFIG_HPP__
#define __EXENG_CONFIG_HPP__

#include <exeng/DetectEnv.hpp>

#ifndef NDEBUG
#  ifndef EXENG_DEBUG
#    define EXENG_DEBUG
#  endif
#endif

#ifdef EXENG_WINDOWS
#  define EXENG_CALLCONV __stdcall
#else
#  define EXENG_CALLCONV 
#endif

#ifdef EXENG_BUILD
#  ifdef EXENG_DYNAMIC
#    if defined(EXENG_MSVC) || defined(EXENG_BCC) || defined(EXENG_ICC)
#      define EXENGAPI __declspec(dllexport)
#    elif defined(EXENG_GCC)
#      define EXENGAPI 
#    else
#      define EXENGAPI
#    endif
#  else
#    define EXENGAPI
#  endif
#else
#  ifdef EXENG_DYNAMIC
#    if defined(EXENG_MSVC) || defined(EXENG_BCC) || defined(EXENG_ICC)
#      define EXENGAPI __declspec(dllimport)
#    elif defined(EXENG_GCC)
#      define EXENGAPI 
#    else
#      define EXENGAPI
#    endif
#  else
#    define EXENGAPI
#  endif
#endif

#endif	//__EXENG_CONFIG_HPP__
