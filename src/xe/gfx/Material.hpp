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

#pragma once

#ifndef __xe_gfx_material_hpp__
#define __xe_gfx_material_hpp__

#include <cassert>
#include <vector>
#include <tuple>
#include <memory>
#include <xe/Object.hpp>
#include <xe/Vector.hpp>
#include <xe/DataType.hpp>
#include <xe/DataFormat.hpp>
#include <xe/gfx/Forward.hpp>

namespace xe { namespace gfx {
    
    struct TextureFilter : public Enum {
        enum Enum {
            Linear,
            Nearest
        };
    };
    
    struct TextureWrap : public Enum {
        enum Enum {
            Clamp,
            Repeat
        };
    };
    
    typedef Attrib MaterialAttrib;

    struct MaterialLayer {
        std::string name;

        Texture *texture = nullptr;
        
        TextureFilter::Enum magFilter = TextureFilter::Linear;
        TextureFilter::Enum minFilter = TextureFilter::Linear;
        
        TextureWrap::Enum xWrap = TextureWrap::Repeat;
        TextureWrap::Enum yWrap = TextureWrap::Repeat;
        TextureWrap::Enum zWrap = TextureWrap::Repeat;
        TextureWrap::Enum wWrap = TextureWrap::Repeat;
    };
    
    struct MaterialFormat : public DataFormat<MaterialAttrib, 16> {
        std::array<std::string, 8> layerNames;
    };

    /**
     * @brief Describes the visual appearance of the objects.
     * @note Class interface subject to change.
     */
    class EXENGAPI Material : public Object {
    public:        
        virtual ~Material() {}
        
        virtual MaterialLayer getLayer(const int index) = 0;
        virtual void setLayer(const int index, const MaterialLayer &layer) = 0;

        virtual Buffer *getBuffer() = 0;
        virtual const Buffer *getBuffer() const = 0;

        virtual const MaterialFormat* getFormat() const = 0;
    };
}}

#endif
