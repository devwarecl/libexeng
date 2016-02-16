
/**
 * @file ShaderProgramGL3.hpp
 * @brief Definition of the ShaderProgramGL3 class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_GL3_GL3SHADERPROGRAM_HPP__
#define __EXENG_GRAPHICS_GL3_GL3SHADERPROGRAM_HPP__

#include <xe/gfx/ShaderProgram.hpp>
#include <list>
#include "GL3.hpp"

namespace xe { namespace gfx { namespace gl3 {

    class ShaderGL3;
    class ShaderProgramGL3 : public ShaderProgram {
    public:
        ShaderProgramGL3();
        virtual ~ShaderProgramGL3();

        virtual TypeInfo getTypeInfo() const override;
        virtual void addShader(Shader *shader) override;
        virtual void link() override;
        virtual bool isLinked() const override;
        virtual bool mustRelink() const override;
        
        GLuint getProgramId() const;
        
    private:
        GLuint programId = 0;
        bool modified = false;
        bool linked = false;
        
        std::list<Shader*> shaders;
    };
}}}

#endif // __EXENG_GRAPHICS_GL3_GL3SHADERPROGRAM_HPP__
