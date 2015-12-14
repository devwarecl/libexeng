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
        VertexAttrib::Enum attribute = VertexAttrib::Unused;    //! The attribute
        int count = 0;                                          //! The dimension
        DataType::Enum dataType = DataType::Float32;            //! The data type for the vertex field.
        
        VertexField() {}

        VertexField(VertexAttrib::Enum attrib_, int count_, DataType::Enum dataType_) {
			this->attribute = attrib_;
			this->count = count_;
			this->dataType = dataType_;
        }
        
        /**
         * @brief Get the size, in bytes, of the field.
         */
        int getSize() const {
            return this->count * DataType::getSize(dataType);
        }

		bool operator== (const VertexField &other) const {
			if (this->attribute != other.attribute) {
				return false;
			}

			if (this->count != other.count) {
				return false;
			}

			if (this->dataType != other.dataType) {
				return false;
			}

			return true;
		}

		bool operator!= (const VertexField &other) const {
			return !(*this == other);
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
        static const int FieldCount = 8;
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
		 * @brief Check if the specified attribute exists.
		 */
		bool hasAttrib(VertexAttrib::Enum attrib) const;

        /**
         * @brief Get the VertexField object containing the specified Vertex Attribute.
         */
        VertexField getAttrib(VertexAttrib::Enum attrib) const;

		bool operator== (const VertexFormat &other) const;

		bool operator!= (const VertexFormat &other) const;
    };
    
    inline VertexFormat::VertexFormat() {
        this->packaging = VertexPackaging::SingleBuffer;
        
        for (int i=0; i<VertexFormat::FieldCount; ++i) {
            this->fields[i] = VertexField(VertexAttrib::Unused, 0, DataType::Float32);
        }
    }
    
    inline int VertexFormat::getSize() const {
        int size = 0;
                
        for (auto &field : this->fields) {
            size += field.getSize();
        }
                
        return size;
    }
    
    inline int VertexFormat::getAttribOffset(VertexAttrib::Enum attrib) const {
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
    
    inline VertexField VertexFormat::getAttrib(VertexAttrib::Enum attrib) const {
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
    
	inline bool VertexFormat::hasAttrib(VertexAttrib::Enum attrib) const {
		return this->getAttrib(attrib).attribute != VertexAttrib::Unused;
	}

	inline bool VertexFormat::operator== (const VertexFormat &other) const {
		if (this->packaging != other.packaging) {
			return false;
		}

		for (int i=0; i<FieldCount; i++) {
			if (this->fields[i] != other.fields[i]) {
				return false;
			}
		}

		return true;
	}

	inline bool VertexFormat::operator!= (const VertexFormat &other) const {
		return !(*this == other);
	}
}}

#endif  //__EXENG_GRAPHICS_VERTEXFORMAT_HPP__
