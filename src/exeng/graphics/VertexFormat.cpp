/**
 * @file VertexFormat.cpp
 * @brief VertexFormat class implementation.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <exeng/graphics/VertexFormat.hpp>

namespace exeng  { namespace graphics {   
    
    VertexFormat::VertexFormat() {
        this->packaging = VertexPackaging::SingleBuffer;
        
        for (int i=0; i<VertexFormat::FieldCount; ++i) {
            this->fields[i] = VertexField(VertexAttrib::Unused, 0, DataType::Float32);
        }
    }
    
    int VertexFormat::getSize() const {
        int size = 0;
                
        for (auto &field : this->fields) {
            size += field.getSize();
        }
                
        return size;
    }
    
    
    int VertexFormat::getAttribOffset(VertexAttrib::Enum attrib) const {
        
        if (this->packaging == VertexPackaging::MultiBuffer) {
            return VertexFormat::InvalidOffset;
        }
        
        int offset = 0;
        
        for (const VertexField &field : this->fields) {
            if (field.attribute == VertexAttrib::Unused) {
                offset = VertexFormat::InvalidOffset;
                break;
            }
            
            offset += field.getSize();
            
            if (field.attribute == attrib) {
                break;
            }
        }
        
        return offset;
    }
    
    
    VertexField VertexFormat::getAttrib(VertexAttrib::Enum attrib) const {
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
    
    
    VertexFormat VertexFormat::makeVertex() {
        VertexFormat format;
        
        format.fields[0] = VertexField(VertexAttrib::Position, 3, DataType::Float32);
        format.fields[1] = VertexField(VertexAttrib::Normal, 3, DataType::Float32);
        format.fields[2] = VertexField(VertexAttrib::TexCoord, 2, DataType::Float32);
        
        return format;
    }
    
    
    VertexFormat VertexFormat::makeVertex2D() {
        VertexFormat format;
    
        format.fields[0] = VertexField(VertexAttrib::Position, 3, DataType::Float32);
        format.fields[1] = VertexField(VertexAttrib::TexCoord, 2, DataType::Float32);
        
        return format;
    }
}}
