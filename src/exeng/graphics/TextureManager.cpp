
#include "TextureManager.hpp"

#include <exeng/Size.hpp>
#include <exeng/ProductManagerImpl.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>

namespace xe { namespace gfx {

	struct TextureManager::Private {
		GraphicsDriver *graphicsDriver = nullptr;

		ProductManagerImpl<TextureLoader, Texture> manager;
	};

	TextureManager::TextureManager() {
		this->impl = new TextureManager::Private();
	}

	TextureManager::~TextureManager() {
		delete this->impl;
	}

	GraphicsDriver* TextureManager::getGraphicsDriver() {
		return this->impl->graphicsDriver;
	}

	const GraphicsDriver* TextureManager::getGraphicsDriver() const {
		return this->impl->graphicsDriver;
	}

	void TextureManager::setGraphicsDriver(GraphicsDriver *graphicsDriver) {
		for (TextureLoader* loader: this->impl->manager.getLoaders()) {
			loader->setGraphicsDriver(graphicsDriver);
		}
		
		this->impl->graphicsDriver = graphicsDriver;
	}

	Texture* TextureManager::getTexture(const std::string &uri) {
		return this->impl->manager.getProduct(uri);
	}

	const Texture* TextureManager::getTexture(const std::string &uri) const {
		return this->impl->manager.getProduct(uri);
	}

	void TextureManager::addLoader(TextureLoader *loader) {
		this->impl->manager.addLoader(loader);
	}

	void TextureManager::removeLoader(TextureLoader *loader) {
		this->impl->manager.removeLoader(loader);
	}

	Texture* TextureManager::generateCheckerboard(const std::string &uri, const Vector2i &size, const Vector2i &tileSize) {
		const ColorFormat format = ColorFormat::getR8G8B8A8();
		TexturePtr texture = this->getGraphicsDriver()->createTexture(size, format);
		Vector4ub *pixels = (Vector4ub *)texture->lock();

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

		texture->unlock();

		Texture *result = texture.get();

		this->impl->manager.putProduct(uri, std::move(texture));

		return result;
	}

    Texture* TextureManager::create(const std::string &uri, const Vector2i &size) {
		const ColorFormat format = ColorFormat::getR8G8B8A8();

		TexturePtr texture = this->getGraphicsDriver()->createTexture(size, format);

        this->impl->manager.putProduct(uri, std::move(texture));

        return this->getTexture(uri);
    }

    Texture* TextureManager::create(const std::string &uri, const Vector2i &size, const Vector4f &color) {
        Texture *texture = this->create(uri, size);

        Vector4ub *textureData = reinterpret_cast<Vector4ub*>(texture->lock());
        for (int i=0; i<size.x * size.y; ++i) {
			textureData[i] = static_cast<Vector4ub>(color * Vector4f(255.0f, 255.0f, 255.0f, 255.0f));
        }
        texture->unlock();

        return texture;
    }
}}
