/**
 * @file 
 * @brief Define the VertexFormat structure.
 * @todo Make the VertexFormat structure a enumeration. I think it's a more 
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
#include <exeng/math/TVector.hpp>

namespace exeng { namespace graphics {

    /**
     * @brief VertexField enumeration
     */
    struct VertexAttrib : public Enum {
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
    struct VertexField {
        VertexAttrib::Enum attribute;   //! The attribute
        int count;                      //! The dimension
        DataType dataType;              //! The data type for the vertex field.
        
        VertexField() : attribute(VertexAttrib::Unused), count(0), dataType(DataType::Float32) {
        }
                
        VertexField(VertexAttrib::Enum attrib_, int count_, DataType dataType_) : attribute(attrib_), count(count_),  dataType(dataType_) {
        }
        
        /**
         * @brief Get the size, in bytes, of the field.
         */
        int getSize() const {
            return this->count * this->dataType.getSize();
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
    struct EXENGAPI VertexFormat {
    public:
        static const int FieldCount = 16;
        static const int InvalidOffset = -1;
        
        VertexField fields[FieldCount];
        VertexPackaging::Enum packaging;
        
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
        
        /**
         * Vertex with a 3D coordinate, normal vector and a single-unit 2D texture coordinates. All
         * values as floats.
         */
        static VertexFormat makeVertex();
        
        /**
         * Vertex with a 3D coordinate, normal vector and a single-unit 2D texture coordinates. All
         * values as floats.
         */
        static VertexFormat makeVertex2D();
    };
    
    struct Vertex {
        exeng::math::Vector3f coord;
        exeng::math::Vector3f normal;
        exeng::math::Vector2f texCoord;
    };
    
    struct Vertex2D {
        exeng::math::Vector3f coord;
        exeng::math::Vector2f texCoord;
    };
}}

#endif  //__EXENG_GRAPHICS_VERTEXFORMAT_HPP__
