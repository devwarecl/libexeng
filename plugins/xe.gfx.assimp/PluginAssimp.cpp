
#include "PluginAssimp.hpp"

namespace xe { namespace gfx {

    PluginAssimp::PluginAssimp() {}
    
    PluginAssimp::~PluginAssimp() {}
    
    std::string PluginAssimp::getName() const {
        return "Assimp mesh loader";
    }
    
    std::string PluginAssimp::getDescription() const {
        return "Mesh loader based on the Assimp library.";
    }
    
    Version PluginAssimp::getVersion() const {
        return Version(1, 0, 0, 1);
    }
    
    void PluginAssimp::initialize(Core *core_) {
        core = core_;
    }
    
    void PluginAssimp::terminate() {
        
    }
}}

