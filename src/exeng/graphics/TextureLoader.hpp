
#ifndef __EXENG_GRAPHICS_TEXTURELOADER_HPP__
#define __EXENG_GRAPHICS_TEXTURELOADER_HPP__

#include <exeng/graphics/Texture.hpp>

namespace exeng { namespace graphics {
	class EXENGAPI GraphicsDriver;
	class EXENGAPI TextureLoader {
	public:
		TextureLoader();
		explicit TextureLoader(GraphicsDriver *graphicsDriver);

		void setGraphicsDriver(GraphicsDriver *graphicsDriver);

		GraphicsDriver* getGraphicsDriver();

		const GraphicsDriver* getGraphicsDriver() const;

		virtual bool tryLoad(const std::string &uri) = 0;

		virtual TexturePtr load(const std::string &uri) = 0;

	private:
		GraphicsDriver *graphicsDriver = nullptr;
	};
}}

#endif 
