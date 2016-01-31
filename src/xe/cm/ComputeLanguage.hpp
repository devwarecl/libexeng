
#pragma once

#ifndef __xe_cm_computelanguage_hpp__
#define __xe_cm_computelanguage_hpp__

#include <xe/Enum.hpp>

namespace xe { namespace cm {
    struct ComputeLanguage : public Enum {
        enum Enum {
            Unknown,
            OpenCL,
            DirectCompute
        };
    };
}}

#endif // COMPUTELANGUAGE_HPP
