
#include "TextureManager.hpp"

#include <xe/ProductManagerImpl.hpp>
#include <xe/gfx/GraphicsDriver.hpp>

namespace xe { namespace gfx {

	struct TextureManager::Private {
		GraphicsDriver *graphicsDriver = nullptr;

		ProductManagerImpl<TextureLoader, Texture> manager;
	};

	TextureManager::TextureManager() {
		impl = new TextureManager::Private();
	}

	TextureManager::~TextureManager() {
		delete impl;
	}

	GraphicsDriver* TextureManager::getGraphicsDriver() {
		assert(impl);

		return impl->graphicsDriver;
	}

	const GraphicsDriver* TextureManager::getGraphicsDriver() const {
		assert(impl);

		return impl->graphicsDriver;
	}

	void TextureManager::setGraphicsDriver(GraphicsDriver *graphicsDriver) {
		assert(impl);

		for (TextureLoader* loader: impl->manager.getLoaders()) {
			loader->setGraphicsDriver(graphicsDriver);
		}
		
		impl->graphicsDriver = graphicsDriver;
	}

	Texture* TextureManager::getTexture(const std::string &uri) {
		assert(impl);

		return impl->manager.getProduct(uri);
	}

	const Texture* TextureManager::getTexture(const std::string &uri) const {

		assert(impl);
		return impl->manager.getProduct(uri);
	}

	void TextureManager::addLoader(TextureLoader *loader) {
		assert(impl);

		impl->manager.addLoader(loader);
	}

	void TextureManager::removeLoader(TextureLoader *loader) {
		assert(impl);

		impl->manager.removeLoader(loader);
	}

	Texture* TextureManager::generateCheckerboard(const std::string &uri, const Vector2i &size, const Vector2i &tileSize) {
		assert(impl);

		PixelFormat::Enum format = PixelFormat::R8G8B8A8;

		TexturePtr texture = getGraphicsDriver()->createTexture(size, format);
        
        {
            auto locker = texture->getBuffer()->getLocker<Vector4ub>();
        
            Vector4ub *pixels = locker.getPointer();
    
            for (int row=0; row<size.y; row++) {
                for (int col=0; col<size.x; col++) {
                    bool rowBool = ((row&tileSize.y) == 0);
                    bool colBool = ((col&tileSize.x) == 0);
    
                    int c = ((int)(rowBool^colBool))*255;
    
                    pixels->x = (std::uint8_t) c;
                    pixels->y = (std::uint8_t) c;
                    pixels->z = (std::uint8_t) c;
                    pixels->w = (std::uint8_t) 255;
    
                    ++pixels;
                }
            }
        }
        
		Texture *result = texture.get();

		impl->manager.putProduct(uri, std::move(texture));

		return result;
	}

    Texture* TextureManager::create(const std::string &uri, const Vector2i &size) {
		assert(impl);

		PixelFormat::Enum format = PixelFormat::R8G8B8A8;

		TexturePtr texture = getGraphicsDriver()->createTexture(size, format);

        impl->manager.putProduct(uri, std::move(texture));

        return getTexture(uri);
    }

    Texture* TextureManager::create(const std::string &uri, const Vector2i &size, const Vector4f &color) {
		assert(impl);

        Texture *texture = create(uri, size);

        auto locker = texture->getBuffer()->getLocker<Vector4ub>();
        
        Vector4ub *textureData = locker.getPointer();
        for (int i=0; i<size.x * size.y; ++i) {
			textureData[i] = static_cast<Vector4ub>(color * Vector4f(255.0f, 255.0f, 255.0f, 255.0f));
        }
        
        return texture;
    }

	Texture* TextureManager::create(const std::string &uri, const Image *image) {
		assert(impl);

		TexturePtr texture = getGraphicsDriver()->createTexture(image);

        impl->manager.putProduct(uri, std::move(texture));

        return getTexture(uri);
	}

	void TextureManager::cleanup() {
		assert(impl);

		impl->manager.cleanup();
	}
}}
