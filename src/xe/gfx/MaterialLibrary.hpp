
#ifndef __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__
#define __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__

#include <string>
#include <memory>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/ShaderProgram.hpp>

namespace xe { namespace gfx {
	/**
	 * @brief Material library interface
	 */
	class EXENGAPI MaterialLibrary {
	public:
		virtual ~MaterialLibrary();

		// mandatory overridables
	public:
		virtual MaterialFormat getFormat() const = 0;
		virtual Material* createMaterial(const std::string &name = "") = 0;
		virtual Material* getMaterial(const int index) = 0;
		virtual const Material* getMaterial(const int index) const = 0;
		virtual const int getMaterialCount() const = 0;

		// optional overridables
	public:
		virtual const int getMaterialIndex(const Material *material) const;
		virtual const Material* getMaterial(const std::string &name) const;
		virtual Material* getMaterial(const std::string &name);
	};

	typedef std::unique_ptr<MaterialLibrary> MaterialLibraryPtr;
}}

#endif	// __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__
