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

#include <xe/gfx/Shader.hpp>
#include "GL3.hpp"

namespace xe { namespace gfx { namespace gl3 {

    /**
    * @brief OpenGL 3 shader.
    */
    class GL3Shader : public Shader {
    public:
        GL3Shader(ShaderType::Enum type);
        
        virtual ~GL3Shader();
        
        virtual TypeInfo getTypeInfo() const override;
        
        virtual void setSourceCode(const std::string &sourceCode) override;
        
        virtual std::string getSourceCode() const override;
        
        virtual bool isSourceModified() const override;
        
        virtual void compile() override;
        
        virtual bool isCompiled() const override;
        
        virtual ShaderType::Enum getType() const override;
        
        /**
        * @brief Get the gl3 identifier of the shader.
        */    
        GLuint getName() const;
        
    private:
        GLuint name;
        std::string sourceCode;
        bool modified;
        bool compiled;
        ShaderType::Enum type;
    };

}}}

#endif // __EXENG_GRAPHICS_GL3_GL3SHADER_HPP__
