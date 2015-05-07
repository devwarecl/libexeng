
#include "ShaderLibrary.hpp"

#include <map>
#include <cassert>

namespace exeng { namespace graphics {

	struct ShaderLibrary::Private {
		GraphicsDriver *driver = nullptr;
		std::string language;
		std::map<std::string, ShaderPtr> shaders;
		std::map<std::string, ShaderProgramPtr> programs;
	};


	ShaderLibrary::ShaderLibrary(GraphicsDriver *driver) {
		this->impl = new ShaderLibrary::Private();
		this->impl->driver = driver;
	}
	
	ShaderLibrary::~ShaderLibrary() {
		delete this->impl;
	}

	Shader* ShaderLibrary::getShader(const std::string &name) {
		assert(impl != nullptr);

		Shader* shader = nullptr;

		auto pos = this->impl->shaders.find(name);

		if (pos != this->impl->shaders.end()) {
			shader = pos->second.get();
		}

		return shader;
	}

	Shader* ShaderLibrary::createShader(const std::string &name, ShaderType::Enum type) {
		assert(impl != nullptr);

		ShaderPtr shaderPtr = this->impl->driver->getModernModule()->createShader(type);
		Shader* shader = shaderPtr.get();

		this->impl->shaders[name] = std::move(shaderPtr);

		return shader;
	}

	ShaderProgram* ShaderLibrary::getProgram(const std::string &name) {
		assert(impl != nullptr);

		ShaderProgram* program = nullptr;

		auto pos = this->impl->programs.find(name);
		if (pos != this->impl->programs.end()) {
			program = pos->second.get();
		}

		return program;
	}

	ShaderProgram* ShaderLibrary::createProgram(const std::string &name) {
		assert(impl != nullptr);

		ShaderProgramPtr programPtr = this->impl->driver->getModernModule()->createShaderProgram();
		ShaderProgram* program = programPtr.get();

		this->impl->programs[name] = std::move(programPtr);

		return program;
	}
}}
