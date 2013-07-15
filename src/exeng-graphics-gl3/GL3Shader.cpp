/**
 * @file GL3Shader.cpp
 * @brief Definition of the GL3Shader class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include "GL3.hpp"
#include "GL3Utils.hpp"
#include "GL3Shader.hpp"
#include "GL3Debug.hpp"

#include <sstream>
#include <map>
#include <stdexcept>

namespace exeng  {
namespace graphics {
namespace gl3 {


GL3Shader::GL3Shader(ResourceFactory* factory, ShaderType type) : Shader(factory) {
    this->name = 0;
    this->modified = false;
    this->compiled = false;
    this->type = type;
    this->name = ::glCreateShader(convShaderType(type));
    
    GL3_CHECK();
}


GL3Shader::~GL3Shader() {
    if (this->name != 0) {
        //! TODO: Remove the shader from the parent shader program.
        ::glDeleteShader(this->name);
        this->name = 0;
    }
}


TypeInfo GL3Shader::getTypeInfo() const {
    return TypeInfo::get<GL3Shader>();
}


void GL3Shader::setSourceCode(const std::string &sourceCode) {
    this->sourceCode = sourceCode;
    this->modified = true;
}


std::string GL3Shader::getSourceCode() const {
    return this->sourceCode;
}


bool GL3Shader::isSourceModified() const {
    return this->modified;
}


void GL3Shader::compile() {
    if (this->sourceCode.empty() == true) {
        throw std::runtime_error("GL3Shader::compile: "
                                 "The source code must be non empty.");
    }
    
    if (this->modified == true || this->compiled == false ) {
        const char* shaderSource = this->sourceCode.c_str( );
        ::glShaderSource( this->name, 1, &shaderSource, NULL );
        ::glCompileShader( this->name );
        
        // Check for shader compilation errors
        GLint status;
        ::glGetShaderiv(this->name, GL_COMPILE_STATUS, &status);
        
        if (status == GL_FALSE) {
            // Get the log string length
            GLint infoLogLength;
            ::glGetShaderiv(this->name, GL_INFO_LOG_LENGTH, &infoLogLength);
            
            // Get the log string
            std::string infoLog;
            infoLog.reserve(infoLogLength + 1);
            infoLog.resize(infoLogLength + 1);
            ::glGetShaderInfoLog(this->name, infoLogLength, NULL, (GLchar*) infoLog.c_str());
            
            throw std::runtime_error("GL3Shader::compile: Compile failure in " + 
                                     shaderTypeStr(this->type) + " shader: \n" + infoLog);
        }
        
        GL3_CHECK();
        
        this->modified = false;
        this->compiled = true;
    }
}


bool GL3Shader::isCompiled() const {
    return this->compiled;
}


ShaderType GL3Shader::getType() const {
    return this->type;
}


GLuint GL3Shader::getName() const {
    return this->name;
}


void GL3Shader::release() {
    std::cout << "GL3Shader::release: Not implemented." << std::endl;
}


}
}
}
