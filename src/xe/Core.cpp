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

#include "Core.hpp"

#include <cassert>
#include <memory>
#include <boost/checked_delete.hpp>

#include <xe/sys/PluginManager.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/TextureManager.hpp>
#include <xe/gfx/MeshManager.hpp>
#include <xe/sg/SceneManager.hpp>

namespace xe {
	using namespace xe::sys;
	using namespace xe::gfx;
	using namespace xe::sg;

    struct Core::Private 
	{
        // The order of the declaration of the different submodules is important.
		std::unique_ptr<GraphicsManager> graphicsManager;
		std::unique_ptr<PluginManager> pluginManager;
		std::unique_ptr<TextureManager> textureManager;
        std::unique_ptr<MeshManager> meshManager;
		SceneManager sceneManager;
    };

    static const char licenseMsg[] = 
        "The C++ Multimedia Engine\n"
        "Copyright (c) 2013 - 2015 Felipe Apablaza\n\n"
        "The license and distribution terms for this library may be\n"
        "found in the file LICENSE in this distribution\n";
    
    Core::Core() 
	{
		this->impl = new Core::Private();
		this->impl->pluginManager.reset(new PluginManager(this));
		this->impl->graphicsManager.reset(new GraphicsManager());
		this->impl->textureManager.reset(new TextureManager());
        this->impl->meshManager.reset(new MeshManager());
    }

    Core::~Core() 
	{
        boost::checked_delete(this->impl);
    }

    PluginManager* Core::getPluginManager() 
	{
        assert(this->impl != nullptr);
        return this->impl->pluginManager.get();
    }

    const PluginManager* Core::getPluginManager() const 
	{
        assert(this->impl != nullptr);
        return this->impl->pluginManager.get();
    }

    MeshManager* Core::getMeshManager() 
	{
        assert(this->impl != nullptr);
        return this->impl->meshManager.get();
    }

    const MeshManager* Core::getMeshManager() const 
	{
        assert(this->impl != nullptr);
        return this->impl->meshManager.get();
    }

    GraphicsManager* Core::getGraphicsManager() 
	{
        assert(this->impl != nullptr);
        return this->impl->graphicsManager.get();
    }

    const GraphicsManager* Core::getGraphicsManager() const 
	{
        assert(this->impl != nullptr);
        return this->impl->graphicsManager.get();
    }

    Version Core::getVersion() const 
	{
        return Version(0, 0, 1, 1);
    }
    
	xe::gfx::TextureManager * Core::getTextureManager() 
	{
        assert(this->impl != nullptr);
        return this->impl->textureManager.get();
    }

	const xe::gfx::TextureManager * Core::getTextureManager() const
	{
        assert(this->impl != nullptr);
        return this->impl->textureManager.get();
    }

	xe::sg::SceneManager* Core::getSceneManager() {
		return &this->impl->sceneManager;
	}

    const xe::sg::SceneManager* Core::getSceneManager() const {
		return &this->impl->sceneManager;
	}
}
