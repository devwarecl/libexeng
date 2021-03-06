
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
		
        GL3_CHECK();

		assert(textureId != 0);

		if (textureTarget == GL_TEXTURE_1D) {
			::glTexImage1D(textureTarget, 0, 4, size.x, 0, internalFormat, dataType, nullptr);

		} else if (textureTarget == GL_TEXTURE_2D) {
			::glTexImage2D(textureTarget, 0, 4, size.x, size.y, 0, internalFormat, dataType, nullptr);

		} else if (textureTarget == GL_TEXTURE_3D) {
			::glTexImage3D(textureTarget, 0, 4, size.x, size.y, size.z, 0, internalFormat, dataType, nullptr);

		} else {
			assert(false);
		}

        GL3_CHECK();
        
        ::glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(GL_LINEAR));
        ::glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(GL_LINEAR));
		::glTexParameteri(textureTarget, GL_TEXTURE_BASE_LEVEL, 0);
		::glTexParameteri(textureTarget, GL_TEXTURE_MAX_LEVEL, 0);
		::glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, static_cast<GLint>(GL_CLAMP_TO_EDGE));
		::glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, static_cast<GLint>(GL_CLAMP_TO_EDGE));

		const int bufferSize = size.x * size.y * size.z * (PixelFormat::size(format)/8);
		
		this->format = format;
		this->type = type;
		this->textureId = textureId;
		this->textureTarget = textureTarget;
		this->internalFormat = internalFormat;
        this->size = size;

        ::glBindTexture(textureTarget, 0);

		// sync the internal texture buffer with the current texture
		buffer.setTexture(this);

		if (data) {
			buffer.write(data);
		}

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
