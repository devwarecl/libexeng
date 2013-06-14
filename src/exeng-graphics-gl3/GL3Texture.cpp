
/**
 * @file GL3Texture.cpp
 * @brief Implementation of the OpenGL 3 texture class
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "GL3Utils.hpp"
#include "GL3Texture.hpp"
#include "GL3Debug.hpp"

#include <map>
#include <stdexcept>
#include <cassert>

using namespace exeng;
using namespace exeng::math;

namespace exeng {
namespace graphics {
namespace gl3 {

GL3Texture::GL3Texture(exeng::math::Vector3i size, ColorFormat colorFormat, TextureType type) {
    GLuint textureId = 0;
    
    // check the type
    if (convType(type) == GL_FALSE) {
        throw std::invalid_argument("GL3Texture::GL3Texture: Unsupported texture type");
    }
    
    // check the pixel format
    if (colorFormat.isValid() == false) {
        throw std::invalid_argument("GL3Texture::GL3Texture: Unsupported texture color format");
    }
    
    // adjust the size
    for(int &coord : size.data) {
        if (coord <= 0) {
            coord = 1;
        }
    }
    
    // get the corresponding OpenGL size
    GLenum textureTarget = convType(type);
    
    // get the corresponding OpenGL internal format
    
    // allocate size for the texture
    ::glGenTextures(1, &textureId);
    ::glBindTexture(textureTarget, textureId);
    
    if (textureTarget == GL_TEXTURE_1D) {
        ::glTexImage1D(textureTarget, 0, 0, size.x, 0, 0, 0, nullptr);
    } else if (textureTarget == GL_TEXTURE_2D) {
        ::glTexImage2D(textureTarget, 0, 0, size.x, size.y, 0, 0, 0, nullptr);
    } else if (textureTarget == GL_TEXTURE_3D) {
        ::glTexImage3D(textureTarget, 0, 0, size.x, size.y, size.z, 0, 0, 0, nullptr);
    } else {
        assert(false);
    }
    
    ::glTexParameteri(textureTarget, GL_TEXTURE_BASE_LEVEL, 0);
    ::glTexParameteri(textureTarget, GL_TEXTURE_MAX_LEVEL, 0);
    ::glBindTexture(textureTarget, 0);
    
    assert(textureId != 0);
    GL3_CHECK();
    
    this->size = size;
    this->colorFormat = colorFormat;
    this->type = type;
    this->textureId = textureId;
}


GL3Texture::~GL3Texture() {
    if (this->textureId != 0) {
        ::glDeleteTextures(1, &this->textureId);
        this->textureId = 0;
    }
}


void* GL3Texture::lock() {
    this->textureData = this->buffer.lock();
    return this->textureData;
}


void* GL3Texture::lock(TextureCubeMapFace face) {
    throw std::runtime_error("GL3Texture::lock: Not implemented yet.");
}


void GL3Texture::unlock() {
    
    //! TODO: Fill all parameters of the glTexSubImageXD calls.
    GLenum textureTarget = convType(this->type);
    assert(textureTarget != 0);
    
    ::glBindTexture(textureTarget, this->textureId);
    
    if (textureTarget == GL_TEXTURE_1D) {
        ::glTexSubImage1D(textureTarget, 0, 0, this->size.x, 0, 0, this->textureData);
    } else if (textureTarget == GL_TEXTURE_2D) {
        // ::glTexSubImage2D(textureTarget, 0, 0, this->size.x, 0, 0, this->textureData);
    } else if (textureTarget == GL_TEXTURE_3D) {
        // ::glTexSubImage3D(textureTarget, 0, 0, this->size.x, 0, 0, this->textureData);
    } else {
        assert( false );
    }
    
    this->buffer.unlock();
}


TextureType GL3Texture::getType() const {
    return this->type;
}

ColorFormat GL3Texture::getColorFormat() const {
    return this->colorFormat;
}

Vector3i GL3Texture::getSize() const {
    return this->size;
}


TypeInfo GL3Texture::getTypeInfo() const {
    return TypeInfo::get<GL3Texture>();
}

}
}
}
