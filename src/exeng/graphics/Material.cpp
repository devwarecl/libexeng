
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
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>
#include <boost/lexical_cast.hpp>

#include <exeng/graphics/Texture.hpp>
#include <exeng/io/Stream.hpp>
#include <exeng/HeapBuffer.hpp>

namespace exeng { namespace graphics {

	struct MaterialLayer::Private 
	{
		Texture* texture = nullptr;
	};
    
	MaterialLayer::MaterialLayer() : impl(nullptr) 
    {
        this->impl = new MaterialLayer::Private();
    }

	MaterialLayer::~MaterialLayer() 
    {
		boost::checked_delete(this->impl);
	}

	const Texture* MaterialLayer::getTexture() const 
	{
		assert(this->impl != nullptr);
		return this->impl->texture;
	}

	Texture* MaterialLayer::getTexture() 
    {
		assert(this->impl != nullptr);
		return this->impl->texture;
	}
    
	void MaterialLayer::setTexture(Texture* texture) 
    {
		assert(this->impl != nullptr);
		this->impl->texture = texture;
	}

	bool MaterialLayer::hasTexture() const 
	{
		assert(this->impl != nullptr);
		return this->impl->texture != nullptr;
	}
}}


// Material implementation
namespace exeng { namespace graphics {

	static const int LayerCount = 4;
    
	struct Material::Private 
	{
		std::string name;
        const MaterialFormat *format = nullptr;
		const ShaderProgram *shaderProgram = nullptr;
        MaterialLayer layers[LayerCount];
        HeapBuffer buffer;

        Private() 
        {
            std::memset(layers, 0, sizeof(layers));
        }
        
		template<typename Type>
		void fillBuffer(void* bufferData, int dimension) {
			Type* data = (Type*)bufferData;

			for (int i=0; i<dimension; i++) {
				data[i] = Type(0);
			}
		}

		void fillBuffer(std::uint8_t *bufferData, DataType::Enum dataType, int dimension) 
		{
			if (dataType == DataType::Float32) {
				fillBuffer<float>(bufferData, dimension);
			} else if (dataType == DataType::Int32) {
				fillBuffer<std::int32_t>(bufferData, dimension);
			} else {
				throw std::runtime_error("Material::fillBufferWithZero: 32-bit floating-point and integer");
			}
		}

		/**
		 * @brief Fill the internal data of the material with zero's
		 */
		void fill() 
		{
			std::uint8_t *bufferData = (std::uint8_t*) this->buffer.getDataPtr();

			for (int i=0; i<this->format->getAttribCount(); i++) {
				const MaterialAttrib *attrib = this->format->getAttrib(i);
				const int offset = this->format->getOffset(i);

				this->fillBuffer(&bufferData[offset], attrib->dataType, attrib->dimension);
			}
		}
	};
    
	Material::Material(const MaterialFormat *format) 
    {
        this->impl = new Material::Private();
        this->impl->format = format;
        
        if (this->getFormat()) {
            this->impl->buffer.allocate(this->impl->format->getSize());
            this->impl->fill();
        }
    }

	Material::Material(const MaterialFormat *format, const std::string &name)
    {
        this->impl = new Material::Private();
        this->impl->format = format;
        
        if (this->getFormat()) {
            this->impl->buffer.allocate(this->impl->format->getSize());
            this->impl->fill();
        }
        
        this->setName(name);
    }
	
	Material::~Material() 
    {
		boost::checked_delete(this->impl);
	}
	
	void Material::setAttribute(const int index, const void* data, const int size)
    {
        assert(this->impl);
        
#if defined(EXENG_DEBUG)
        if (!this->getFormat()) {
            throw std::runtime_error("Material::setAttribute: The MaterialFormat instance is a nullptr.");
        }
#endif
        int offset = this->getFormat()->getOffset(index);
        std::uint8_t* materialData = (std::uint8_t*)this->impl->buffer.getDataPtr();
        
        std::memcpy(materialData + offset, data, this->getFormat()->getAttrib(index)->getSize());
    }
        
    void Material::getAttribute(const int index, void* data, const int size) const 
    {
        assert(this->impl);

#if defined(EXENG_DEBUG)
        if (!this->getFormat()) {
            throw std::runtime_error("Material::setAttribute: The MaterialFormat instance is a nullptr.");
        }
#endif
        int offset = this->getFormat()->getOffset(index);
        std::uint8_t* materialData = (std::uint8_t*)this->impl->buffer.getDataPtr();
        
        std::memcpy(data, materialData + offset, this->getFormat()->getAttrib(index)->getSize());
    }
	
	std::string Material::getName() const 
	{
		assert(this->impl != nullptr);
		return this->impl->name;
	}

	void Material::setName(const std::string& name) 
    {
		assert(this->impl != nullptr);
		this->impl->name = name;
	}
    
	MaterialLayer* Material::getLayer(int index) 
    {
		assert(this->impl != nullptr);

#ifdef EXENG_DEBUG
		if (index < 0 || index >= LayerCount) {
			throw std::out_of_range("Material::getLayer: Index out of range.");
		}
#endif

		return &this->impl->layers[index];
	}
	
	const MaterialLayer* Material::getLayer(int index) const 
	{
		assert(this->impl != nullptr);

#ifdef EXENG_DEBUG
		if (index < 0 || index >= LayerCount) {
			throw std::out_of_range("Material::getLayer: Index out of range.");
		}
#endif

		return &this->impl->layers[index];
	}

	TypeInfo Material::getTypeInfo() const 
	{
		assert(this->impl != nullptr);
    
		return TypeInfo(typeid(Material));
	}

	const int Material::getLayerCount() 
    {
		return LayerCount;
	}

	void Material::setShaderProgram(const ShaderProgram *shader) 
    {
		assert(this->impl != nullptr);
    
		this->impl->shaderProgram = shader;
	}

	const ShaderProgram* Material::getShaderProgram() const 
	{
		assert(this->impl != nullptr);
    
		return this->impl->shaderProgram;
	}

	bool Material::checkTextureType(const TypeInfo &textureTypeInfo) const 
	{
		assert(this->impl != nullptr);
    
		const MaterialLayer *layer = nullptr;
    
		for (int i=0; i<this->getLayerCount(); ++i ) {
			layer = this->getLayer(i);
        
			if (layer->hasTexture() == true) {
				if (layer->getTexture()->getTypeInfo() != textureTypeInfo) {
					return false;
				}
			}
		}
    
		return true;
	}
	
	const MaterialFormat* Material::getFormat() const
	{
        assert(this->impl != nullptr);
        
        return this->impl->format;
    }
	
	bool Material::isSerializable() const 
	{
        assert(this->impl != nullptr);
        
        return false;
    }
    
    void Material::serialize(exeng::io::Stream *out) const 
    {
        assert(this->impl != nullptr);
        
    }
    
    bool Material::isDeserializable() const 
    {
        assert(this->impl != nullptr);
        
        return false;
    }
    
    void Material::deserialize(const exeng::io::Stream *inStream)  
    {
        assert(this->impl != nullptr);
    }
}}
