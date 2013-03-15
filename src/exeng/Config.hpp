
#ifndef __EXENG_CONFIG_HPP__
#define __EXENG_CONFIG_HPP__

#include "DetectEnv.hpp"

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
