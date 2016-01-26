
#pragma once

#ifndef __xe_gfx_TEXTUREBUFFERGL3_Hpp__
#define __xe_gfx_TEXTUREBUFFERGL3_Hpp__

#include <xe/Buffer.hpp>
#include <xe/HeapBuffer.hpp>

#include "GL3.hpp"

namespace xe { namespace gfx { namespace gl3 {

    class TextureGL3;
    class TextureBufferGL3 : public Buffer {
    public:
        TextureBufferGL3();
        
        void setTexture(TextureGL3 *texture);
        
        TextureGL3 *getTexture() const {
            return texture;
        }
        
        virtual ~TextureBufferGL3();
        
		virtual int getSize() const override;

        virtual void* lock(BufferLockMode::Enum mode) override;

		virtual void unlock() override;

		virtual const void* lock() const override;

		virtual void unlock() const override;
        
		virtual int getHandle() const override {
			return 0;
		}

    private:
		// read data from texture to cache
        void download();

		// write data to texture from cache
		void upload();
        
    private:
        TextureGL3 *texture = nullptr;
		void* cache_ptr = nullptr;
        HeapBuffer cache;
    };
}}}

#endif
