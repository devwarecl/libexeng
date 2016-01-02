
#ifndef __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__
#define __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__

#include <string>
#include <memory>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/ShaderProgram.hpp>

namespace xe { namespace gfx {
	/**
	 * @brief Manager class for material collections
	 */
	class EXENGAPI MaterialLibrary {
	public:
		MaterialLibrary(const MaterialFormat &format);
		virtual ~MaterialLibrary();

		MaterialFormat getFormat() const;

		Material* createMaterial(const std::string &name, const ShaderProgram *program=nullptr);

		Material* getMaterial(const std::string &name);
		Material* getMaterial(const int index);

		const Material* getMaterial(const std::string &name) const;
		const Material* getMaterial(const int index) const;
		const int getMaterialCount() const;
		const int getMaterialIndex(const Material *material) const;

	private:
		struct Private;
		Private *impl = nullptr;
	};

	typedef std::unique_ptr<MaterialLibrary> MaterialLibraryPtr;
}}

#endif	// __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__
