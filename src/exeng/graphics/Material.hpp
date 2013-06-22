/**
 * @file Material.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_MATERIAL_HPP__
#define __EXENG_GRAPHICS_MATERIAL_HPP__

#include <vector>
#include <exeng/Object.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/graphics/Color.hpp>

namespace exeng {
	namespace graphics {
        class EXENGAPI Texture;
        
        /**
         * @brief Material Layer. Holds a texture, and associated 
         */
        class EXENGAPI MaterialLayer {
        public:
            MaterialLayer();
            ~MaterialLayer();
            
            /**
             * @brief Get the texture of the material.
             */
            const Texture* getTexture() const;
            
            /**
             * @brief Get the texture of the material.
             */
            Texture* getTexture();
            
            /**
             * @brief Set the currently used texture
             */
            void setTexture(Texture* texture);
            
            /**
             * @brief Check if the current material layer has a texture.
             */
            bool hasTexture() const;
            
        private:
            struct Private;
            Private *impl;
        };
        
        
        /**
         * @brief Describes the visual appearance of the objects.
         * @note Class interface subject to change.
         */
	    class EXENGAPI Material : public Object {
        public:
            Material();
            virtual ~Material();
            
            void setProperties(const std::vector< std::pair<std::string, TypeInfo> >  &properties);
            
            std::vector<std::string> getProperties() const;
            
            void setPropertyValue(const std::string &name, float value);
            void setPropertyValue(const std::string &name, const exeng::math::Vector2f &value);
            void setPropertyValue(const std::string &name, const exeng::math::Vector3f &value);
            void setPropertyValue(const std::string &name, const exeng::math::Vector4f &value);
            
            float getPropertyValueFloat(const std::string &name) const;
            exeng::math::Vector2f getPropertyValueVector2f(const std::string &name) const;
            exeng::math::Vector3f getPropertyValueVector3f(const std::string &name) const;
            exeng::math::Vector4f getPropertyValueVector4f(const std::string &name) const;
            
            std::string getName() const;
            void setName(const std::string& name);
            
            MaterialLayer* getLayer(int index);
            const MaterialLayer* getLayer(int index) const;
            
            virtual TypeInfo getTypeInfo() const;
            
        public:
            static const int getLayerCount();
            
        private:
            struct Private;
            Private *impl;
	    };
	}
}

#endif
