
#include <xe/Core.hpp>
#include <xe/cm/ComputeManager.hpp>

#include "PluginCL.hpp"


namespace xe { namespace cm {    
    PluginCL::PluginCL() {}
        
    PluginCL::~PluginCL() {}
    
	std::string PluginCL::getName() const {
        return "OpenCL Computing Module Plugin";
    }

    std::string PluginCL::getDescription() const {
        return "TODO: No description yet.";
    }

    Version PluginCL::getVersion() const {
        return {1, 0, 0, 0};
    }

    void PluginCL::initialize(Core *core) {
        core->getComputeManager()->addFactory(&factory);
    }

    void PluginCL::terminate() {}
}}


#if defined (EXENG_WINDOWS)
#  if defined (EXENG_64)
#    pragma comment (linker, "/export:ExengGetPluginObject")
#    undef EXENG_EXPORT
#  endif
#endif 

EXENG_EXPORT_PLUGIN(xe::cm::PluginCL);
