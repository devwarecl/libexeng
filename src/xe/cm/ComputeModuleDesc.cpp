
#include "ComputeModuleDesc.hpp"

namespace xe { namespace cm {
    ComputeModuleDesc::ComputeModuleDesc() {
        this->language = ComputeLanguage::Unknown;
    }

    bool ComputeModuleDesc::operator< (const ComputeModuleDesc &other) const {
        return other.language < other.language;
    }
    
    bool ComputeModuleDesc::operator== (const ComputeModuleDesc &other) const {
        return other.language == other.language;
    }
    
    bool ComputeModuleDesc::operator!= (const ComputeModuleDesc &other) const {
        return !(*this==other);
    }
}}
