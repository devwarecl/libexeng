/**
 * @file
 * @brief Root class implementation
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <cassert>
#include <boost/checked_delete.hpp>
#include <memory>
#include <iostream>
#include <exeng/Root.hpp>
#include <exeng/system/PluginManager.hpp>
#include <exeng/graphics/GraphicsManager.hpp>
#include <exeng/scenegraph/MeshManager.hpp>
#include <exeng/scenegraph/SceneManager.hpp>

using namespace exeng;
using namespace exeng::system;
using namespace exeng::scenegraph;
using namespace exeng::graphics;

namespace exeng {
#if defined(EXENG_DEBUG)
    extern int count;
#endif
    
    struct Root::Private {
        std::unique_ptr<PluginManager> pluginManager;
        std::unique_ptr<MeshManager> meshManager;
        std::unique_ptr<GraphicsManager> graphicsManager;
        std::unique_ptr<SceneManager> sceneManager;
    };

    static const char licenseMsg[] = 
            "The C++ Multimedia Engine\n"
            "Copyright (c) 2013 Felipe Apablaza\n\n"
            "The license and distribution terms for this library may be\n"
            "found in the file LICENSE in this distribution\n";
    
    Root::Root() : impl(new Root::Private()) {
        std::cout << licenseMsg << std::endl;
        
        this->impl->graphicsManager.reset(new GraphicsManager());
        this->impl->pluginManager.reset(new PluginManager(this));
        this->impl->meshManager.reset(new MeshManager());
        this->impl->sceneManager.reset(new SceneManager(this));
    }

    Root::~Root() {
        boost::checked_delete(this->impl);
        
#if defined (EXENG_DEBUG)
        if (count !=0) {
            std::cout << "Root::~Root: Detected object leaks!. " << count << " objects non freed." << std::endl;
        }   
#endif
    }

    PluginManager* Root::getPluginManager() {
        assert(this->impl != nullptr);
        return this->impl->pluginManager.get();
    }

    const PluginManager* Root::getPluginManager() const {
        assert(this->impl != nullptr);
        return this->impl->pluginManager.get();
    }

    MeshManager* Root::getMeshManager() {
        assert(this->impl != nullptr);
        return this->impl->meshManager.get();
    }

    const MeshManager* Root::getMeshManager() const {
        assert(this->impl != nullptr);
        return this->impl->meshManager.get();
    }

    GraphicsManager* Root::getGraphicsManager() {
        assert(this->impl != nullptr);
        return this->impl->graphicsManager.get();
    }

    const GraphicsManager* Root::getGraphicsManager() const {
        assert(this->impl != nullptr);
        return this->impl->graphicsManager.get();
    }

    Version Root::getVersion() const {
        return Version(0, 0, 1, 1);
    }
        
    exeng::scenegraph::SceneManager* Root::getSceneManager() {
        assert(this->impl != nullptr);
        return this->impl->sceneManager.get();
    }

    const exeng::scenegraph::SceneManager* Root::getSceneManager() const {
        assert(this->impl != nullptr);
        return this->impl->sceneManager.get();
    }
}
