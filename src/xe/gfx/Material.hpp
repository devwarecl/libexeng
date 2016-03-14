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

#include <cassert>
#include <vector>
#include <tuple>
#include <memory>
#include <xe/Object.hpp>
#include <xe/Vector.hpp>
#include <xe/DataType.hpp>
#include <xe/gfx/Forward.hpp>

#if defined(EXENG_DEBUG)
#  include <sstream>
#endif

namespace xe { namespace gfx {

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
        
        int getSize() const;
        
        MaterialAttrib();
        
        MaterialAttrib (std::string name, 
            DataType::Enum dataType = DataType::Float32, 
            int dimension = 4, 
            int alignment = 1);
        
        bool operator== (const MaterialAttrib &other) const;
        bool operator!= (const MaterialAttrib &other) const;
    };
    
	struct MaterialLayerDesc {
		std::string name;
	};

    class MaterialFormat {
    public:
        MaterialFormat();
        
        MaterialFormat(const std::vector<MaterialAttrib> &attribs);
        
        int getSize() const;
        
        int getOffset(int attribIndex) const;
        
        int getAttribCount() const;
        
        const MaterialAttrib* getAttrib(const int index) const;
        
		const int getAttribIndex(const std::string &name) const;

		const MaterialAttrib* getAttrib(const std::string &name) const;
        
		std::string getLayerName(const int index) const;

		bool operator== (const MaterialFormat &other) const;
        
        bool operator!= (const MaterialFormat &other) const;
		
    private:
        std::vector<MaterialAttrib> attribs;
		std::vector<MaterialLayerDesc> layerdecs;
    };
    
    /**
     * @brief Describes the visual appearance of the objects.
     * @note Class interface subject to change.
     */
    class EXENGAPI Material : public Object {
    public:
        explicit Material(const MaterialFormat *format);
        explicit Material(const MaterialFormat *format, const std::string &name);
        
        virtual ~Material();
        
        const MaterialFormat* getFormat() const;
        
        template<typename ValueType>
        Material* setAttribute(const int index, const ValueType &value) 
        {
            assert(sizeof(ValueType) == this->getFormat()->getAttrib(index)->getSize());
            
            this->setAttribute(index, &value, sizeof(value));

			return this;
        }
        
        template<typename ValueType>
        ValueType getAttribute(const int index) const
        {
            assert(sizeof(ValueType) == this->getFormat()->getAttrib(index)->getSize());
            
            ValueType value;
            
            this->getAttribute(index, &value, sizeof(value));
            
            return value;
        }
        
		template<typename ValueType>
        Material* setAttribute(const std::string &name, const ValueType &value) 
        {
            assert(sizeof(ValueType) == this->getFormat()->getAttrib(name)->getSize());
            
			const int index = this->getFormat()->getAttribIndex(name);
            this->setAttribute(index, &value, sizeof(value));

			return this;
        }
        
        template<typename ValueType>
        ValueType getAttribute(const std::string &name) const
        {
            assert(sizeof(ValueType) == this->getFormat()->getAttrib(name)->getSize());
            
			const int index = this->getFormat()->getAttribIndex(name);

            ValueType value;
            this->getAttribute(index, &value, sizeof(value));
            
            return value;
        }
        
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
        virtual void serialize(xe::io::Stream *outStream) const;
        
        virtual bool isDeserializable() const;
        virtual void deserialize(const xe::io::Stream *inStream);
        
    private:
        struct Private;
        Private *impl = nullptr;
    };

	typedef std::unique_ptr<Material> MaterialPtr;
}}


// MaterialAttrib implementation
namespace xe { namespace gfx {

    inline MaterialAttrib::MaterialAttrib() 
    {
        
    }
    
    inline MaterialAttrib::MaterialAttrib (std::string name, DataType::Enum dataType, int dimension, int alignment)
    {
        this->name = name;
        this->dataType = dataType;
        this->dimension = dimension;
        this->alignment = alignment;    
    }
    
    inline int MaterialAttrib::getSize() const 
    {
        int size = dimension * DataType::getSize(this->dataType);
        return size + size%alignment;
    }
    
    inline bool MaterialAttrib::operator== (const MaterialAttrib &other) const
    {
        if (name != other.name) {
            return false;
        }
        
        if (dataType != other.dataType) {
            return false;
        }
        
        if (dimension != other.dimension) {
            return false;
        }
        
        if (alignment != other.alignment) {
            return false;
        }
        
        return true;
    }
    
    inline bool MaterialAttrib::operator!= (const MaterialAttrib &other) const
    {
        return ! (*this == other);
    }  
}}


namespace xe { namespace gfx {
    inline MaterialFormat::MaterialFormat() {}
    
    inline MaterialFormat::MaterialFormat(const std::vector<MaterialAttrib> &attribs) 
    {
        this->attribs = attribs;
    }
    
    inline int MaterialFormat::getSize() const
    {
        return this->getOffset(this->getAttribCount());
    }
    
    inline int MaterialFormat::getOffset(int attribIndex) const
    {
        int offset = 0;
        
        for (int i=0; i<attribIndex; i++) {
            offset += this->attribs[i].getSize();
        }
        
        return offset;
    }
    
    inline int MaterialFormat::getAttribCount() const 
    {
        return this->attribs.size();
    }
    
    inline const MaterialAttrib* MaterialFormat::getAttrib(const int index) const 
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
    
    inline const int MaterialFormat::getAttribIndex(const std::string &name) const 
    {
        for (int i=0; i<this->getAttribCount(); ++i) {
            if (this->getAttrib(i)->name == name) {
                return i;
            }
        }

        return -1;
    }

    inline const MaterialAttrib* MaterialFormat::getAttrib(const std::string &name) const {
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
    
    inline bool MaterialFormat::operator== (const MaterialFormat &other) const {
        if (this->getAttribCount() != other.getAttribCount()) {
            return false;
        }
        
        for (int i=0; i<this->getAttribCount(); i++) {
            if (this->attribs[i] != other.attribs[i]) {
                return false;
            }
        }
        
        return true;
    }

	inline bool MaterialFormat::operator!= (const MaterialFormat &other) const {
		return !(*this == other);
	}

	inline std::string MaterialFormat::getLayerName(const int index) const {
		assert(index >= 0);

		if (index >= static_cast<int>(layerdecs.size())) {
			return "";

		} else {
			return layerdecs[index].name;
		}
	}
}}

#endif
