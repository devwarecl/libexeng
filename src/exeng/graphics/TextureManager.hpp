
#ifndef __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
#define __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__

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

	private:
		GraphicsDriver* graphicsDriver = nullptr;
	};
}}

#endif	// __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
