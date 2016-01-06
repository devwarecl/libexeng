
#ifndef __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
#define __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__

#include <xe/Vector.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/gfx/Texture.hpp>
#include <xe/gfx/TextureLoader.hpp>

namespace xe { namespace gfx {
	
	class EXENGAPI TextureManager {
	public:
		TextureManager();
		~TextureManager();

		GraphicsDriver* getGraphicsDriver();
		const GraphicsDriver* getGraphicsDriver() const;

		void setGraphicsDriver(GraphicsDriver *graphicsDriver);

		Texture* getTexture(const std::string &uri);
		const Texture* getTexture(const std::string &uri) const;

		void addLoader(TextureLoader *loader);
		void removeLoader(TextureLoader *loader);

		Texture* generateCheckerboard(const std::string &uri, const Vector2i &size, const Vector2i &tileSize);

        /**
         * @brief Create a managed, empty texture.
         */
        Texture* create(const std::string &uri, const Vector2i &size);

        /**
         * @brief Create a managed, empty texture initialized with a default color.
         */
        Texture* create(const std::string &uri, const Vector2i &size, const Vector4f &color);

		Texture* create(const std::string &uri, const Image *image);

	private:
		struct Private;
		Private *impl = nullptr;
	};
}}

#endif	// __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
