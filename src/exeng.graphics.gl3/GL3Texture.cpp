
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

#include <stdexcept>
#include <cassert>

using namespace exeng;
using namespace exeng::math;

namespace exeng { namespace graphics { namespace gl3 {

	GL3Texture::GL3Texture(ResourceManager *factory,  TextureType::Enum type, Vector3i size, const ColorFormat &colorFormat) : Texture(factory) {
		GLuint textureId = 0;
        
		// check for a valid type
		if (convTextureType(type) == GL_FALSE) {
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
        
		// get the corresponding OpenGL states
		GLenum textureTarget = convTextureType(type);
		GLenum internalFormat = convFormat(colorFormat);
        GLenum dataType = GL_UNSIGNED_BYTE;
    
		// allocate size for the texture
		::glGenTextures(1, &textureId);
		::glBindTexture(textureTarget, textureId);
    
		GL3_CHECK();
    
		if (textureTarget == GL_TEXTURE_1D) {
			::glTexImage1D(textureTarget, 0, internalFormat, size.x, 0, internalFormat, dataType, nullptr);
		} else if (textureTarget == GL_TEXTURE_2D) {
			::glTexImage2D(textureTarget, 0, internalFormat, size.x, size.y, 0, internalFormat, dataType, nullptr);
		} else if (textureTarget == GL_TEXTURE_3D) {
			::glTexImage3D(textureTarget, 0, internalFormat, size.x, size.y, size.z, 0, internalFormat, dataType, nullptr);
		} else {
			assert(false);
		}
    
		GL3_CHECK();

        ::glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        ::glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		::glTexParameteri(textureTarget, GL_TEXTURE_BASE_LEVEL, 0);
		::glTexParameteri(textureTarget, GL_TEXTURE_MAX_LEVEL, 0);
		::glBindTexture(textureTarget, 0);
    
		assert(textureId != 0);
		GL3_CHECK();
    
		this->buffer.allocate(size.x*size.y*size.z * colorFormat.size/8);
		this->size = size;
		this->colorFormat = colorFormat;
		this->type = type;
		this->textureId = textureId;
		this->textureTarget = textureTarget;
		this->internalFormat = internalFormat;
	}


	GL3Texture::~GL3Texture() {
		if (this->textureId != 0) {
			::glDeleteTextures(1, &this->textureId);
			this->textureId = 0;
		}
	}


	void* GL3Texture::lock() {
		assert(this->textureId != 0);
    
		this->textureData = this->buffer.lock();
		return this->textureData;
	}


	void* GL3Texture::lock(TextureCubeMapFace::Enum face) {
		assert(this->textureId != 0);
		throw std::runtime_error("GL3Texture::lock(TextureCubeMapFace): Not yet implemented.");
	}


	void GL3Texture::unlock() {
		assert(this->textureId != 0);
		assert(this->textureTarget != 0);
		assert(this->textureData != nullptr);
    
		::glBindTexture(this->textureTarget, this->textureId);
    
		switch (this->textureTarget) {
		case GL_TEXTURE_1D:
			::glTexSubImage1D(textureTarget, 0,  0, this->size.x, 
							  GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
			break;
        
		case GL_TEXTURE_2D:
			::glTexSubImage2D(textureTarget, 0,  0, 0, this->size.x, this->size.y, 
							  GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
			break;
        
		case GL_TEXTURE_3D:
			::glTexSubImage3D(textureTarget, 0,  0, 0, 0, this->size.x, this->size.y, this->size.z, 
							  GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
			break;
        
		default: assert(false); break;
		}
    
		::glBindTexture(this->textureTarget, 0);
    
		GL3_CHECK();
    
		this->buffer.unlock();
	}


	TextureType::Enum GL3Texture::getType() const {
		return this->type;
	}


	ColorFormat GL3Texture::getColorFormat() const {
		return this->colorFormat;
	}


	Vector3i GL3Texture::getSize() const {
		return this->size;
	}


	TypeInfo GL3Texture::getTypeInfo() const {
		return TypeId<GL3Texture>();
	}


	void GL3Texture::release() {
		std::cout << "GL3Texture::release: TODO: Not implemented." << std::endl;
	}
	
	std::uint64_t GL3Texture::getHandle() const {
        return static_cast<std::uint64_t>(this->textureId);
    }
    
    const void* GL3Texture::getDataPtr() const {
        return this->textureData;
    }
}}}
