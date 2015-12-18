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


#ifndef __EXENG_GRAPHICS_TEXTURE_HPP__
#define __EXENG_GRAPHICS_TEXTURE_HPP__

#include <memory>
#include <exeng/Enum.hpp>
#include <exeng/Object.hpp>
#include <exeng/Vector.hpp>
#include <exeng/graphics/TextureType.hpp>
#include <exeng/graphics/PixelFormat.hpp>
#include <exeng/graphics/ColorFormat.hpp>

namespace exeng { namespace graphics {
    
    /**
     * @brief Faces for CubeMap textures.
     */
    struct TextureCubeMapFace : public Enum {
        enum Enum {
            PositiveX, NegativeX,
            PositiveY, NegativeY,
            PositiveZ, NegativeZ
        };
    };
    
    /**
     * @brief Visual specific appearance for materials.
     */
    class EXENGAPI Texture : public Object {
    public:
        Texture();
        
        virtual ~Texture();
        
        /**
         * @brief Get a direct pointer to the 
         */
        virtual const void* getDataPtr() const = 0;
        
        /**
         * @brief Locks the texture
         */
        virtual void* lock() = 0;
        
        /**
         * @brief Locks the texture
         */
        virtual void* lock(TextureCubeMapFace::Enum Face) = 0;
        
        /**
         * @brief Unlocks the texture.
         */
        virtual void unlock() = 0;
        
        /**
         * @brief Get the current type of texture
         */
        virtual TextureType::Enum getType() const = 0;
        
        /**
         * @brief Get the color format of the texture
         */
        virtual ColorFormat getColorFormat() const = 0;
        
        /**
         * @brief Get the size, in texels, of the texture.
         */
        virtual exeng::Vector3i getSize() const = 0;
        
        /**
         * @brief Get the native handle of the underlying graphics API.
         * 
         * For graphics devices implemented for the exeng library, it just return 
         * the 'this' pointer, casted to std::uint64_t.
         */
        virtual int getHandle() const = 0;
    };

	typedef std::unique_ptr<Texture> TexturePtr;
}}

#endif  // __EXENG_GRAPHICS_TEXTURE_HPP__
