
#ifndef __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
#define __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__

#include <exeng/Config.hpp>
#include <exeng/graphics/Texture.hpp>

namespace exeng { namespace graphics {

	template<typename AbstractResource>
	class ResourceLoader {
	public:
		virtual ~ResourceLoader() = 0 {}
		std::unique_ptr<AbstractResource> load();
	};

	class EXENGAPI TextureLoader {
	public:
		virtual ~TextureLoader() = 0;
	};

	class EXENGAPI TextureManager {
	public:
		TextureManager();
		~TextureManager();

	private:
		struct Impl;
		Impl *impl = nullptr;
	};
}}

#endif	// __EXENG_GRAPHICS_TEXTUREMANAGER_HPP__
