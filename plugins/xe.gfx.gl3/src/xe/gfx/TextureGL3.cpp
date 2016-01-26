
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

		if (textureTarget == GL_TEXTURE_1D) {
			::glTexImage1D(textureTarget, 0, internalFormat, size.x, 0, internalFormat, dataType, data);

		} else if (textureTarget == GL_TEXTURE_2D) {
			::glTexImage2D(textureTarget, 0, internalFormat, size.x, size.y, 0, internalFormat, dataType, data);

		} else if (textureTarget == GL_TEXTURE_3D) {
			::glTexImage3D(textureTarget, 0, internalFormat, size.x, size.y, size.z, 0, internalFormat, dataType, data);

		} else {
			assert(false);
		}
		
        ::glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        ::glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		::glTexParameteri(textureTarget, GL_TEXTURE_BASE_LEVEL, 0);
		::glTexParameteri(textureTarget, GL_TEXTURE_MAX_LEVEL, 0);
		::glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		::glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		const int bufferSize = size.x * size.y * size.z * (PixelFormat::size(format)/8);
		
		this->format = format;
		this->type = type;
		this->textureId = textureId;
		this->textureTarget = textureTarget;
		this->internalFormat = internalFormat;

		// Determine true size
		xe::Vector3i tex_size = {1, 1, 1};

		::glGetTexLevelParameteriv(textureTarget, 0, GL_TEXTURE_WIDTH, &tex_size.x);

		if (textureTarget==GL_TEXTURE_3D || textureTarget==GL_TEXTURE_2D) {
			::glGetTexLevelParameteriv(textureTarget, 0, GL_TEXTURE_HEIGHT, &tex_size.y);
		}

		if (textureTarget==GL_TEXTURE_3D) {
			::glGetTexLevelParameteriv(textureTarget, 0, GL_TEXTURE_DEPTH, &tex_size.z);
		}

		this->size = tex_size;

		::glBindTexture(textureTarget, 0);

		// download the texture cache
		buffer.setTexture(this);

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
		return &buffer;
	}

	const Buffer* TextureGL3::getBuffer() const {
		return &buffer;
	}

	Buffer* TextureGL3::getBuffer(TextureCubeMapFace::Enum face) {
		return nullptr;
	}

	const Buffer* TextureGL3::getBuffer(TextureCubeMapFace::Enum face) const {
		return nullptr;
	}

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
