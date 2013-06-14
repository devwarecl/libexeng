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
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>

#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/Texture.hpp>

namespace exeng {
    namespace graphics {
        struct MaterialLayer::Private {
            Texture* textureMap;
            
            Private() {
                this->textureMap = nullptr;
            }
        };
        
        
        MaterialLayer::MaterialLayer() : impl(nullptr) {
            this->impl = new MaterialLayer::Private();
        }
        
            
        MaterialLayer::~MaterialLayer() {
            boost::checked_delete(this->impl);
        }
        
        
        const Texture* MaterialLayer::getTexture() const {
            assert(this->impl != nullptr);
            return this->impl->textureMap;
        }
        
        
        Texture* MaterialLayer::getTexture() {
            assert(this->impl != nullptr);
            return this->impl->textureMap;
        }
        
        
        void MaterialLayer::setTexture(Texture* tex) {
            assert(this->impl != nullptr);
            this->impl->textureMap = tex;
        }


        bool MaterialLayer::operator== (const MaterialLayer& other) const {
            assert(this->impl != nullptr);
            return this->impl->textureMap == other.impl->textureMap;
        }

        
        bool MaterialLayer::operator!= (const MaterialLayer& other) const {
            assert(this->impl != nullptr);
            return ! (*this == other);
        }


        MaterialLayer& MaterialLayer::operator= (const MaterialLayer& other) {
            assert(this->impl != nullptr);
            this->impl->textureMap = other.impl->textureMap;
            return *this;
        }
    }
}


// Implementacion del material
namespace exeng {
    namespace graphics {
        using namespace exeng::math;
        
        /**
         *  @brief La cantidad maxima de capas de textura soportadas por un material
         */
        static const int LayerCount = 8;
        
        /**
         *  @brief Atributos y funciones privadas del material
         */
        struct Material::Private {
            std::string name;
            Color ambient, diffuse, specular, emissive;
            float shininess;
            MaterialLayer layers[LayerCount];
            
            Private() {
                this->ambient.set(0.8f, 0.8f, 0.8f, 1.0f);
                this->diffuse.set(0.2f, 0.2f, 0.2f, 1.0f);
                this->specular.set(0.0f, 0.0f, 0.0f, 1.0f);
                this->emissive.set(0.0f, 0.0f, 0.0f, 1.0f);
                this->shininess = 0.0;
            }
        };
        
        
        Material::Material()  {
            this->impl = new Material::Private();
        }

        
        Material::Material(const Material& Other) {
            assert(this->impl != NULL);

            *this = Other;
        }
        
        
        Material::~Material() {
            boost::checked_delete(this->impl);
        }

        
        void Material::setAmbient( const Color &color ) {
            assert(this->impl != NULL);
            this->impl->ambient = color;
        }
        
        
        void Material::setDiffuse( const Color &color ) {
            assert(this->impl != NULL);
            this->impl->diffuse = color;
        }
        
        
        void Material::setSpecular( const Color &color) {
            assert(this->impl != NULL);
            this->impl->specular = color;
        }
        
        
        void Material::setEmissive( const Color &color ) {
            assert(this->impl != NULL);
            this->impl->emissive = color;
        }
        
        
        void Material::setShininess( float Value) {
            assert(this->impl != NULL);
            this->impl->shininess = Value;
        }
        

        Color Material::getAmbient() const {
            assert(this->impl != NULL);
            return this->impl->ambient;
        }
        
        
        Color Material::getDiffuse() const {
            assert(this->impl != NULL);
            return this->impl->diffuse;
        }
        
        
        Color Material::getSpecular() const {
            assert(this->impl != NULL);
            return this->impl->specular;
        }
        
        
        Color Material::getEmissive() const {
            assert(this->impl != NULL);
            return this->impl->emissive;
        }
        
        
        float Material::getShininess() const {
            assert(this->impl != NULL);
            return this->impl->shininess;
        }
        
        
        std::string Material::getName() const {
            assert(this->impl != NULL);
            return this->impl->name;
        }

        
        void Material::setName(const std::string& name) {
            assert(this->impl != NULL);
            this->impl->name = name;
        }
            
        
        MaterialLayer& Material::getLayerRef(int index) {
            assert(this->impl != NULL);

#ifdef EXENG_DEBUG
            if (index >= LayerCount)
                throw std::out_of_range("");
#endif

            return this->impl->layers[index];
        }


        const MaterialLayer& Material::getLayerRef(int index) const {
            assert(this->impl != NULL);

#ifdef EXENG_DEBUG
            if (index >= LayerCount) {
                throw std::out_of_range("");
			}
#endif

            return this->impl->layers[index];
        }


        Material* Material::clone() const {
            Material* result = new Material();
            result->assign(*this);
            return result;
        }


        bool Material::equals(const Object &other) const {
            if (this->getTypeInfo() != other.getTypeInfo()) {
                return false;
            }

            auto &otherMaterial = static_cast<const Material&>(other);

            if (this != &otherMaterial) {
                Material::Private *impl = NULL, *otherImpl = NULL;

                // Sacar los objetos de implementacion
                // Asi nos ahorramos una indireccion, y mayor eficiencia en entornos
                // de depuracion
                impl = this->impl;
                otherImpl = otherMaterial.impl;

                // Comparar las componetes de color
                if (impl->ambient != otherImpl->ambient) return false;
                if (impl->diffuse != otherImpl->diffuse) return false;
                if (impl->specular != otherImpl->specular) return false;
                if (impl->emissive != otherImpl->emissive) return false;
                if (impl->shininess != otherImpl->shininess) return false;

                // Comparar las capas de textura
                for (int i=0; i<exeng::graphics::LayerCount; ++i) {
                    if ( impl->layers[i] != otherImpl->layers[i])
                        return false;
                }
            }

            return true;
        }

        
        bool Material::lesserThan(const Object& other) const {
            if (other.getTypeInfo() != this->getTypeInfo()) {
                throw std::bad_cast();
            }

            auto &otherMaterial = static_cast<const Material&>(other);

            return (this->getName().compare(otherMaterial.getName()) < 0);
        }

        
        void Material::assign(const Object& other) {
            if (other.getTypeInfo() != this->getTypeInfo()) {   
                throw std::bad_cast();
            }

            auto &otherMaterial = static_cast<const Material&>(other);

            *this->impl = *otherMaterial.impl;
        }
        

        TypeInfo Material::getTypeInfo() const {
            return TypeInfo(typeid(Material));
        }


        const int Material::getLayerCount() {
            return LayerCount;
        }
    }
}
