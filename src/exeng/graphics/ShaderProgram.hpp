/**
 * @file ShaderProgram.hpp
 * @brief ShaderProgram class definition.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_SHADERPROGRAM_HPP__
#define __EXENG_GRAPHICS_SHADERPROGRAM_HPP__

#include <memory>
#include <exeng/Resource.hpp>

namespace exeng { namespace graphics {

    class EXENGAPI Shader;

    /**
     * @brief A shader program hold a collection of shader subprograms.
     */
    class EXENGAPI ShaderProgram : public Resource {
    public:
        ShaderProgram();
    
        virtual ~ShaderProgram();
        
        /**
         * @brief addShader
         * @param shader
         */
        virtual void addShader(std::unique_ptr<Shader> shader) = 0;
        
        /**
         * @brief link
         */
        virtual void link() = 0;
    
        /**
         * @brief isLinked
         * @return 
         */
        virtual bool isLinked() const = 0;
    
        /**
         * @brief Check if the shader program must be linked.
         * @return 
         */
        virtual bool mustRelink() const = 0;
    };
}}

#endif // __EXENG_GRAPHICS_SHADERPROGRAM_HPP__
