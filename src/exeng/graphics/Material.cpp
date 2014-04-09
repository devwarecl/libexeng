/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <cassert>
#include <stdexcept>
#include <cstring>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>
#include <boost/lexical_cast.hpp>

#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/Texture.hpp>
#include <exeng/io/Stream.hpp>

using namespace exeng;
using namespace exeng::math;

namespace exeng { namespace graphics {

	struct MaterialLayer::Private {
		Texture* texture;
		Private() : texture(nullptr) {}
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
	using namespace exeng::math;

	static const int LayerCount = 4;

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

	struct Material::Private {
		std::string name;
		PropertyMap properties;
		MaterialLayer layers[LayerCount];
		const ShaderProgram *shaderProgram;
    
		Private() : shaderProgram(nullptr) {}
		
		PropertyMap::const_iterator getPosition(int index) const {
			PropertyMap::const_iterator it = this->properties.end();
        
			int i=0;
            
			for(it=this->properties.begin(); it!=this->properties.end(); ++it ) {
				if (index == i) {
					break;
				}
				++i;
			}
        
			return it;
		}
    
	};


	Material::Material() : impl(nullptr) {
		this->impl = new Material::Private();
	}

	
	Material::Material(const std::string &name) : impl(nullptr) {
        this->impl = new Material::Private();
        this->setName(name);
    }
	
    
	Material::~Material() {
		boost::checked_delete(this->impl);
	}


	void Material::setProperty(const std::string &name, float value) {
		assert( this->impl != nullptr );
		this->impl->properties[name] = makePropertyValue(value);
	}


	void Material::setProperty(const std::string &name, const Vector2f &value) {
		assert( this->impl != nullptr );
		this->impl->properties[name] = makePropertyValue(value);
	}


	void Material::setProperty(const std::string &name, const Vector3f &value) {
		assert( this->impl != nullptr );
		this->impl->properties[name] = makePropertyValue(value);
	}


	void Material::setProperty(const std::string &name, const Vector4f &value) {
		assert( this->impl != nullptr );
    
		this->impl->properties[name] = makePropertyValue(value);
	}


	float Material::getPropertyf(const std::string &name) const {
		assert( this->impl != nullptr );
    
		return this->impl->properties[name].getValue<float>();
	}


	Vector2f Material::getProperty2f(const std::string &name) const {
		assert( this->impl != nullptr );
    
		return this->impl->properties[name].getValue<Vector2f>();
	}


	Vector3f Material::getProperty3f(const std::string &name) const {
		assert( this->impl != nullptr );
    
		return this->impl->properties[name].getValue<Vector3f>();
	}


	Vector4f Material::getProperty4f(const std::string &name) const {
		assert( this->impl != nullptr );
    
		return this->impl->properties[name].getValue<Vector4f>();
	}


	std::string Material::getName() const {
		assert(this->impl != nullptr);
		return this->impl->name;
	}


	void Material::setName(const std::string& name) {
		assert(this->impl != nullptr);
		this->impl->name = name;
	}
    

	MaterialLayer* Material::getLayer(int index) {
		assert(this->impl != nullptr);

	#ifdef EXENG_DEBUG
		if (index < 0 || index >= LayerCount) {
			throw std::out_of_range("Material::getLayer: Index out of range.");
		}
	#endif

		return &this->impl->layers[index];
	}
	
	
	const MaterialLayer* Material::getLayer(int index) const {
		assert(this->impl != nullptr);

	#ifdef EXENG_DEBUG
		if (index < 0 || index >= LayerCount) {
			throw std::out_of_range("Material::getLayer: Index out of range.");
		}
	#endif

		return &this->impl->layers[index];
	}


	TypeInfo Material::getTypeInfo() const {
		assert(this->impl != nullptr);
    
		return TypeInfo(typeid(Material));
	}


	const int Material::getLayerCount() {
		return LayerCount;
	}


	void Material::setShaderProgram(const ShaderProgram *shader) {
		assert(this->impl != nullptr);
    
		this->impl->shaderProgram = shader;
	}


	const ShaderProgram* Material::getShaderProgram() const {
		assert(this->impl != nullptr);
    
		return this->impl->shaderProgram;
	}


	bool Material::checkTextureType(const TypeInfo &textureTypeInfo) const {
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


	int Material::getPropertyNameCount() const {
		assert(this->impl != nullptr);
    
		return static_cast<int>(this->impl->properties.size());
	}


	std::string Material::getPropertyName( int index ) const {
		assert(this->impl != nullptr);
    
		if (index < 0 || index >= this->getPropertyNameCount()) {
			std::string msg;
        
			msg += "Material::getPropertyName: ";
			msg += "Index is at '" + boost::lexical_cast<std::string>(index) + "', ";
			msg += "but should be in the range [0, ";
			msg += boost::lexical_cast<std::string>(this->getPropertyNameCount() - 1);
			msg += "].";
        
			throw std::runtime_error(msg);
		}
		
		return this->impl->getPosition( index )->first;
	}


	TypeInfo Material::getPropertyType(int index) const {
		assert(this->impl != nullptr);
		return this->impl->getPosition(index)->second.typeInfo;
	}


	void Material::removeProperty(const std::string &name) {
		assert(this->impl != nullptr);
    
		auto &properties = this->impl->properties;
    
		auto it = properties.find(name);
		if (it == properties.end()) {
			std::string msg;
        
			msg += "Material::removeProperty: ";
			msg += "The property named '" + name + " doesn't not exist.";
        
			throw std::runtime_error(msg);
		}
	}
	
	
	bool Material::isSerializable() const {
        return true;
    }
    
    
    void Material::serialize(exeng::io::Stream *out) const {
        // chunk based serialization
    }
    
    
    bool Material::isDeserializable() const {
        return true;
    }
    
    void Material::deserialize(const exeng::io::Stream *inStream) {
        
    }
}}
