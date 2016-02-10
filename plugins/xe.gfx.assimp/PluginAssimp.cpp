
#include "PluginAssimp.hpp"

namespace xe { namespace gfx {

    PluginAssimp::PluginAssimp() {}
    
    PluginAssimp::~PluginAssimp() {}
    
    std::string PluginAssimp::getName() const {
        return "";
    }
    
    std::string PluginAssimp::getDescription() const {
        return "";
    }
    
    Version PluginAssimp::getVersion() const {
        return Version();
    }
    
    void PluginAssimp::initialize(Core *core_) {
        core = core_;
    }
    
    void PluginAssimp::terminate() {
        
    }
}}

