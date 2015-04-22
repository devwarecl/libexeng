
#ifndef __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__
#define __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__

#include <string>
#include <memory>

#include <exeng/graphics/Material.hpp>

namespace exeng { namespace graphics {
	/**
	 * @brief Manager class for material collections
	 */
	class EXENGAPI MaterialLibrary {
	public:
		MaterialLibrary(const MaterialFormat *format);

		Material* getMaterial(const std::string &name);

	private:
		struct Private;
		Private *impl = nullptr;
	};
}}

#endif	// __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__
