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

#ifndef exeng_graphics_vertexformat
#define exeng_graphics_vertexformat

#include "../Config.hpp"
#include "../DataType.hpp"
#include <cstdint>
#include <vector>
#include <numeric>

namespace exeng {
    namespace graphics {
        /**
         * @brief VertexField enumeration
         */
        enum class VertexAttribute {
            Position,
            Color,
            Normal,
            TexCoord
        };
        
        /**
         * @brief The VertexField struct
         */
        struct VertexField {
            VertexAttribute attribute;  //! The attribute
            int count;                  //! The dimension
            DataType dataType;          //! The data type for the vertex field.
        };
        
        /**
         * @brief Dynamic array of VertexField.
         */
        typedef std::vector<VertexField> VertexFieldVector;
        
        /**
         * @brief Iterator for the VertexFieldVector.
         */
        typedef VertexFieldVector::iterator VertexFieldVectorIt;
        
        
        /**
         * @brief Describe the format of a vertex. Used in the VertexBuffer class.
         */
        struct VertexFormat {
            VertexFieldVector fields;
            
            int getSize() const;
        };
        
        
        inline int VertexFormat::getSize() const {
            return std::accumulate(fields.begin(), fields.end(), 0, [](int prev, const VertexField &in) {
                return prev + in.dataType.getSize();
            });
        }
    }
}

#endif  //__EXENG_GRAPHICS_VERTEXFORMAT_HPP__
