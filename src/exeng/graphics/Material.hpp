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
#include <exeng/Vector.hpp>
#include <exeng/graphics/Color.hpp>

namespace exeng { namespace graphics {

    class EXENGAPI Texture;
    class EXENGAPI ShaderProgram;

    /**
     * @brief Material Layer. Holds a texture, and associated state.
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
        Material(const std::string &name);
        virtual ~Material();
        
        void setProperty(const std::string &name, float value);
        void setProperty(const std::string &name, const Vector2f &value);
        void setProperty(const std::string &name, const Vector3f &value);
        void setProperty(const std::string &name, const Vector4f &value);
        
        float getPropertyf(const std::string &name) const;
        Vector2f getProperty2f(const std::string &name) const;
        Vector3f getProperty3f(const std::string &name) const;
        Vector4f getProperty4f(const std::string &name) const;
        
        void setShaderProgram(const ShaderProgram *shader);
        
        const ShaderProgram* getShaderProgram() const;
        
        std::string getName() const;
        void setName(const std::string& name);
        
        MaterialLayer* getLayer(int index);
        const MaterialLayer* getLayer(int index) const;
        
        bool checkTextureType(const TypeInfo &textureTypeInfo) const;
        
        virtual TypeInfo getTypeInfo() const;
        
        int getPropertyNameCount() const;
        std::string getPropertyName(int index) const;
        TypeInfo getPropertyType(int index) const;
        void removeProperty(const std::string &name);
        
    public:
        static const int getLayerCount();
        
        /* Serializable implementation */
    public:
        virtual bool isSerializable() const;
        virtual void serialize(exeng::io::Stream *outStream) const;
        
        virtual bool isDeserializable() const;
        virtual void deserialize(const exeng::io::Stream *inStream);
        
    private:
        struct Private;
        Private *impl;
    };
}}

#endif
