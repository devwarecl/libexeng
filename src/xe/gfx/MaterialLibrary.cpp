
#include "MaterialLibrary.hpp"

#include <xe/Exception.hpp>

namespace xe { namespace gfx {
	//typedef std::unique_ptr<Material> MaterialPtr;
	//typedef std::vector<MaterialPtr> MaterialVector;

	//struct MaterialLibrary::Private {
	//	MaterialVector materials;
	//	MaterialFormat format;
	//};
	//
	//MaterialLibrary::MaterialLibrary(const MaterialFormat &format) {
	//	this->impl = new MaterialLibrary::Private();
	//	this->impl->format = format;
	//}

	//MaterialLibrary::~MaterialLibrary() {
	//	delete this->impl;
	//}

	//MaterialFormat MaterialLibrary::getFormat() const {
	//	return this->impl->format;
	//}

	//Material* MaterialLibrary::createMaterial(const std::string &name, const ShaderProgram *) {
	//	Material *material = new Material(&this->impl->format);

	//	material->setName(name);
	//	
	//	this->impl->materials.push_back(MaterialPtr(material));

	//	return material;
	//}

	//inline Material* findMaterial(const MaterialVector &materials, const std::string &name) {
	//	auto materialIt = std::find_if(materials.begin(), materials.end(), [name](const MaterialPtr &material) {
	//		return material->getName() == name;
	//	});

	//	if (materialIt != materials.end()) {
	//		return materialIt->get();
	//	} 

	//	EXENG_THROW_EXCEPTION("The specified material '" + name  + "' wasn't found.");
	//}

	//Material* MaterialLibrary::getMaterial(const std::string &name) {
	//	return findMaterial(this->impl->materials, name);
	//}

	//Material* MaterialLibrary::getMaterial(const int index) {
	//	return this->impl->materials[index].get();
	//}

	//const Material* MaterialLibrary::getMaterial(const std::string &name) const {
	//	return findMaterial(this->impl->materials, name);
	//}

	//const Material* MaterialLibrary::getMaterial(const int index) const {
	//	return this->impl->materials[index].get();
	//}

	//const int MaterialLibrary::getMaterialCount() const {
	//	return this->impl->materials.size();
	//}

	//const int MaterialLibrary::getMaterialIndex(const Material *material) const {
	//	for (int i=0; i<this->getMaterialCount(); ++i) {
	//		if (this->getMaterial(i) == material) {
	//			return i;
	//		}
	//	}

	//	EXENG_THROW_EXCEPTION("Specified material wasn't found.");
	//}

	MaterialLibrary::~MaterialLibrary() {}

	const int MaterialLibrary::getMaterialIndex(const Material *material) const {
		int index = -1;

		for (int i=0; i<this->getMaterialCount(); i++) {
			if (this->getMaterial(i) == material) {
				index = i;
				break;
			}
		}

		return index;
	}

	const Material* MaterialLibrary::getMaterial(const std::string &name) const {
		const Material *material = nullptr;

		for (int i=0; i<this->getMaterialCount(); i++) {

			const Material *material_ = this->getMaterial(i);

			assert(material_);

			if (material_->getName() == name) {
				material = material_;
				break;
			}
		}

		return material;
	}

	Material* MaterialLibrary::getMaterial(const std::string &name) {
		Material *material = nullptr;

		for (int i=0; i<this->getMaterialCount(); i++) {

			Material *material_ = this->getMaterial(i);

			assert(material_);

			if (material_->getName() == name) {
				material = material_;
				break;
			}
		}

		return material;
	}
}}
