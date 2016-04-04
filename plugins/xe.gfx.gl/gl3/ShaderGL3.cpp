/**
 * @file ShaderGL3.cpp
 * @brief Definition of the ShaderGL3 class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "GL3.hpp"
#include "UtilGL3.hpp"
#include "ShaderGL3.hpp"
#include "DebugGL3.hpp"

#include <sstream>
#include <map>
#include <stdexcept>

namespace xe  { namespace gfx { namespace gl3 {
    ShaderGL3::ShaderGL3(ShaderType::Enum type) {
        this->name = 0;
        this->modified = false;
        this->compiled = false;
        this->type = type;
        this->name = ::glCreateShader(convShaderType(type));
        
        GL3_CHECK();
    }

    ShaderGL3::~ShaderGL3() {
        if (this->name != 0) {
            //! TODO: Remove the shader from the parent shader program.
            ::glDeleteShader(this->name);
            this->name = 0;
        }
    }

    TypeInfo ShaderGL3::getTypeInfo() const {
        return TypeId<ShaderGL3>();
    }

    void ShaderGL3::setSourceCode(const std::string &sourceCode) {
        this->sourceCode = sourceCode;
        this->modified = true;
    }

    std::string ShaderGL3::getSourceCode() const {
        return this->sourceCode;
    }

    bool ShaderGL3::isSourceModified() const {
        return this->modified;
    }

    void ShaderGL3::compile() {
        
        assert(!sourceCode.empty());
    
        if (this->modified == true || this->compiled == false) {
            const char* shaderSource = this->sourceCode.c_str();
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
                
                std::cerr << "ShaderGL3::compile: Compile failure in ";
                std::cerr << shaderTypeStr(this->type);
                std::cerr << " shader: \n" + infoLog;
                std::cerr << std::endl;
            }
            
            assert(status);
            
            GL3_CHECK();
            
            this->modified = false;
            this->compiled = true;
        }
    }

    bool ShaderGL3::isCompiled() const {
        return this->compiled;
    }

    ShaderType::Enum ShaderGL3::getType() const {
        return this->type;
    }

    GLuint ShaderGL3::getName() const {
        return this->name;
    }
}}}
