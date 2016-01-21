
/**
 * @file TextureGL3.cpp
 * @brief Implementation of the OpenGL 3 texture class
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "UtilGL3.hpp"
#include "TextureGL3.hpp"
#include "DebugGL3.hpp"

#include <stdexcept>
#include <cassert>

using namespace xe;

namespace xe { namespace gfx { namespace gl3 {

	TextureGL3::TextureGL3(TextureType::Enum type, Vector3i size, PixelFormat::Enum format, const void *data) {
		GLuint textureId = 0;
#if defined(EXENG_DEBUG)
		// check for a valid type
		if (convTextureType(type) == GL_FALSE) {
			throw std::invalid_argument("TextureGL3::TextureGL3: Unsupported texture type");
		}
        
		// check the pixel format
		//if (format.isValid() == false) {
		//	throw std::invalid_argument("TextureGL3::TextureGL3: Unsupported texture color format");
		//}
#endif
		// adjust the size
		for(int &coord : size.data) {
			if (coord <= 0) {
				coord = 1;
			}
		}
        
		// get the corresponding OpenGL states
		GLenum textureTarget = convTextureType(type);
		GLenum internalFormat = convFormat(format);
        GLenum dataType = GL_UNSIGNED_BYTE;
    
		// allocate size for the texture
		::glGenTextures(1, &textureId);
		::glBindTexture(textureTarget, textureId);
		
		assert(textureId != 0);

		GL3_CHECK();
    
		if (textureTarget == GL_TEXTURE_1D) {
			::glTexImage1D(textureTarget, 0, internalFormat, size.x, 0, internalFormat, dataType, data);

		} else if (textureTarget == GL_TEXTURE_2D) {
			::glTexImage2D(textureTarget, 0, internalFormat, size.x, size.y, 0, internalFormat, dataType, data);

		} else if (textureTarget == GL_TEXTURE_3D) {
			::glTexImage3D(textureTarget, 0, internalFormat, size.x, size.y, size.z, 0, internalFormat, dataType, data);

		} else {
			assert(false);
		}
		
		GL3_CHECK();

        ::glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        ::glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		::glTexParameteri(textureTarget, GL_TEXTURE_BASE_LEVEL, 0);
		::glTexParameteri(textureTarget, GL_TEXTURE_MAX_LEVEL, 0);
		::glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		::glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GL3_CHECK();
    
		const int bufferSize = size.x * size.y * size.z * (PixelFormat::size(format)/8);
		
		this->format = format;
		this->type = type;
		this->textureId = textureId;
		this->textureTarget = textureTarget;
		this->internalFormat = internalFormat;

		// Determine true size
		if (textureTarget == GL_TEXTURE_1D) {
			GLint width;

			::glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_WIDTH, &width);
			this->size.x = width;

		} else if (textureTarget == GL_TEXTURE_2D) {
			GLint width, height;

			::glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
			::glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

			this->size.x = width;
			this->size.y = height;

		} else if (textureTarget == GL_TEXTURE_3D) {
			GLint width, height, depth;

			::glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_WIDTH, &width);
			::glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_HEIGHT, &height);
			::glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_DEPTH, &depth);

			this->size.x = width;
			this->size.y = height;
			this->size.z = depth;

		} else {
			assert(false);
		}

		::glBindTexture(textureTarget, 0);

		GL3_CHECK();
	}

	TextureGL3::~TextureGL3() {
		if (this->textureId != 0) {
			::glDeleteTextures(1, &this->textureId);
			this->textureId = 0;

			GL3_CHECK();
		}
	}

	Buffer* TextureGL3::getBuffer() {
		return nullptr;
	}

	const Buffer* TextureGL3::getBuffer() const {
		return nullptr;
	}

	Buffer* TextureGL3::getBuffer(TextureCubeMapFace::Enum face) {
		return nullptr;
	}

	const Buffer* TextureGL3::getBuffer(TextureCubeMapFace::Enum face) const {
		return nullptr;
	}

    /*
	void* TextureGL3::lock(TextureCubeMapFace::Enum face) {
		assert(this->textureId != 0);
		throw std::runtime_error("TextureGL3::lock(TextureCubeMapFace): Not yet implemented.");
	}

	void TextureGL3::unlock() {
		assert(this->textureId != 0);
		assert(this->textureTarget != 0);
		assert(this->textureData != nullptr);
    
		::glBindTexture(this->textureTarget, this->textureId);
    
		switch (this->textureTarget) {
		case GL_TEXTURE_1D:
			::glTexSubImage1D(textureTarget, 0, 0, this->size.x, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
			break;
        
		case GL_TEXTURE_2D:
			::glTexSubImage2D(textureTarget, 0, 0, 0, this->size.x, this->size.y, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
			break;
        
		case GL_TEXTURE_3D:
			::glTexSubImage3D(textureTarget, 0, 0, 0, 0, this->size.x, this->size.y, this->size.z, GL_RGBA, GL_UNSIGNED_BYTE, this->textureData);
			break;
        
		default: assert(false); break;
		}
    
		::glBindTexture(this->textureTarget, 0);

		GL3_CHECK();
	}
    */
    
	TextureType::Enum TextureGL3::getType() const {
		return this->type;
	}

	PixelFormat::Enum TextureGL3::getFormat() const {
		return this->format;
	}

	Vector3i TextureGL3::getSize() const {
		return this->size;
	}

	TypeInfo TextureGL3::getTypeInfo() const {
		return TypeId<TextureGL3>();
	}

	int TextureGL3::getHandle() const {
        return static_cast<int>(this->textureId);
    }
}}}
