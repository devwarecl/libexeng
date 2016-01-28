
#include "Material2.hpp"
#include <cassert>

namespace xe { namespace gfx {
    Material2::Material2(const MaterialFormat2 *format_) : format(format_) {}
    
    Texture* Material2::getTexture(const int index) {
        assert(index >= 0);
        assert(index < this->getTextureCount());
        
        return this->textures[index];
    }
    
    const Texture* Material2::getTexture(const int index) const {
        assert(index >= 0);
        assert(index < this->getTextureCount());
        
        return this->textures[index];
    }
    
    void Material2::setTexture(const int index, Texture* texture) {
        assert(index >= 0);
        assert(index < this->getTextureCount());
        
        this->textures[index] = texture;
    }
}}
