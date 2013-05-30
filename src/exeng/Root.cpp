/**
 * @file
 *
 * @brief Implement the Root class.
 *
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include <cassert>
#include <boost/checked_delete.hpp>
#include <iostream>

#include <exeng/Root.hpp>
#include <exeng/system/PluginManager.hpp>
#include <exeng/scenegraph/MeshManager.hpp>
#include <exeng/graphics/GraphicsManager.hpp>

using namespace exeng;
using namespace exeng::system;
using namespace exeng::scenegraph;
using namespace exeng::graphics;

namespace exeng {
    struct Root::Private {
    public:
        Private() {
            this->pluginManager = nullptr;
            this->meshManager = nullptr;
            this->graphicsManager = nullptr;
        }
        
        ~Private() {
            boost::checked_delete(this->pluginManager);
            boost::checked_delete(this->meshManager);
            boost::checked_delete(this->graphicsManager);
        }    
        
    public:
        PluginManager *pluginManager;
        MeshManager *meshManager;
        GraphicsManager *graphicsManager;
    };
    
    
	Root::Root() : impl(new Root::Private()) {
        std::cout << "The C++ Multimedia Engine" << std::endl;
        std::cout << "Copyright (c) 2013 Felipe Apablaza" << std::endl;
        std::cout << std::endl;
        std::cout << "The license and distribution terms for this library may be" << std::endl;
        std::cout << "found in the file LICENSE in this distribution" << std::endl;
        
        this->impl->meshManager = new MeshManager();
        this->impl->graphicsManager = new GraphicsManager();
        
        std::cout << "" << std::endl;
        
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
    
    
    GraphicsManager* Root::getGraphicsManager() {
        assert(this->impl != nullptr);
        return this->impl->graphicsManager;
    }
    

    const GraphicsManager* Root::getGraphicsManager() const {
        assert(this->impl != nullptr);
        return this->impl->graphicsManager;
    }
    
    
    Version Root::getVersion() const {
        return Version(0, 0, 1, 1);
    }
}
