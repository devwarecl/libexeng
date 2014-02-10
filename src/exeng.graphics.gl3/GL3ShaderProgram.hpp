
/**
 * @file GL3ShaderProgram.hpp
 * @brief Definition of the GL3ShaderProgram class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_GL3_GL3SHADERPROGRAM_HPP__
#define __EXENG_GRAPHICS_GL3_GL3SHADERPROGRAM_HPP__

#include <exeng/graphics/ShaderProgram.hpp>
#include <list>
#include "GL3.hpp"

namespace exeng {
namespace graphics {
namespace gl3 {

class GL3Shader;
class GL3ShaderProgram : public ShaderProgram {
public:
    GL3ShaderProgram(ResourceFactory *factory);
    
    virtual ~GL3ShaderProgram();

    virtual TypeInfo getTypeInfo() const;
    
    virtual void addShader(Shader *shader);
    
    virtual void removeShader(Shader *shader);
    
    virtual void link();
    
    virtual bool isLinked() const;
    
    virtual bool mustRelink() const;
    
    GLuint getProgramId() const;
    
    virtual void release();
    
private:
    GLuint programId;
    bool modified;
    bool linked;
    
    std::list< GL3Shader* > shaders;
};


}
}
}

#endif // __EXENG_GRAPHICS_GL3_GL3SHADERPROGRAM_HPP__
