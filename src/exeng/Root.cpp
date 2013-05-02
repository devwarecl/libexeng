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

using exeng::system::PluginManager;

namespace exeng {
    
    struct Root::Private {
    public:
        Private(Root *root) : root(nullptr), pluginManager(nullptr) {
            this->root = root;
            this->pluginManager = new PluginManager(root);
        }
        
        ~Private() {
            boost::checked_delete(this->pluginManager);
        }    
        
    public:
        Root *root;
        system::PluginManager *pluginManager;
    };

    
	Root::Root() : impl(nullptr) {
		this->impl = new Root::Private(this);
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
}
