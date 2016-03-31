
/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "Material.hpp"

#include <cassert>
#include <stdexcept>
#include <cstring>
#include <map>
#include <memory>

#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>
#include <boost/lexical_cast.hpp>

#include <xe/Exception.hpp>
#include <xe/gfx/Texture.hpp>
#include <xe/HeapBuffer.hpp>

namespace xe { namespace gfx {
	struct MaterialLayer::Private {
		Texture* texture = nullptr;
		std::string name;
	};
    
	MaterialLayer::MaterialLayer() {
        impl = new MaterialLayer::Private();
    }

	MaterialLayer::~MaterialLayer() {
		boost::checked_delete(impl);
	}

	const Texture* MaterialLayer::getTexture() const {
		assert(impl);
		return impl->texture;
	}

	Texture* MaterialLayer::getTexture() {
		assert(impl);
		return impl->texture;
	}
    
	void MaterialLayer::setTexture(Texture* texture) {
		assert(impl);
		impl->texture = texture;
	}

	bool MaterialLayer::hasTexture() const {
		assert(impl);
		return impl->texture != nullptr;
	}
}}


// Material implementation
namespace xe { namespace gfx {

	static const int LayerCount = 4;
    
	struct Material::Private {
		std::string name;
        const MaterialFormat *format = nullptr;
		const ShaderProgram *shaderProgram = nullptr;
        MaterialLayer layers[LayerCount];

		std::unique_ptr<HeapBuffer> buffer;

		template<typename Type>
		void fillBuffer(void* bufferData, int dimension) {
			Type* data = (Type*)bufferData;

			for (int i=0; i<dimension; i++) {
				data[i] = Type(0);
			}
		}

		void fillBuffer(std::uint8_t *bufferData, DataType::Enum dataType, int dimension) 
		{
			switch (dataType) {
			case DataType::Float32:	
				fillBuffer<float>(bufferData, dimension);	
				break;

			case DataType::Int32:
				fillBuffer<std::int32_t>(bufferData, dimension);
				break;

			default:
				EXENG_THROW_EXCEPTION("DataType don't supported.");
			}
		}

		/**
		 * @brief Fill the internal data of the material with zero's
		 */
		void fill() 
		{
            BufferLocker<std::uint8_t> locker(buffer.get(), BufferUsage::Write);
            
			std::uint8_t *bufferData = locker.getPointer();

			for (int i=0; i<format->getAttribCount(); i++) {
				const MaterialAttrib *attrib = format->getAttrib(i);
				const int offset = format->getOffset(i);

				fillBuffer(&bufferData[offset], attrib->dataType, attrib->dimension);
			}
		}
	};
    
	Material::Material(const MaterialFormat *format) {
        impl = new Material::Private();

		if (!format) {
			EXENG_THROW_EXCEPTION("Format can't be a null pointer.");
		}

		impl->format = format;
		impl->buffer = std::make_unique<HeapBuffer>(format->getSize());
		impl->fill();
    }

	Material::Material(const MaterialFormat *format, const std::string &name) {
        impl = new Material::Private();

		if (!format) {
			EXENG_THROW_EXCEPTION("Format can't be a null pointer.");
		}

		impl->format = format;
		impl->buffer = std::make_unique<HeapBuffer>(format->getSize());
		impl->fill();
        
        setName(name);
    }
	
	Material::~Material() {
		boost::checked_delete(impl);
	}
	
	void Material::setAttribute(const int index, const void* data, const int size) {
        assert(impl);
		assert(impl->format);
          
        BufferLocker<std::uint8_t> locker(impl->buffer.get(), BufferUsage::Write);
        
        const int offset = getFormat()->getOffset(index);
        std::uint8_t* materialData = locker.getPointer();
        
        std::memcpy(materialData + offset, data, getFormat()->getAttrib(index)->getSize());
    }
        
    void Material::getAttribute(const int index, void* data, const int size) const {
        assert(impl);
		assert(impl->format);

        BufferLockerConst<std::uint8_t> locker(impl->buffer.get());
        
        const int offset = getFormat()->getOffset(index);
        const std::uint8_t* materialData = locker.getPointer();
        
        std::memcpy(data, materialData + offset, getFormat()->getAttrib(index)->getSize());
    }
	
	std::string Material::getName() const {
		assert(impl);
		return impl->name;
	}

	void Material::setName(const std::string& name) {
		assert(impl);
		impl->name = name;
	}
    
	MaterialLayer* Material::getLayer(int index) {
		assert(impl);
		assert(index >= 0);
		assert(index < LayerCount);
		
		return &impl->layers[index];
	}
	
	const MaterialLayer* Material::getLayer(int index) const {
		assert(impl);
		assert(index >= 0);
		assert(index < LayerCount);

		return &impl->layers[index];
	}

	TypeInfo Material::getTypeInfo() const {
		assert(impl);
    
		return TypeInfo(typeid(Material));
	}

	const int Material::getLayerCount() {
		return LayerCount;
	}

	bool Material::checkTextureType(const TypeInfo &textureTypeInfo) const {
		assert(impl);
    
		const MaterialLayer *layer = nullptr;
    
		for (int i=0; i<getLayerCount(); ++i ) {
			layer = getLayer(i);
        
			if (layer->hasTexture() == true) {
				if (layer->getTexture()->getTypeInfo() != textureTypeInfo) {
					return false;
				}
			}
		}
    
		return true;
	}
	
	const MaterialFormat* Material::getFormat() const {
        assert(impl);
        
        return impl->format;
    }
	
	bool Material::isSerializable() const {
        assert(impl);
        
        return false;
    }
    
    void Material::serialize(xe::io::Stream *out) const {
        assert(impl);
    }
    
    bool Material::isDeserializable() const {
        assert(impl);
        
        return false;
    }
    
    void Material::deserialize(const xe::io::Stream *inStream) {
        assert(impl);
    }
}}
