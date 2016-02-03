
#include "PluginCL.hpp"

namespace xe { namespace cm {
    
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

    }

    void PluginCL::terminate() {

    }
}}
