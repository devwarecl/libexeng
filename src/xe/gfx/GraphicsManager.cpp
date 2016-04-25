/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/TextureLoaderImage.hpp>

#include <stdexcept>
#include <map>
#include <sstream>
#include <cassert>

namespace xe { namespace gfx {

    struct GraphicsManager::Private {
        std::map <GraphicsDriverInfo, IGraphicsDriverFactory*> factories;

		TextureLoaderImage textureLoaderImage;
		TextureManager textureManager;
		MeshManager meshManager;
		ImageLoader *imageLoader = nullptr;
    };

    GraphicsManager::GraphicsManager() {
		impl = new GraphicsManager::Private();
		
		this->getTextureManager()->addLoader(&impl->textureLoaderImage);
		this->getMeshManager()->setTextureManager(this->getTextureManager());
    }

    GraphicsManager::~GraphicsManager()  {
        delete impl;
    }

    void GraphicsManager::addDriverFactory(IGraphicsDriverFactory* factory) {
        assert(impl);
        
        if (factory == nullptr) {
            throw std::invalid_argument("GraphicsManager::addDriverFactory: the factory can't be null");
        }
        
        GraphicsDriverInfo driverInfo = factory->getDriverInfo();
        impl->factories.insert({driverInfo, factory});
    }

    void GraphicsManager::removeDriverFactory(IGraphicsDriverFactory* factory) {
        assert(impl);
        
        if (factory == nullptr) {
            throw std::invalid_argument("GraphicsManager::addDriverFactory -> The factory can't be a null pointer.");
        }

        auto &factories = impl->factories;
        auto key = factory->getDriverInfo();
        auto pos = factories.find(key);
        
        if (pos == factories.end()) {
            throw std::runtime_error("GraphicsManager::addDriverFactory -> The factory isn't in the graphics manager instance.");
        }
        
        factories.erase(pos);
    }
    
    //std::unique_ptr<GraphicsDriver> GraphicsManager::createDriver() {
    //    assert(impl);
    //    
    //    for (auto element : impl->factories) {
    //        return element.second->create();
    //    }
    //    
    //    return nullptr;
    //}
    //
    //std::unique_ptr<GraphicsDriver> GraphicsManager::createDriver(const GraphicsDriverInfo &info) {
    //    assert(impl);
    //    
    //    auto &factories = impl->factories;
    //    auto pos = factories.find(info);
    //    
    //    if (pos == factories.end()) {
    //        throw std::runtime_error("GraphicsManager::createDriver -> Driver with the specified info not registered.");
    //    }
    //    
    //    return pos->second->create();
    //}

	std::vector<GraphicsDriverInfo> GraphicsManager::getAvailableDrivers() const {
		assert(impl);

		std::vector<GraphicsDriverInfo> driverInfos;

		for (auto driverIterator : impl->factories) {
			driverInfos.push_back(driverIterator.first);
		}

		return driverInfos;
	}

	void GraphicsManager::setImageToolkit(ImageLoader* loader) {
		assert(impl);

		impl->textureLoaderImage = TextureLoaderImage(loader);
		impl->imageLoader = loader;
	}

	ImageLoader* GraphicsManager::getImageToolkit() {
		assert(impl);

		return impl->imageLoader;
	}

	const ImageLoader* GraphicsManager::getImageToolkit() const {
		assert(impl);

		return impl->imageLoader;
	}

	TextureManager* GraphicsManager::getTextureManager() {
		assert(impl);

		return &impl->textureManager;
	}

	const TextureManager* GraphicsManager::getTextureManager() const {
		assert(impl);

		return &impl->textureManager;
	}

	MeshManager* GraphicsManager::getMeshManager() {
		assert(impl);

		return &impl->meshManager;
	}

	const MeshManager* GraphicsManager::getMeshManager() const {
		assert(impl);

		return &impl->meshManager;
	}
}}
