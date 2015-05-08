/**
 * @file 
 * @brief Define the VertexFormat structure.
 * @todo Make the VertexFormat structure a enumeration. Maybe it's a more 
 * elegant solution than relying on a array of structures
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_VERTEXFORMAT_HPP__
#define __EXENG_GRAPHICS_VERTEXFORMAT_HPP__

#include <cstdint>
#include <numeric>

#include <exeng/Enum.hpp>
#include <exeng/Config.hpp>
#include <exeng/DataType.hpp>
#include <exeng/Vector.hpp>

namespace exeng { namespace graphics {

    /**
     * @brief VertexField enumeration
     */
    struct VertexAttrib : public Enum 
	{
        enum Enum {
            Unused,
            Position,
            Color,
            Normal,
            Tangent,
            Binormal,
            TexCoord
        };
        
        const char* str(VertexAttrib::Enum attrib) {
            switch (attrib) {
                case VertexAttrib::Position:    return "Position";
                case VertexAttrib::Color :      return "Color";
                case VertexAttrib::Normal:      return "Normal";
                case VertexAttrib::Tangent:     return "Tangent";
                case VertexAttrib::Binormal:    return "Binormal";
                case VertexAttrib::TexCoord:    return "TexCoord";
                
                default: return "$UNUSED$";
            }
        }
    };
    
    /**
     * @brief Describe a determined field
     */
    struct VertexField 
	{
        VertexAttrib::Enum attribute = VertexAttrib::Unused;    //! The attribute
        int count = 0;                                          //! The dimension
        DataType::Enum dataType = DataType::Float32;            //! The data type for the vertex field.
        
        VertexField() {}

        VertexField(VertexAttrib::Enum attrib_, int count_, DataType::Enum dataType_) 
		{
			this->attribute = attrib_;
			this->count = count_;
			this->dataType = dataType_;
        }
        
        /**
         * @brief Get the size, in bytes, of the field.
         */
        int getSize() const 
		{
            return this->count * DataType::getSize(dataType);
        }
    };
    
    /**
     * @brief Specify the packaging of the vertex data.
     */
    struct VertexPackaging : public Enum {
        enum Enum {
            SingleBuffer,   //! The vertex data is stored on a single buffer
            MultiBuffer     //! The vertex data is stored in multiple buffers (one buffer per field of the vertex format)
        };
    };
    
    /**
     * @brief Describe the format of a vertex. Used in the VertexBuffer class.
     */
    struct VertexFormat {
    public:
        static const int FieldCount = 16;
        static const int InvalidOffset = -1;
        
        VertexField fields[FieldCount];
        VertexPackaging::Enum packaging = VertexPackaging::SingleBuffer;
        
    public:
        VertexFormat();
        
        /**
         * @brief Get the size, in bytes, for each vertex of this format.
         */
        int getSize() const;
        
        /**
         * @brief Get the offset for the specified attrib.
         *
         * Computes the offset, in bytes, of the storage of the specified vertex attribute. If is not found, 
         * returns VertexFormat::InvalidOffset. This function only make sense when the packaing of the Vertex Data
         * is VertexPackaging::SingleBuffer. Else, returns VertexFormat::InvalidOffset.
         *
         */
        int getAttribOffset(VertexAttrib::Enum attrib) const;
        
        /**
         * @brief Get the VertexField object containing the specified Vertex Attribute.
         */
        VertexField getAttrib(VertexAttrib::Enum attrib) const;
    };
    
	/**
     * @brief Vertex with a 3D coordinate, normal vector and a single-unit 2D texture coordinate. All
     * values as floats.
     */
    struct Vertex 
	{
        Vector3f coord;
        Vector3f normal;
        Vector2f texCoord;

		static VertexFormat format();
    };
    
    struct Vertex2
	{
        Vector3f coord;
        Vector2f texCoord;

		static VertexFormat format();
    };

    inline VertexFormat::VertexFormat() 
	{
        this->packaging = VertexPackaging::SingleBuffer;
        
        for (int i=0; i<VertexFormat::FieldCount; ++i) {
            this->fields[i] = VertexField(VertexAttrib::Unused, 0, DataType::Float32);
        }
    }
    
    inline int VertexFormat::getSize() const 
	{
        int size = 0;
                
        for (auto &field : this->fields) {
            size += field.getSize();
        }
                
        return size;
    }
    
    inline int VertexFormat::getAttribOffset(VertexAttrib::Enum attrib) const 
	{
        if (this->packaging == VertexPackaging::MultiBuffer) {
            return VertexFormat::InvalidOffset;
        }
        
        int offset = 0;
        
        for (const VertexField &field : this->fields) {
            if (field.attribute == attrib || field.attribute == VertexAttrib::Unused) {
                break;
            }

			offset += field.getSize();
        }
        
        return offset;
    }
    
    inline VertexField VertexFormat::getAttrib(VertexAttrib::Enum attrib) const 
	{
        VertexField resultField = VertexField(VertexAttrib::Unused, 0, DataType::Float32);
        
        for (const VertexField &field : this->fields) {
            if (field.attribute == VertexAttrib::Unused) {
                break;
            }
            
            if (field.attribute == attrib) {
                resultField = field;
            }
        }
        
        return resultField;
    }
    
    inline VertexFormat Vertex::format() 
	{
        VertexFormat format;
        
		format.fields[0] = {VertexAttrib::Position, 3, DataType::Float32};
		format.fields[1] = {VertexAttrib::Normal, 3, DataType::Float32};
		format.fields[2] = {VertexAttrib::TexCoord, 2, DataType::Float32};
        
        return format;
    }
    
    inline VertexFormat Vertex2::format() 
	{
        VertexFormat format;
    
		format.fields[0] = {VertexAttrib::Position, 3, DataType::Float32};
		format.fields[1] = {VertexAttrib::TexCoord, 2, DataType::Float32};
        
        return format;
    }
}}

#endif  //__EXENG_GRAPHICS_VERTEXFORMAT_HPP__
