
#include "MaterialLibrary.hpp"

#include <map>
#include <memory>
#include <vector>
#include <xe/Exception.hpp>

namespace xe { namespace gfx {
	typedef std::unique_ptr<Material> MaterialPtr;
	typedef std::vector<MaterialPtr> MaterialVector;

	struct MaterialLibrary::Private {
		MaterialVector materials;
		MaterialFormat format;
		const ShaderProgram *program = nullptr;
		bool initialized = false;
	};
	
	MaterialLibrary::MaterialLibrary() {
		this->initialize(MaterialFormat());
	}

	MaterialLibrary::MaterialLibrary(const MaterialFormat &format) {
		this->initialize(format);
	}

	void MaterialLibrary::initialize(const MaterialFormat &format) {
		if (this->impl) {
			delete this->impl;
			this->impl = nullptr;
		}

		this->impl = new MaterialLibrary::Private();
		this->impl->format = format;
		this->impl->initialized = true;
	}

	MaterialLibrary::~MaterialLibrary() {
		delete this->impl;
	}

	bool MaterialLibrary::isInitialized() const {
		return this->impl->initialized;
	}

	Material* MaterialLibrary::createMaterial(const std::string &name, const ShaderProgram *program) {
		if (!this->isInitialized()) {
			EXENG_THROW_EXCEPTION("The material library isn't intialized.");
		}

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

		EXENG_THROW_EXCEPTION("The specified material '" + name  + "' wasn't found.");
	}

	Material* MaterialLibrary::getMaterial(const std::string &name) {
		if (!this->isInitialized()) {
			EXENG_THROW_EXCEPTION("The material library isn't intialized.");
		}

		return findMaterial(this->impl->materials, name);
	}

	Material* MaterialLibrary::getMaterial(const int index) {
		if (!this->isInitialized()) {
			EXENG_THROW_EXCEPTION("The material library isn't intialized.");
		}


		return this->impl->materials[index].get();
	}

	const Material* MaterialLibrary::getMaterial(const std::string &name) const {
		if (!this->isInitialized()) {
			EXENG_THROW_EXCEPTION("The material library isn't intialized.");
		}


		return findMaterial(this->impl->materials, name);
	}

	const Material* MaterialLibrary::getMaterial(const int index) const {
		if (!this->isInitialized()) {
			EXENG_THROW_EXCEPTION("The material library isn't intialized.");
		}


		return this->impl->materials[index].get();
	}

	const int MaterialLibrary::getMaterialCount() const {
		if (!this->isInitialized()) {
			EXENG_THROW_EXCEPTION("The material library isn't intialized.");
		}

		return this->impl->materials.size();
	}

	const int MaterialLibrary::getMaterialIndex(const Material *material) const {
		if (!this->isInitialized()) {
			EXENG_THROW_EXCEPTION("The material library isn't intialized.");
		}

		for (int i=0; i<this->getMaterialCount(); ++i) {
			if (this->getMaterial(i) == material) {
				return i;
			}
		}

		EXENG_THROW_EXCEPTION("Specified material wasn't found.");
	}
}}
