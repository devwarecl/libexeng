/**
 * @file GL3Shader.hpp
 * @brief Definition of the GL3Shader class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_GL3_GL3SHADER_HPP__
#define __EXENG_GRAPHICS_GL3_GL3SHADER_HPP__

#include <exeng/graphics/Shader.hpp>
#include "GL3.hpp"

namespace exeng {
namespace graphics {
namespace gl3 {

/**
 * @brief OpenGL 3 shader.
 */
class GL3Shader : public Shader {
public:
    GL3Shader(ShaderType type);
    
    virtual ~GL3Shader();
    
    virtual TypeInfo getTypeInfo() const;
    
    virtual void setSourceCode(const std::string &sourceCode);
    
    virtual std::string getSourceCode() const;
    
    virtual bool isSourceModified() const;
    
    virtual void compile();
    
    virtual bool isCompiled() const;
    
    virtual ShaderType getType() const;

    /**
     * @brief Get the gl3 identifier of the shader.
     */    
    GLuint getName() const;
    
private:
    GLuint name;
    std::string sourceCode;
    bool modified;
    bool compiled;
    ShaderType type;
};

}
}
}

#endif // __EXENG_GRAPHICS_GL3_GL3SHADER_HPP__
