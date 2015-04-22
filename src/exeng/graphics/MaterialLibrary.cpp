
#include "MaterialLibrary.hpp"

#include <map>
#include <memory>
#include <vector>
#include <exeng/Exception.hpp>

namespace exeng { namespace graphics {
	typedef std::unique_ptr<Material> MaterialPtr;
	typedef std::vector<MaterialPtr> MaterialVector;

	struct MaterialLibrary::Private {
		MaterialVector materials;
		MaterialFormat format;
		const ShaderProgram *program = nullptr;
	};

	MaterialLibrary::MaterialLibrary(const MaterialFormat &format, const ShaderProgram *program) {
		this->impl = new MaterialLibrary::Private();
		this->impl->format = format;
		this->impl->program = program;
	}

	MaterialLibrary::~MaterialLibrary() {
		delete this->impl;
	}

	Material* MaterialLibrary::createMaterial(const std::string &name) {
		return this->createMaterial(name, this->impl->program);
	}

	Material* MaterialLibrary::createMaterial(const std::string &name, const ShaderProgram *program) {
		Material *material = new Material(&this->impl->format);

		material->setName(name);
		material->setShaderProgram(program);

		this->impl->materials.push_back(MaterialPtr(material));

		return material;
	}

	inline Material* findMaterial(const MaterialVector &materials, const std::string &name) {
		auto materialIt = std::find_if(materials.begin(), materials.end(), [name](const MaterialPtr &material) {
			return material->getName() == name;
		});

		if (materialIt != materials.end()) {
			return materialIt->get();
		} 

		EXENG_THROW_EXCEPTION("Specified material wasn't found.");
	}

	Material* MaterialLibrary::getMaterial(const std::string &name) {
		return findMaterial(this->impl->materials, name);
	}

	Material* MaterialLibrary::getMaterial(const int index) {
		return this->impl->materials[index].get();
	}

	const Material* MaterialLibrary::getMaterial(const std::string &name) const {
		return findMaterial(this->impl->materials, name);
	}

	const Material* MaterialLibrary::getMaterial(const int index) const {
		return this->impl->materials[index].get();
	}

	const int MaterialLibrary::getMaterialCount() const {
		return this->impl->materials.size();
	}

	const int MaterialLibrary::getMaterialIndex(const Material *material) const {
		for (int i=0; i<this->getMaterialCount(); ++i) {
			if (this->getMaterial(i) == material) {
				return i;
			}
		}

		EXENG_THROW_EXCEPTION("Specified material wasn't found.");
	}
}}
