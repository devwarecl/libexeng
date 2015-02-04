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
#include <tuple>
#include <exeng/Object.hpp>
#include <exeng/Vector.hpp>
#include <exeng/DataType.hpp>

#if defined(EXENG_DEBUG)
#  include <sstream>
#endif

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
        Private *impl = nullptr;
    };
    
    struct MaterialAttrib 
    {
        std::string name;
        DataType::Enum dataType = DataType::Float32;
        int dimension = 4;
        int alignment = 1;
        
        int getSize() const 
        {
            int size = dimension * DataType::getSize(this->dataType);
            return size + size%alignment;
        }
        
        MaterialAttrib() {}
        
        MaterialAttrib (
            std::string name_, 
            DataType::Enum dataType_ = DataType::Float32, 
            int dimension_ = 4, 
            int alignment_ = 1) : name(name_), dataType(dataType_), dimension(dimension_), alignment(alignment_)
        {}
    };
    
    class MaterialFormat {
    public:
        inline MaterialFormat() {}
        inline MaterialFormat(const std::vector<MaterialAttrib> &attribs_) : attribs(attribs_) {}
        
        inline int getSize() const
        {
            int size = 0;
            
            for (const MaterialAttrib &attrib : this->attribs) {
                size += attrib.getSize();
            }
            
            return size;
        }
        
        inline int getOffset(int attribIndex) const
        {
            int offset = 0;
            
            for (int i=0; i<=attribIndex; i++) {
                offset += this->attribs[i].getSize();
            }
            
            return offset;
        }
        
        inline int getAttribCount() const 
        {
            return this->attribs.size();
        }
        
        inline const MaterialAttrib* getAttrib(const int index) const 
        {
#if defined(EXENG_DEBUG)
			if (index < 0 || index >= this->getAttribCount()) {
				std::stringstream ss;

				ss << "MaterialFormat::getAttrib: ";
				ss << "Index out of bounds: " << index;

				throw std::runtime_error(ss.str());
			}
#endif
            return &this->attribs[index];
        }
        
		inline const int getAttribIndex(const std::string &name) const 
		{
			for (int i=0; i<this->getAttribCount(); ++i) {
				if (this->getAttrib(i)->name == name) {
					return i;
				}
			}

			return -1;
		}

		inline const MaterialAttrib* getAttrib(const std::string &name) const 
		{
#if defined (EXENG_DEBUG)
			const int index = this->getAttribIndex(name);

			if (index == -1) {
				std::stringstream ss;

				ss << "MaterialFormat::getAttrib: ";
				ss << "Unknown attribute name '" << name << "'.";

				throw std::runtime_error(ss.str());
			}
#endif
			return this->getAttrib(this->getAttribIndex(name));
		}

    private:
        std::vector<MaterialAttrib> attribs;
    };
    
    /**
     * @brief Describes the visual appearance of the objects.
     * @note Class interface subject to change.
     */
    class EXENGAPI Material : public Object {
    public:
        Material(const MaterialFormat *format);
        Material(const MaterialFormat *format, const std::string &name);
        
        virtual ~Material();
        
        const MaterialFormat* getFormat() const;
        
        template<typename ValueType>
        void setAttribute(const int index, const ValueType &value) 
        {
            this->setAttribute(index, &value, sizeof(value));
        }
        
        template<typename ValueType>
        ValueType getAttribute(const int index) const
        {
            ValueType value;
            
            this->getAttribute(index, &value, sizeof(value));
            
            return value;
        }
        
		template<typename ValueType>
        void setAttribute(const std::string &name, const ValueType &value) 
        {
			const int index = this->getFormat()->getAttribIndex(name);
            this->setAttribute(index, &value, sizeof(value));
        }
        
        template<typename ValueType>
        ValueType getAttribute(const std::string &name) const
        {
			const int index = this->getFormat()->getAttribIndex(name);

            ValueType value;
            this->getAttribute(index, &value, sizeof(value));
            
            return value;
        }

        void setShaderProgram(const ShaderProgram *shader);
        
        const ShaderProgram* getShaderProgram() const;
        
        std::string getName() const;
        void setName(const std::string& name);
        
        MaterialLayer* getLayer(int index);
        const MaterialLayer* getLayer(int index) const;
        
        bool checkTextureType(const TypeInfo &textureTypeInfo) const;
        
        virtual TypeInfo getTypeInfo() const;
        
        void setAttribute(const int index, const void* data, const int size);
        
        void getAttribute(const int index, void* data, const int size) const;
        
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
        Private *impl = nullptr;
    };
}}

#endif
