
#include "TextureBufferGL3.hpp"

#include "DebugGL3.hpp"
#include "TextureGL3.hpp"
#include <cassert>

namespace xe { namespace gfx { namespace gl3 {

    TextureBufferGL3::TextureBufferGL3() {}
    
    TextureBufferGL3::~TextureBufferGL3() {}
  
    void TextureBufferGL3::download() {
        // read the texture pixel data
        ::glBindTexture(texture->getTarget(), texture->getTextureId());
        ::glGetTexImage (
                texture->getTarget(), 
                0, 
                texture->getInternalFormat(), 
                GL_UNSIGNED_BYTE, 
                cache_ptr
        );
        ::glBindTexture(texture->getTarget(), 0);

		GL3_CHECK();
    }
    
	void TextureBufferGL3::upload() {
		const GLenum target = texture->getTarget();
		const xe::Vector3i size = texture->getSize();

		::glBindTexture(target, texture->getTextureId());
		
		if (target == GL_TEXTURE_1D) {
			::glTexSubImage1D(GL_TEXTURE_1D, 0, 0, size.x, GL_RGBA, GL_UNSIGNED_BYTE, cache_ptr);

		} else if (target == GL_TEXTURE_2D) {
			::glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size.x, size.y, GL_RGBA, GL_UNSIGNED_BYTE, cache_ptr);

		} else if (target == GL_TEXTURE_3D) {
			::glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, size.x, size.y, size.z, GL_RGBA, GL_UNSIGNED_BYTE, cache_ptr);

		} else {
			assert(false);
		}

		::glBindTexture(target, 0);

		GL3_CHECK();
	}

    void TextureBufferGL3::setTexture(TextureGL3 *texture) {
        assert(texture);
        
        // TODO: Maybe put this on a utility function
        const Vector3i texture_size = texture->getSize();
        const int pixel_size = PixelFormat::size(texture->getFormat());
        const int cache_size = texture_size.x * texture_size.y * texture_size.z * pixel_size;
        
        // allocate the cache for the texture
        cache.alloc(cache_size);
        
        auto locker = getLocker();
		download();
        
        this->texture = texture;
    }
    
    int TextureBufferGL3::getSize() const {
        return cache.getSize();
    }
    
    void* TextureBufferGL3::lock(BufferUsage::Enum mode) {
		void *cache_ptr = cache.lock(mode);

		if (mode&BufferUsage::Read) {
			this->cache_ptr = cache_ptr;
		}

        return cache_ptr;
    }
    
    void TextureBufferGL3::unlock() {
		if (cache_ptr) {
			this->upload();
			cache_ptr = nullptr;
		}

		cache.unlock();
    }
    
    const void* TextureBufferGL3::lock() const {
        return cache.lock();
    }
    
    void TextureBufferGL3::unlock() const {
        cache.unlock();
    }
}}}
