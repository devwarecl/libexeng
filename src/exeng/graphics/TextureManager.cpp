
#include "TextureManager.hpp"

#include <exeng/Size.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>

namespace exeng { namespace graphics {

	GraphicsDriver* TextureManager::getGraphicsDriver() {
		return this->graphicsDriver;
	}

	const GraphicsDriver* TextureManager::getGraphicsDriver() const {
		return this->graphicsDriver;
	}

	void TextureManager::setGraphicsDriver(GraphicsDriver *graphicsDriver) {
		for (ResourceLoader* resourceLoader : this->getLoaders()) {
			TextureLoader* textureLoader = static_cast<TextureLoader*>(resourceLoader);
			textureLoader->setGraphicsDriver(graphicsDriver);
		}
		
		this->graphicsDriver = graphicsDriver;
	}

	Texture* TextureManager::get(const std::string &uri) {
		return static_cast<Texture*>(ResourceManager::get(uri));
	}

	const Texture* TextureManager::get(const std::string &uri) const {
		return static_cast<const Texture*>(ResourceManager::get(uri));
	}

	void TextureManager::addLoader(TextureLoader *loader) {
		ResourceManager::addLoader(loader);
		loader->setGraphicsDriver(this->graphicsDriver);
	}

	void TextureManager::removeLoader(TextureLoader *loader) {
		ResourceManager::removeLoader(loader);
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

		this->put(uri, std::move(texture));

		return result;
	}

    Texture* TextureManager::create(const std::string &uri, const Vector2i &size) {
		const ColorFormat format = ColorFormat::getR8G8B8A8();

		TexturePtr texture = this->getGraphicsDriver()->createTexture(size, format);

        this->put(uri, std::move(texture));

        return this->get(uri);
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
