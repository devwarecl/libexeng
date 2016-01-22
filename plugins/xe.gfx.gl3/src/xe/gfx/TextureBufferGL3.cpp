
#include "TextureBufferGL3.hpp"

#include "TextureGL3.hpp"
#include <cassert>

namespace xe { namespace gfx { namespace gl3 {

    TextureBufferGL3::TextureBufferGL3() {}
    
    TextureBufferGL3::~TextureBufferGL3() {}
  
    void TextureBufferGL3::syncCache() {
        // Compute texture storage size
        // TODO: put this on a utility function
        const Vector3i texture_size = texture->getSize();
        const int pixel_size = PixelFormat::size(texture->getFormat());
        const int cache_size = texture_size.x * texture_size.y * texture_size.z * pixel_size;
        
        // allocate the cache for the texture
        cache.alloc(cache_size);
        
        auto cache_locker = cache.getLocker();
        
        // read the texture pixel data
        ::glBindTexture(texture->getTarget(), texture->getTextureId());
        ::glGetTexImage (
                texture->getTarget(), 
                0, 
                texture->getInternalFormat(), 
                GL_UNSIGNED_BYTE, 
                cache_locker.getSize(), 
                cache_locker.getPointer()
        );
        ::glBindTexture(texture->getTarget(), 0);
    }
    
    void* TextureBufferGL3::lockImpl(BufferLockMode::Enum mode) const {
        if (mode&BufferLockMode::Read) {
            // we will need to read the data from the texture
            
        }
    }
    
    void TextureBufferGL3::unlockImpl() const {
        
    }
    
    void TextureBufferGL3::setTexture(TextureGL3 *texture) {
        assert(texture);
        
        // TODO: Maybe put this on a utility function
        const Vector3i texture_size = texture->getSize();
        const int pixel_size = PixelFormat::size(texture->getFormat());
        const int cache_size = texture_size.x * texture_size.y * texture_size.z * pixel_size;
        
        // allocate the cache for the texture
        cache.alloc(cache_size);
        
        auto cache_locker = cache.getLocker();
        
        // read the texture pixel data
        ::glBindTexture(texture->getTarget(), texture->getTextureId());
        ::glGetTexImage (
                texture->getTarget(), 
                0, 
                texture->getInternalFormat(), 
                GL_UNSIGNED_BYTE, 
                cache_locker.getSize(), 
                cache_locker.getPointer()
        );
        ::glBindTexture(texture->getTarget(), 0);
        
        GL3_CHECK();
        
        this->texture = texture;
    }
    
    
    int TextureBufferGL3::getSize() const {
        return cache.getSize();
    }
    
    void* TextureBufferGL3::lock(BufferLockMode::Enum mode) {
        return cache.lock(mode);
    }
    
    void TextureBufferGL3::unlock() {
        cache.unlock();
    }
    
    const void* TextureBufferGL3::lock() const {
        return cache.lock();
    }
    
    void TextureBufferGL3::unlock() const {
        cache.unlock();
    }
}}}
