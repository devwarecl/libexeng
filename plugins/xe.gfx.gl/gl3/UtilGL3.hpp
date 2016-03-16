/**
 * @file UtilGL3.hpp
 * @brief OpenGL 3 Utility functions
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_GL3_GL3UTILS_HPP__
#define __EXENG_GRAPHICS_GL3_GL3UTILS_HPP__

#include "GL3.hpp"
#include "MeshSubsetGL3.hpp"
#include "BufferGL3.hpp"

#include <cassert>
#include <xe/DataType.hpp>
#include <xe/gfx/PixelFormat.hpp>
#include <xe/gfx/Primitive.hpp>
#include <xe/gfx/TextureType.hpp>
#include <xe/gfx/ShaderType.hpp>
#include <xe/gfx/IndexFormat.hpp>

namespace xe { namespace gfx { namespace gl3 {

    inline GLenum convTextureType( TextureType::Enum type ) {
        switch ( type ) {
			case TextureType::Tex1D: return GL_TEXTURE_1D;
			case TextureType::Tex2D: return GL_TEXTURE_2D;
			case TextureType::Tex3D: return GL_TEXTURE_3D;
			default: return GL_FALSE;
        }
    }

    inline GLenum convFormat(PixelFormat::Enum format) {
		switch (format) {
			case PixelFormat::R8G8B8:	return GL_RGB;
			case PixelFormat::R8G8B8A8:	return GL_RGBA;
			default: return GL_FALSE;
		}
    }

    inline GLenum convShaderType(ShaderType::Enum type) {
        switch (type) {
			case ShaderType::Vertex:    return GL_VERTEX_SHADER;
			case ShaderType::Fragment:  return GL_FRAGMENT_SHADER;
			case ShaderType::Geometry:  return GL_GEOMETRY_SHADER;
			default: return GL_FALSE;
        }
    }
	
	inline std::string shaderTypeStr(ShaderType::Enum type) {
        switch (type) {
			case ShaderType::Vertex:    return "vertex";
			case ShaderType::Fragment:  return "fragment";
			case ShaderType::Geometry:  return "geometry";
			default: return GL_FALSE;
        }
    }

    inline GLenum convPrimitive(Primitive::Enum pt) {
        switch (pt) {
			case Primitive::PointList:      return GL_POINTS;
			case Primitive::LineList:       return GL_LINES;
			case Primitive::LineLoop:       return GL_LINE_LOOP;
			case Primitive::LineStrip:      return GL_LINE_STRIP;
			case Primitive::TriangleList:   return GL_TRIANGLES;
			case Primitive::TriangleStrip:  return GL_TRIANGLE_STRIP;
			case Primitive::TriangleFan:    return GL_TRIANGLE_FAN;
			default: return GL_FALSE;
        }
    }

    inline GLenum convDataType(DataType::Enum dt) {
        switch (dt) {
			case DataType::UInt8:   return GL_UNSIGNED_BYTE;
			case DataType::UInt16:  return GL_UNSIGNED_SHORT;
			case DataType::UInt32:  return GL_UNSIGNED_INT;
			case DataType::Int8:    return GL_BYTE;
			case DataType::Int16:   return GL_SHORT;
			case DataType::Int32:   return GL_INT;
			case DataType::Float32: return GL_FLOAT;
			default: return GL_FALSE;
        }
    }

	inline GLenum convIndexFormatType(IndexFormat::Enum indexFormat) {
		switch (indexFormat) {
			case IndexFormat::Index16:	return GL_UNSIGNED_SHORT;
			case IndexFormat::Index32:	return GL_UNSIGNED_INT;
			default: return GL_FALSE;
		}
	}

	inline void checkMeshSubsetBinding(const MeshSubsetGL3 *meshSubset) 
	{
// #if defined(EXENG_DEBUG)
#if 0
		assert(meshSubset);

		GLint currentVao = 0;
		::glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVao);

		const GLint vaoId = meshSubset->getVertexArrayId();
		assert(currentVao == vaoId);

		const auto vertexBuffer = static_cast<const BufferGL3*>(meshSubset->getBuffer(0));
		const auto indexBuffer = static_cast<const BufferGL3*>(meshSubset->getIndexBuffer());

		assert(vertexBuffer);

		GLint bufferId = 0;

		// Check if the current setted buffer is the same
		const GLint vertexBufferId = static_cast<GLint>(vertexBuffer->getBufferId());

        ::glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bufferId);
        assert(bufferId);
        assert(bufferId == vertexBufferId);

		// Check current index buffer
		if (indexBuffer) {
			const GLint indexBufferId = static_cast<GLint>(indexBuffer->getBufferId());

			::glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &bufferId);

			assert(bufferId);
			assert(bufferId == indexBufferId);
		}
#endif
	}
}}}

#endif // __EXENG_GRAPHICS_GL3_GL3UTILS_HPP__
