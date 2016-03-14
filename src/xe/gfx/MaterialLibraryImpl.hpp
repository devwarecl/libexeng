#pragma once

#ifndef __xe_gfx_materiallibraryimpl_hpp__
#define __xe_gfx_materiallibraryimpl_hpp__

#include <xe/gfx/MaterialLibrary.hpp>
#include <map>
#include <memory>
#include <vector>

namespace xe { namespace gfx {

	class MaterialLibraryImpl : public MaterialLibrary {
	public:
		explicit MaterialLibraryImpl(const MaterialFormat &format_) : format(format_) {}
		virtual ~MaterialLibraryImpl() {}

		virtual MaterialFormat getFormat() const override {
			return format;
		}

		virtual Material* createMaterial(const std::string &name = "") override {
			Material *material = new Material(&this->format);

			material->setName(name);
				
			this->materials.push_back(MaterialPtr(material));

			return material;
		}

		virtual Material* getMaterial(const int index) override {
			assert(index >= 0);
			assert(index < this->getMaterialCount());

			return materials[index].get();
		}

		virtual const Material* getMaterial(const int index) const override {
			assert(index >= 0);
			assert(index < this->getMaterialCount());

			return materials[index].get();
		}

		virtual const int getMaterialCount() const override {
			return materials.size();
		}

	private:
		std::vector<MaterialPtr> materials;
		MaterialFormat format;
	};
}}

#endif
