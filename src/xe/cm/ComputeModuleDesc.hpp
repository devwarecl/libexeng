
#pragma once

#ifndef __xe_cm_computemoduledesc_hpp__
#define __xe_cm_computemoduledesc_hpp__

#include <xe/Config.hpp>
#include <xe/cm/ComputeLanguage.hpp>

namespace xe { namespace cm {
    
    struct EXENGAPI ComputeModuleDesc {
        ComputeLanguage::Enum language;
        
        ComputeModuleDesc();
        
        bool operator< (const ComputeModuleDesc &other) const;
        bool operator== (const ComputeModuleDesc &other) const;
        bool operator!= (const ComputeModuleDesc &other) const;
    };
}}

#endif
