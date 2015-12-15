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

#include <exeng/system/PluginManager.hpp>
#include <exeng/graphics/GraphicsManager.hpp>
#include <exeng/graphics/TextureManager.hpp>
#include <exeng/scenegraph/MeshManager.hpp>

namespace exeng {
	using namespace exeng::system;
	using namespace exeng::scenegraph;
	using namespace exeng::graphics;

    struct Core::Private 
	{
        // The order of the declaration of the different submodules is important.
		std::unique_ptr<GraphicsManager> graphicsManager;
		std::unique_ptr<PluginManager> pluginManager;
		std::unique_ptr<TextureManager> textureManager;
        std::unique_ptr<MeshManager> meshManager;
        // std::unique_ptr<SceneManager> sceneManager;
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
    
	exeng::graphics::TextureManager * Core::getTextureManager() 
	{
        assert(this->impl != nullptr);
        return this->impl->textureManager.get();
    }

	const exeng::graphics::TextureManager * Core::getTextureManager() const
	{
        assert(this->impl != nullptr);
        return this->impl->textureManager.get();
    }
}
