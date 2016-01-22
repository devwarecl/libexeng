
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
        
        GLuint getTexture() const {
            return texture;
        }
        
        virtual ~TextureBufferGL3();
        
		virtual int getHandle() const override;

		virtual int getSize() const override;

        virtual void* lock(BufferLockMode::Enum mode) override;

		virtual void unlock() override;

		virtual const void* lock() const override;

		virtual void unlock() const override;
        
    private:
        int getTextureStorage();
        
        void syncCache();
        
        void* lockImpl(BufferLockMode::Enum mode) const;
        
        void unlockImpl() const;
        
    private:
        TextureGL3 *texture = nullptr;
        HeapBuffer cache;
    };
}}}

#endif
