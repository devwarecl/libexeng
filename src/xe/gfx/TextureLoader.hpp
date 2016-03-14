
#ifndef __EXENG_GRAPHICS_TEXTURELOADER_HPP__
#define __EXENG_GRAPHICS_TEXTURELOADER_HPP__

#include <memory>
#include <xe/gfx/Texture.hpp>
#include <xe/gfx/Forward.hpp>

namespace xe { namespace gfx {
	class EXENGAPI TextureLoader {
	public:
		TextureLoader();
		explicit TextureLoader(GraphicsDriver *graphicsDriver);

		void setGraphicsDriver(GraphicsDriver *graphicsDriver);

		GraphicsDriver* getGraphicsDriver();

		const GraphicsDriver* getGraphicsDriver() const;

		virtual bool isSupported(const std::string &uri) = 0;

		virtual TexturePtr load(const std::string &uri) = 0;

	private:
		GraphicsDriver *graphicsDriver = nullptr;
	};

	typedef std::unique_ptr<TextureLoader> TextureLoaderPtr;
}}

#endif 
