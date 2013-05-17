/**
 * @file
 *
 * @brief Implement the Root class.
 *
 */


#include <cassert>
#include <boost/checked_delete.hpp>

#include "Root.hpp"
#include "system/PluginManager.hpp"
#include "scenegraph/MeshManager.hpp"

using namespace exeng;
using namespace exeng::system;
using namespace exeng::scenegraph;

namespace exeng {
    struct Root::Private {
    public:
        Private() : pluginManager(nullptr), meshManager(nullptr) {}
        
        ~Private() {
            boost::checked_delete(this->pluginManager);
        }    
        
    public:
        PluginManager *pluginManager;
        MeshManager *meshManager;
    };
    
    
	Root::Root() : impl(new Root::Private()) {
        this->impl->meshManager = new MeshManager();
        this->impl->pluginManager = new PluginManager(this);
	}
    

	Root::~Root() {
		boost::checked_delete(this->impl);
	}


	PluginManager* Root::getPluginManager() {
		assert(this->impl != nullptr);
		return this->impl->pluginManager;
	}
    
    
    const PluginManager* Root::getPluginManager() const {
		assert(this->impl != nullptr);
		return this->impl->pluginManager;
	}
    
    
    MeshManager* Root::getMeshManager() {
        assert(this->impl != nullptr);
        return this->impl->meshManager;
    }
    
    
    const MeshManager* Root::getMeshManager() const {
        assert(this->impl != nullptr);
        return this->impl->meshManager;
    }
}
