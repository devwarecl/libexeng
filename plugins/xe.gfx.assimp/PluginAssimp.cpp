
#include "PluginAssimp.hpp"

#include <xe/Core.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/MeshManager.hpp>

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
		core->getGraphicsManager()->getMeshManager()->addMeshLoader(&meshLoader);
    }
    
    void PluginAssimp::terminate() {
        core->getGraphicsManager()->getMeshManager()->removeMeshLoader(&meshLoader);
    }
}}


#if defined (EXENG_WINDOWS)
#  if defined (EXENG_64)
#    pragma comment (linker, "/export:ExengGetPluginObject")
#    undef EXENG_EXPORT
#  endif
#endif 

EXENG_EXPORT_PLUGIN(xe::gfx::PluginAssimp);
