
#pragma once

#ifndef __xe_cm_contextoptions_hpp__
#define __xe_cm_contextoptions_hpp__

#include <memory>
#include <xe/Config.hpp>

namespace xe { namespace cm {

    struct EXENGAPI ContextOptions {
        bool enableGraphics = false;
        
        ContextOptions();
    };
}}

#endif 
