
#pragma once

#ifndef __xe_gfx_materialformat2_hpp__
#define __xe_gfx_materialformat2_hpp__

#include <array>
#include <cassert>
#include <xe/DataType.hpp>
#include <xe/Buffer.hpp>
#include <xe/gfx/ShaderProgram.hpp>
#include <xe/gfx/Texture.hpp>

namespace xe { namespace gfx {
    
    struct MaterialAttribDesc2 {
        xe::DataType::Enum type = xe::DataType::Unknown;
        int count = 0;
        int align = 1;
        int offset = 0;
        std::string name;
        
        int getSize() const {
            const int temp_size = count*xe::DataType::getSize(type);
            const int size = temp_size + temp_size%align;
            
            return size;
        }
    };
    
    class MaterialFormat2 {
    public:
        int getSize() const {
            return size;
        }
        
        int getAttribCount() const {
            return AttribCount;
        }
        
        const MaterialAttribDesc2& getAttrib(const int index) const {
            assert(index >= 0);
            assert(index < this->getAttribCount());
            
            return attribs[index];
        }
        
        template<typename ContainerType>
        void construct(const ContainerType &attribs) {
        
            // store attributes, compute offsets, and compute size
            int i = 0;
            int offset = 0;
            
            for (const auto &attrib : attribs) {
                if (attrib.type == xe::DataType::Unknown) {
                    break;
                }
                
                this->attribs[i] = attrib;
                this->attribs[i].offset = offset;
                
                offset += this->attribs[i].getSize();
                i++;
                
                if (i == this->getAttribCount()) {
                    break;
                }
            }
            
            this->size = offset;
        }
                
    private:
        static const int AttribCount = 8;
        std::array<MaterialAttribDesc2, AttribCount> attribs;
        int size = 0;
    };
}}

#endif 
