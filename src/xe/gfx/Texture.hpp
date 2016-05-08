/**
 * @file Texture.hpp
 * @brief Define the Texture abstract class, and his companion structures.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#pragma once

#ifndef __EXENG_GRAPHICS_TEXTURE_HPP__
#define __EXENG_GRAPHICS_TEXTURE_HPP__

#include <memory>
#include <array>
#include <xe/Enum.hpp>
#include <xe/Object.hpp>
#include <xe/Vector.hpp>
#include <xe/Buffer.hpp>
#include <xe/gfx/TextureType.hpp>
#include <xe/gfx/PixelFormat.hpp>

namespace xe { namespace gfx {
    /**
     * @brief Faces for CubeMap textures.
     */
    struct TextureCubeMapFace : public Enum {
        enum Enum {
            PositiveX, NegativeX,
            PositiveY, NegativeY,
            PositiveZ, NegativeZ
        };

		std::array<TextureCubeMapFace::Enum, 6> enumerate() {
			return {PositiveX, NegativeX, PositiveY, NegativeY, PositiveZ, NegativeZ};
		}
    };
    
    /**
     * @brief Visual specific appearance for materials.
     */
    class EXENGAPI Texture : public Object {
    public:
        typedef std::unique_ptr<Texture> Ptr;

    public:
        virtual ~Texture() {}

		virtual Buffer* getBuffer() = 0;

		virtual const Buffer* getBuffer() const = 0;

		virtual Buffer* getBuffer(TextureCubeMapFace::Enum face) = 0;

		virtual const Buffer* getBuffer(TextureCubeMapFace::Enum face) const = 0;

        /**
         * @brief Get the current type of texture
         */
        virtual TextureType::Enum getType() const = 0;
        
        /**
         * @brief Get the color format of the texture
         */
        virtual PixelFormat::Enum getFormat() const = 0;
        
        /**
         * @brief Get the size, in texels, of the texture.
         */
        virtual xe::Vector3i getSize() const = 0;
        
        /**
         * @brief Get the native handle of the underlying graphics API.
         * 
         * For graphics devices implemented for the exeng library, it just return 
         * the 'this' pointer, casted to std::uint64_t.
         */
        virtual int getHandle() const = 0;
    };
}}

#endif  // __EXENG_GRAPHICS_TEXTURE_HPP__
