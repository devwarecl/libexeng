
/**
 * @file GL3ShaderProgram.cpp
 * @brief Definition of the GL3ShaderProgram class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include "GL3Shader.hpp"
#include "GL3ShaderProgram.hpp"
#include "GL3Debug.hpp"

#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <iostream>

namespace exeng { namespace graphics { namespace gl3 {
    GL3ShaderProgram::GL3ShaderProgram() {        
        this->programId = ::glCreateProgram();
        
        GL3_CHECK();
    }

    GL3ShaderProgram::~GL3ShaderProgram() {
        if (this->programId != 0) {
            ::glDeleteProgram(this->programId);
            this->programId = 0;
        }
        
        GL3_CHECK();
    }

    TypeInfo GL3ShaderProgram::getTypeInfo() const {
        return TypeId<GL3ShaderProgram>();
    }
    
    void GL3ShaderProgram::addShader(std::unique_ptr<Shader> shader) {
        assert (this->programId != 0);
        
        if (shader == nullptr) {
            throw std::invalid_argument("GL3ShaderProgram::addShader -> The shader object can't be null");
        }
        
        if (shader->getTypeInfo() != TypeId<GL3Shader>()) {
            throw std::invalid_argument("GL3ShaderProgram::addShader -> The shader object must be of type GL3Shader.");
        }
        
        //! TODO: Check the creator objects too
        this->modified = true;
        this->shaders.push_back(std::move(shader));
    }

    /**
    * @brief The ProgramAttacher class uses RAII to attach the shaders. 
    * Exception safe!
    */
    class ProgramAttacher {            
    public:
        ProgramAttacher(GLuint p, std::list<std::unique_ptr<Shader>> shaders_) : programId(p), shaders(std::move(shaders_)) {
            
            assert(programId != 0);
            assert(shaders.size() != 0);
            
            for ( auto &shader : this->shaders ) {
                GL3Shader* glshader = static_cast<GL3Shader*>(shader.get());
                ::glAttachShader(this->programId, glshader->getName());
            }
            
            GL3_CHECK();
        }
        
        ~ProgramAttacher() {
            assert(programId != 0);
            assert(shaders.size() != 0);
            
            // Detach the programs. They are not longer neccesary.
            for ( auto &shader : this->shaders ) {
                GL3Shader* glshader = static_cast<GL3Shader*>(shader.get() );
                ::glDetachShader( this->programId, glshader->getName() );
            }
            
            GL3_CHECK();
        }
        
        GLuint programId;
        std::list<std::unique_ptr<Shader>> shaders;
    };

    void GL3ShaderProgram::link() {
        assert (this->programId != 0);
        
        if (this->linked == false || this->modified == true || this->shaders.size() > 0) {
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
                infoLog.reserve(infoLogLength + 1);
                infoLog.resize(infoLogLength + 1);
                ::glGetProgramInfoLog(this->programId, infoLogLength, NULL, (GLchar*)infoLog.c_str());
                
                throw std::runtime_error(std::string("GL3ShaderProgram::link: Link failure:\n") + infoLog);
            }
            
            this->linked = true;
            this->modified = false;
        }
        
        GL3_CHECK();
    }

    bool GL3ShaderProgram::isLinked() const {
        assert (this->programId != 0);
        return this->linked;
    }

    bool GL3ShaderProgram::mustRelink() const {
        assert (this->programId != 0);
        return this->modified;
    }

    GLuint GL3ShaderProgram::getProgramId() const {
        assert (this->programId != 0);
        return this->programId;
    }

    void GL3ShaderProgram::release() {
        std::cout << "GL3ShaderProgram::release: Not implemented." << std::endl;
    }
}}}
