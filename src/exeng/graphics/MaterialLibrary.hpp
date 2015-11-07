
#ifndef __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__
#define __EXENG_GRAPHICS_MATERIALLIBRARY_HPP__

#include <string>
#include <memory>
#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/ShaderProgram.hpp>

namespace exeng { namespace graphics {
	/**
	 * @brief Manager class for material collections
	 */
	class EXENGAPI MaterialLibrary : public Object {
	public:
		MaterialLibrary();
		MaterialLibrary(const MaterialFormat &format);
		virtual ~MaterialLibrary();

		void initialize(const MaterialFormat &format);

		bool isInitialized() const;

		MaterialFormat getFormat() const;

		Material* createMaterial(const std::string &name, const ShaderProgram *program);

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
