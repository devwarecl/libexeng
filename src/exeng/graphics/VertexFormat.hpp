/**
 * @file 
 * @brief Define the VertexFormat 
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
#include <vector>
#include <numeric>

#include <exeng/Config.hpp>
#include <exeng/DataType.hpp>

namespace exeng {
    namespace graphics {
        /**
         * @brief VertexField enumeration
         */
        enum class VertexAttrib {
            Position,
            Color,
            Normal,
            TexCoord
        };
        
        /**
         * @brief The VertexField struct
         */
        struct VertexField {
            VertexAttrib attribute;  //! The attribute
            int count;                  //! The dimension
            DataType dataType;          //! The data type for the vertex field.
            
            inline VertexField() {
            }
            
            inline VertexField(VertexAttrib attrib, int count, DataType dataType) {
                this->attribute = attrib;
                this->count = count;
                this->dataType = dataType;
            }
            
            inline int getSize() const {
                return this->count * this->dataType.getSize();
            }
        };
        
        /**
         * @brief Dynamic array of VertexField.
         */
        typedef std::vector<VertexField> VertexFieldVector;
         
        /**
         * @brief Describe the format of a vertex. Used in the VertexBuffer class.
         */
        struct VertexFormat {
            VertexFieldVector fields;
            
            /**
             * @brief Get the size, in bytes, for each vertex of this format.
             */
            int getSize() const;
        };
        
        
        inline int VertexFormat::getSize() const {
            int size = 0;
            
            for (auto &field : this->fields) {
                size += field.getSize();
            }
            
            return size;
        }
    }
}

#endif  //__EXENG_GRAPHICS_VERTEXFORMAT_HPP__
