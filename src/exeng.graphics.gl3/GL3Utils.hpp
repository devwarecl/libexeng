/**
 * @file GL3Utils.hpp
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

#include <exeng/DataType.hpp>
#include <exeng/graphics/Primitive.hpp>
#include <exeng/graphics/TextureType.hpp>
#include <exeng/graphics/ColorFormat.hpp>
#include <exeng/graphics/ShaderType.hpp>

namespace exeng { namespace graphics { namespace gl3 {

    inline GLenum convTextureType( TextureType::Enum type ) {
        switch ( type ) {
        case TextureType::Tex1D: return GL_TEXTURE_1D;
        case TextureType::Tex2D: return GL_TEXTURE_2D;
        case TextureType::Tex3D: return GL_TEXTURE_3D;
        default: return GL_FALSE;
        }
    }


    inline GLenum convFormat(const ColorFormat &format) {
        if (format == ColorFormat(8, 
                    ColorChannel( ColorComponent::Red, 8 ))) {
            return GL_RED;
        } else if (format == ColorFormat(16, 
                            ColorChannel( ColorComponent::Red, 8 ), 
                            ColorChannel( ColorComponent::Green, 8 ))) {
            return GL_RG;
        }else if (format == ColorFormat(24, 
                            ColorChannel( ColorComponent::Red, 8 ), 
                            ColorChannel( ColorComponent::Green, 8 ), 
                            ColorChannel( ColorComponent::Blue, 8 ))) {
            return GL_RGB;
        } else if (format == ColorFormat(32, 
                            ColorChannel( ColorComponent::Red, 8 ), 
                            ColorChannel( ColorComponent::Green, 8 ), 
                            ColorChannel( ColorComponent::Blue, 8 ), 
                            ColorChannel( ColorComponent::Alpha, 8 ))) {
            return GL_RGBA;
        } else {
            return GL_FALSE;
        }
    }


    inline GLenum convShaderType(ShaderType type) {
        switch (type) {
        case ShaderType::Vertex:    return GL_VERTEX_SHADER;
        case ShaderType::Fragment:  return GL_FRAGMENT_SHADER;
        case ShaderType::Geometry:  return GL_GEOMETRY_SHADER;
        default: return GL_FALSE;
        }
    }


    inline std::string shaderTypeStr(ShaderType type) {
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
        case DataType::Float64: return GL_DOUBLE;
        default: return GL_FALSE;
        }
    }

}}}

#endif // __EXENG_GRAPHICS_GL3_GL3UTILS_HPP__

