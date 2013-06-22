/**
 * @file 
 * @brief 
 */


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

#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/Texture.hpp>

using namespace exeng;
using namespace exeng::math;

namespace exeng {
namespace graphics {
struct MaterialLayer::Private {
    Texture* texture;
    
    Private() : texture(nullptr) {
    }
};


MaterialLayer::MaterialLayer() : impl( new MaterialLayer::Private() ) {
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

}
}

// Material implementation
namespace exeng {
namespace graphics {
using namespace exeng::math;

static const int LayerCount = 4;

// Holds the raw value for a property
struct PropertyValue {    
    // Big enough to hold a four dimensional vector of doubles
    uint8_t rawData[32];    
    
    // Used for error checking
    TypeInfo typeInfo;
    
    inline PropertyValue() : typeInfo( TypeInfo::get<void>() ) {
    }
    
    
    inline PropertyValue(const TypeInfo &info) : typeInfo(info) {
        ::memset(rawData, sizeof(rawData), 0);
    }
    
    
    template<typename ValueType>
    inline bool checkType() const {
        return typeInfo != TypeInfo::get<ValueType>();
    }
    
    
    template<typename ValueType>
    inline void setValue( const ValueType &value ) {
#if defined(EXENG_DEBUG)
        if (this->checkType<ValueType>() == false)
            throw std::runtime_error("PropertyMap::setValue: The types doesn't coincides.");
        }
#endif
        *reinterpret_cast<ValueType*>(this->rawData) = value;
    }
    
    
    template<typename ValueType>
    inline ValueType getValue() const {
#if defined(EXENG_DEBUG)
        if (this->checkType<ValueType>() == false)
            throw std::runtime_error("PropertyMap::setValue: The types doesn't coincides.");
        }
#endif
        return *reinterpret_cast<const ValueType*>(this->rawData);
    }
};


template<typename ValueType>
inline PropertyValue makePropertyValue(const ValueType &value) {
    PropertyValue propertyValue( TypeInfo::get<ValueType>() );
    
    propertyValue.setValue(value);
    
    return propertyValue;
}


typedef std::map<std::string, PropertyValue> PropertyMap;
typedef PropertyMap::iterator PropertyMapIt;

struct Material::Private {
    std::string name;
    PropertyMap properties;
    MaterialLayer layers[LayerCount];
    
    Private() {
    }    
    
    template<typename ValueType>
    void setPropertyValue(const std::string &name, const ValueType &value) {
    }
};


Material::Material() : impl(nullptr) {
    this->impl = new Material::Private();
}


Material::~Material() {
    boost::checked_delete(this->impl);
}


void Material::setPropertyValue(const std::string &name, float value) {
    assert( this->impl != nullptr );
    this->impl->properties[name] = makePropertyValue(value);
}


void Material::setPropertyValue(const std::string &name, const Vector2f &value) {
    assert( this->impl != nullptr );
    this->impl->properties[name] = makePropertyValue(value);
}


void Material::setPropertyValue(const std::string &name, const Vector3f &value) {
    assert( this->impl != nullptr );
    this->impl->properties[name] = makePropertyValue(value);
}


void Material::setPropertyValue(const std::string &name, const Vector4f &value) {
    assert( this->impl != nullptr );
    
    this->impl->properties[name] = makePropertyValue(value);
}


float Material::getPropertyValueFloat(const std::string &name) const {
    assert( this->impl != nullptr );
    
    return this->impl->properties[name].getValue<float>();
}


Vector2f Material::getPropertyValueVector2f(const std::string &name) const {
    assert( this->impl != nullptr );
    
    return this->impl->properties[name].getValue<Vector2f>();
}


Vector3f Material::getPropertyValueVector3f(const std::string &name) const {
    assert( this->impl != nullptr );
    
    return this->impl->properties[name].getValue<Vector3f>();
}


Vector4f Material::getPropertyValueVector4f(const std::string &name) const {
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
    return TypeInfo(typeid(Material));
}


const int Material::getLayerCount() {
    return LayerCount;
}


}
}
