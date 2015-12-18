
#ifndef __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
#define __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__

#include <exeng/Vector.hpp>
#include <exeng/graphics/Texture.hpp>
#include <exeng/graphics/TextureLoader.hpp>

namespace exeng { namespace graphics {
	
	class EXENGAPI GraphicsDriver;
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

	private:
		struct Private;
		Private *impl = nullptr;
	};
}}

#endif	// __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
