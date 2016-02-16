
/**
 * @file ShaderProgramGL3.cpp
 * @brief Definition of the ShaderProgramGL3 class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "ShaderProgramGL3.hpp"

#include "ShaderGL3.hpp"
#include "DebugGL3.hpp"

#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <xe/Exception.hpp>

namespace xe { namespace gfx { namespace gl3 {

    /**
     * @brief The ProgramAttacher class uses RAII to attach the shaders. 
     * Exception safe!
     */
    class ProgramAttacher {            
    public:
        ProgramAttacher(GLuint programId, std::list<Shader*> shaders) {
#if defined(EXENG_DEBUG)
			if (!programId) {
				EXENG_THROW_EXCEPTION("Invalid supplied program id.");
			}

			if (!shaders.size()) {
				EXENG_THROW_EXCEPTION("Total count of shader is zero.");
			}
#endif
			this->programId = programId;
			this->shaders = shaders;

            for (Shader *shader : this->shaders) {
                ShaderGL3* glshader = static_cast<ShaderGL3*>(shader);
                ::glAttachShader(this->programId, glshader->getName());
            }
            
            GL3_CHECK();
        }
        
        ~ProgramAttacher() {
            // Detach the programs. They are not longer neccesary.
            for (Shader *shader : this->shaders) {
                ShaderGL3* glshader = static_cast<ShaderGL3*>(shader);
                ::glDetachShader(this->programId, glshader->getName());
            }
            
            GL3_CHECK();
        }
        
        GLuint programId = 0;
        std::list<Shader*> shaders;
    };

    ShaderProgramGL3::ShaderProgramGL3() {        
        this->programId = ::glCreateProgram();
        
        GL3_CHECK();
    }

    ShaderProgramGL3::~ShaderProgramGL3() {
        if (this->programId != 0) {
            ::glDeleteProgram(this->programId);
            this->programId = 0;
        }
        
        GL3_CHECK();
    }

    TypeInfo ShaderProgramGL3::getTypeInfo() const {
        return TypeId<ShaderProgramGL3>();
    }
    
    void ShaderProgramGL3::addShader(Shader *shader) {
        assert (this->programId != 0);
    
#if defined(EXENG_DEBUG)
        if (shader == nullptr) {
            throw std::invalid_argument("ShaderProgramGL3::addShader -> The shader object can't be null");
        }
        
        if (shader->getTypeInfo() != TypeId<ShaderGL3>()) {
            throw std::invalid_argument("ShaderProgramGL3::addShader -> The shader object must be of type ShaderGL3.");
        }
#endif
        
        //! TODO: Check the creator objects too
        this->modified = true;
        this->shaders.push_back(shader);
    }

    void ShaderProgramGL3::link() {
        assert (this->programId != 0);
        
        if (!(this->linked == false || this->modified == true || this->shaders.size() > 0)) {
			EXENG_THROW_EXCEPTION("Can't link shader program. Invalid current status.");
		}

        ProgramAttacher attacher(this->programId, std::move(this->shaders));
            
        // Link the shaders to the program, 
        ::glLinkProgram(this->programId);
            
        // and check for errors
        GLint status = 0;
        ::glGetProgramiv(this->programId, GL_LINK_STATUS, &status);
            
        if (status == GL_FALSE) {
            // Get the error string length
            GLint infoLogLength = 0;
            ::glGetProgramiv(this->programId, GL_INFO_LOG_LENGTH, &infoLogLength);
                
            // Get the error string
            std::string infoLog;
            infoLog.resize(infoLogLength + 1);
            ::glGetProgramInfoLog(this->programId, infoLogLength, NULL, (GLchar*)infoLog.c_str());
                
            throw std::runtime_error(std::string("ShaderProgramGL3::link: Link failure:\n") + infoLog);
        }
        
        this->linked = true;
        this->modified = false;
        
        GL3_CHECK();
    }

    bool ShaderProgramGL3::isLinked() const {
        assert (this->programId != 0);
        return this->linked;
    }

    bool ShaderProgramGL3::mustRelink() const {
        assert (this->programId != 0);
        return this->modified;
    }

    GLuint ShaderProgramGL3::getProgramId() const {
        assert (this->programId != 0);
        return this->programId;
    }
}}}
