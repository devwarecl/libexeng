
#pragma once

#ifndef __xe_gfx_buffertype__
#define __xe_gfx_buffertype__

#include <xe/Enum.hpp>

namespace xe { namespace gfx {
    struct BufferType : public Enum {
        enum Enum {
            Vertex,
            Index
        };
    };
}}

#endif 
