
#ifndef __EXENG_GRAPHICS_TEXTURELOADER_HPP__
#define __EXENG_GRAPHICS_TEXTURELOADER_HPP__

#include <exeng/ResourceLoader.hpp>

namespace exeng { namespace graphics {
	class EXENGAPI GraphicsDriver;
	class EXENGAPI TextureLoader : public ResourceLoader {
	public:
		TextureLoader();
		TextureLoader(GraphicsDriver *graphicsDriver);

		void setGraphicsDriver(GraphicsDriver *graphicsDriver);

		GraphicsDriver* getGraphicsDriver();

	private:
		GraphicsDriver *graphicsDriver = nullptr;
	};
}}

#endif 
