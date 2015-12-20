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

#include <xe/DetectEnv.hpp>

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

#ifdef EXENG_WINDOWS
#  define EXENG_EXPORT __declspec(dllexport)
#  define EXENG_IMPORT __declspec(dllimport)
#else 
#  define EXENG_EXPORT
#  define EXENG_IMPORT
#endif

// define EXENGAPI
#ifdef EXENG_BUILD
#  ifdef EXENG_WINDOWS
#    define EXENGAPI EXENG_EXPORT
#  else
#    define EXENGAPI
#  endif
#else 
#  ifdef EXENG_WINDOWS
#    define EXENGAPI EXENG_IMPORT
#  else
#    define EXENGAPI
#  endif
#endif

#endif	//__EXENG_CONFIG_HPP__
