
#ifndef __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
#define __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__

#include <exeng/Vector.hpp>
#include <exeng/ResourceManager.hpp>
#include <exeng/graphics/Texture.hpp>
#include <exeng/graphics/TextureLoader.hpp>

namespace exeng { namespace graphics {
	
	class EXENGAPI GraphicsDriver;
	class EXENGAPI TextureManager : public ResourceManager {
	public:
		GraphicsDriver* getGraphicsDriver();
		const GraphicsDriver* getGraphicsDriver() const;

		void setGraphicsDriver(GraphicsDriver *graphicsDriver);

		virtual Texture* get(const std::string &uri) override;
		virtual const Texture* get(const std::string &uri) const override;

		virtual void addLoader(TextureLoader *loader);
		virtual void removeLoader(TextureLoader *loader);

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
		GraphicsDriver* graphicsDriver = nullptr;
	};
}}

#endif	// __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
