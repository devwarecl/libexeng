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

namespace exeng {
    
    struct Root::Private {
        Private(Root *root) : root(nullptr), pluginManager(nullptr) {
            this->root = root;
            this->pluginManager = new system::PluginManager(*root);
        }
        
        ~Private() {
            boost::checked_delete(this->pluginManager);
        }    
        
        Root *root;
        system::PluginManager *pluginManager;
    };

    
	Root::Root() : impl(nullptr) {
		this->impl = new Root::Private(this);
	}


	Root::~Root() {
		boost::checked_delete(this->impl);
	}


	system::PluginManager& Root::getPluginManagerRef() {
		assert(this->impl != nullptr);
		return *this->impl->pluginManager;
	}
}
