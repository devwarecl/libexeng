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
#include <xe/cm/ComputeManager.hpp>

namespace xe {
	using namespace xe::sys;
	using namespace xe::gfx;
	using namespace xe::sg;

    struct Core::Private {
        // The order of the declaration of the different submodules is important.
		xe::gfx::GraphicsManager graphicsManager;
		xe::cm::ComputeManager computeManager;
		xe::sys::PluginManager pluginManager;
		xe::gfx::TextureManager textureManager;
        xe::gfx::MeshManager meshManager;
		xe::sg::SceneManager sceneManager;
    };

    const char licenseMsg[] = 
        "The C++ Multimedia Engine\n"
        "Copyright (c) 2013 - 2015 Felipe Apablaza\n\n"
        "The license and distribution terms for this library may be\n"
        "found in the file LICENSE in this distribution\n";
    
    Core::Core() {
		this->impl = new Core::Private();
		this->impl->pluginManager.setCore(this);
    }

    Core::~Core() {
        boost::checked_delete(this->impl);
    }

    Version Core::getVersion() const {
        return Version(0, 0, 1, 1);
    }
    
    PluginManager* Core::getPluginManager() {
        assert(this->impl != nullptr);
        return &this->impl->pluginManager;
    }

    const PluginManager* Core::getPluginManager() const {
        assert(this->impl != nullptr);
        return &this->impl->pluginManager;
    }

    MeshManager* Core::getMeshManager() {
        assert(this->impl != nullptr);
        return &this->impl->meshManager;
    }

    const MeshManager* Core::getMeshManager() const {
        assert(this->impl != nullptr);
        return &this->impl->meshManager;
    }

    GraphicsManager* Core::getGraphicsManager() {
        assert(this->impl != nullptr);
        return &this->impl->graphicsManager;
    }

    const GraphicsManager* Core::getGraphicsManager() const {
        assert(this->impl != nullptr);
        return &this->impl->graphicsManager;
    }

	xe::gfx::TextureManager* Core::getTextureManager() {
        assert(this->impl != nullptr);
        return &this->impl->textureManager;
    }

	const xe::gfx::TextureManager* Core::getTextureManager() const {
        assert(this->impl != nullptr);
        return &this->impl->textureManager;
    }

	xe::sg::SceneManager* Core::getSceneManager() {
		return &this->impl->sceneManager;
	}

    const xe::sg::SceneManager* Core::getSceneManager() const {
		return &this->impl->sceneManager;
	}

	xe::cm::ComputeManager* Core::getComputeManager() {
		assert(this->impl != nullptr);
		return &this->impl->computeManager;
	}

	const xe::cm::ComputeManager* Core::getComputeManager() const {
		assert(this->impl != nullptr);
		return &this->impl->computeManager;
	}
}
