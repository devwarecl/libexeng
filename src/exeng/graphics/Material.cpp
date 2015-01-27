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

using namespace exeng;

namespace exeng { namespace graphics {

	struct MaterialLayer::Private {
		Texture* texture = nullptr;
	};
    
	MaterialLayer::MaterialLayer() : impl(nullptr) {
        this->impl = new MaterialLayer::Private();
    }

	MaterialLayer::~MaterialLayer() {
		boost::checked_delete(this->impl);
	}

	const Texture* MaterialLayer::getTexture() const {
		assert(this->impl != nullptr);
		return this->impl->texture;
	}

	Texture* MaterialLayer::getTexture() {
		assert(this->impl != nullptr);
		return this->impl->texture;
	}
    
	void MaterialLayer::setTexture(Texture* texture) {
		assert(this->impl != nullptr);
		this->impl->texture = texture;
	}

	bool MaterialLayer::hasTexture() const {
		assert(this->impl != nullptr);
		return this->impl->texture != nullptr;
	}
}}


// Material implementation
namespace exeng { namespace graphics {

	static const int LayerCount = 4;

    /*
	// Holds the raw value for a property
	struct PropertyValue {    
		// Big enough to hold a four dimensional vector of doubles
		uint8_t rawData[32];
    
		// Used for error checking
		TypeInfo typeInfo;
    
		inline PropertyValue() : typeInfo( TypeId<void>() ) {
			::memset(rawData, sizeof(rawData), 0);
		}
    
		inline PropertyValue(const TypeInfo &info) : typeInfo(info) {
			::memset(rawData, sizeof(rawData), 0);
		}
	    	
		template<typename ValueType>
		inline bool checkType() const {
			return typeInfo == TypeId<ValueType>();
		}
		
		template<typename ValueType>
		inline void setValue( const ValueType &value ) {
#if defined(EXENG_DEBUG)
			if (!this->checkType<void>() &&  !this->checkType<ValueType>()) {
				throw std::runtime_error("PropertyMap::setValue: The types doesn't coincides.");
			}
#endif
			*reinterpret_cast<ValueType*>(this->rawData) = value;
		}
		
		template<typename ValueType>
		inline ValueType getValue() const {
#if defined(EXENG_DEBUG)
			if (this->checkType<ValueType>() == false) {
				throw std::runtime_error("PropertyMap::setValue: The types doesn't coincides.");
			}
#endif
			return *reinterpret_cast<const ValueType*>(this->rawData);
		}
	};

	template<typename ValueType>
	inline PropertyValue makePropertyValue(const ValueType &value) {
		PropertyValue propertyValue( TypeId<ValueType>() );
		propertyValue.setValue(value);
    
		return propertyValue;
	}

	typedef std::map<std::string, PropertyValue> PropertyMap;
	typedef PropertyMap::iterator PropertyMapIt;
    */
    
	struct Material::Private 
	{
		std::string name;
        const MaterialFormat *format = nullptr;
		const ShaderProgram *shaderProgram = nullptr;
        MaterialLayer layers[LayerCount];
        HeapBuffer buffer;
	};
    
	Material::Material(const MaterialFormat *format) 
    {
        this->impl = new Material::Private();
        this->impl->format = format;
        this->impl->buffer.allocate(this->impl->format->getSize());
    }

	Material::Material(const MaterialFormat *format, const std::string &name)
    {
        this->impl = new Material::Private();
        this->impl->format = format;
        this->impl->buffer.allocate(this->impl->format->getSize());
        this->setName(name);
    }
	
	Material::~Material() 
    {
		boost::checked_delete(this->impl);
	}
	
	void Material::setAttribute(const int index, const void* data, const int size)
    {
        assert(this->impl);
        
        int offset = this->getFormat()->getOffset(index);
        std::uint8_t* materialData = (std::uint8_t*)this->impl->buffer.getDataPtr();
        
        std::memcpy(materialData + offset, data, this->getFormat()->getAttrib(index)->getSize());
    }
        
    void Material::getAttribute(const int index, void* data, const int size) const 
    {
        assert(this->impl);
        
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
        return this->impl->format;
    }
	
	bool Material::isSerializable() const 
	{
        return false;
    }
    
    void Material::serialize(exeng::io::Stream *out) const {}
    
    bool Material::isDeserializable() const 
    {
        return false;
    }
    
    void Material::deserialize(const exeng::io::Stream *inStream)  {}
}}
