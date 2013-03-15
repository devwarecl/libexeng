
#include "Material.hpp"
#include "Texture.hpp"

#include <cassert>
#include <stdexcept>
#include <cstring>
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>

namespace exeng
{
    namespace graphics
    {
        struct MaterialLayer::Private
        {
            Texture* textureMap;

            Private() : textureMap(NULL)
            {}
        };
        
        
        MaterialLayer::MaterialLayer() : impl(NULL)
        {
            this->impl = new MaterialLayer::Private();
        }
        
            
        MaterialLayer::~MaterialLayer()
        {
            boost::checked_delete(this->impl);
        }
        
        
        const Texture* MaterialLayer::getTexture() const
        {
            assert(this->impl != NULL);

            return this->impl->textureMap;
        }
        
        
        Texture* MaterialLayer::getTexture()
        {
            assert(this->impl != NULL);

            return this->impl->textureMap;
        }
        
        
        void MaterialLayer::setTexture(Texture* tex)
        {
            assert(this->impl != NULL);

            this->impl->textureMap = tex;
        }



        bool MaterialLayer::operator== (const MaterialLayer& other) const
        {
            return this->impl->textureMap == other.impl->textureMap;
        }

        
        bool MaterialLayer::operator!= (const MaterialLayer& other) const
        {
            return ! (*this == other);
        }


        MaterialLayer& MaterialLayer::operator= (const MaterialLayer& other)
        {
            this->impl->textureMap = other.impl->textureMap;
            return *this;
        }
    }
    }


    namespace exeng
    {
    namespace graphics
    {
        using namespace exeng::math;

        //! La cantidad maxima de capas de textura soportadas por un material
        static const int LayerCount = 4;
        
        struct Material::Private
        {
            std::string name;
            Vector4f ambient;
            Vector4f diffuse;
            Vector4f specular;
            Vector4f emissive;
            float shininess;
            MaterialLayer layers[LayerCount];
            
            Private()
            {
                this->ambient = Vector4f(0.8f, 0.8f, 0.8f, 1.0f);
                this->diffuse = Vector4f(0.2f, 0.2f, 0.2f, 1.0f);
                this->specular = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
                this->emissive = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
                this->shininess = 0.0;
            }
        };
        
        
        Material::Material() 
        {
            this->impl = new Material::Private();
        }

        
        Material::Material(const Material& Other)
        {
            assert(this->impl != NULL);

            *this = Other;
        }
        
        
        Material::~Material()
        {
            boost::checked_delete(this->impl);
        }

        
        void Material::setAmbient( const exeng::math::Vector4f &color )
        {
            assert(this->impl != NULL);
            this->impl->ambient = color;
        }
        
        
        void Material::setDiffuse( const exeng::math::Vector4f &color )
        {
            assert(this->impl != NULL);
            this->impl->diffuse = color;
        }
        
        
        void Material::setSpecular( const exeng::math::Vector4f &color)
        {
            assert(this->impl != NULL);
            this->impl->specular = color;
        }
        
        
        void Material::setEmissive( const exeng::math::Vector4f &color )
        {
            assert(this->impl != NULL);
            this->impl->emissive = color;
        }
        
        
        void Material::setShininess( float Value)
        {
            assert(this->impl != NULL);
            this->impl->shininess = Value;
        }
        

        exeng::math::Vector4f Material::getAmbient() const
        {
            assert(this->impl != NULL);
            return this->impl->ambient;
        }
        
        
        exeng::math::Vector4f Material::getDiffuse() const
        {
            assert(this->impl != NULL);
            return this->impl->diffuse;
        }
        
        
        exeng::math::Vector4f Material::getSpecular() const
        {
            assert(this->impl != NULL);
            return this->impl->specular;
        }
        
        
        exeng::math::Vector4f Material::getEmissive() const
        {
            assert(this->impl != NULL);
            return this->impl->emissive;
        }
        
        
        float Material::getShininess() const
        {
            assert(this->impl != NULL);
            return this->impl->shininess;
        }
        
        
        std::string Material::getName() const
        {
            assert(this->impl != NULL);
            return this->impl->name;
        }

        
        void Material::setName(const std::string& name)
        {
            assert(this->impl != NULL);
            this->impl->name = name;
        }
            
        
        MaterialLayer& Material::getLayerRef(int index)
        {
            assert(this->impl != NULL);

    #ifdef __EXENG_DEBUG__
            if (index >= LayerCount)
                throw std::out_of_range("");
    #endif

            return this->impl->layers[index];
        }


        const MaterialLayer& Material::getLayerRef(int index) const
        {
            assert(this->impl != NULL);

    #ifdef __EXENG_DEBUG__
            if (index >= LayerCount)
                throw std::out_of_range("");
    #endif

            return this->impl->layers[index];
        }


        Material* Material::clone() const
        {
            Material* result = new Material();
            result->assign(*this);
            return result;
        }


        bool Material::equals(const Object &other) const
        {
            if (this->getTypeInfo() != other.getTypeInfo())
                return false;

            const Material& otherMaterial = static_cast<const Material&>(other);

            if (this != &otherMaterial)
            {
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
                for (int i=0; i<exeng::graphics::LayerCount; ++i)
                {
                    if ( impl->layers[i] != otherImpl->layers[i])
                        return false;
                }
            }

            return true;
        }

        
        bool Material::lesserThan(const Object& other) const
        {
            if (other.getTypeInfo() != this->getTypeInfo())
                throw std::bad_cast();

            const Material& otherMaterial = static_cast<const Material&>(other);

            return (this->getName().compare(otherMaterial.getName()) < 0);
        }

        
        void Material::assign(const Object& other)
        {
            if (other.getTypeInfo() != this->getTypeInfo())
                throw std::bad_cast();

            const Material& otherMaterial = static_cast<const Material&>(other);

            *this->impl = *otherMaterial.impl;
        }
        

        TypeInfo Material::getTypeInfo() const
        {
            return TypeInfo(typeid(Material));
        }


        const int Material::getLayerCount()
        {
            return LayerCount;
        }
    }
}
