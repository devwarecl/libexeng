
#include "ModernModule.hpp" 

namespace exeng { namespace graphics {

	ModernModule::~ModernModule() {}

	ShaderProgramPtr ModernModule::createShaderProgram(const std::list<std::string> &vertexShaderSrcs, const std::list<std::string> &fragmentShaderSrcs) {
		ShaderProgramPtr shaderProgram;

		// create vertex shaders
		for (const std::string &source : vertexShaderSrcs) {
			ShaderPtr shader = this->createShader(ShaderType::Vertex, source);
			shader->compile();

			shaderProgram->addShader(std::move(shader));
		}

		// create fragment shaders
		for (const std::string &source : fragmentShaderSrcs) {
			ShaderPtr shader = this->createShader(ShaderType::Fragment, source);
			shader->compile();

			shaderProgram->addShader(std::move(shader));
		}

		shaderProgram->link();

		return shaderProgram;
	}

	ShaderProgramPtr ModernModule::createShaderProgram(std::string &vertexShaderSrc, std::string &fragmentShaderSrc) {
		std::list<std::string> vertexShaderSrcs;
		std::list<std::string> fragmentShaderSrcs;

		vertexShaderSrcs.push_back(vertexShaderSrc);
		fragmentShaderSrcs.push_back(fragmentShaderSrc);

		return this->createShaderProgram(vertexShaderSrcs, fragmentShaderSrcs);
	}

	ShaderPtr ModernModule::createShader(ShaderType::Enum type, const char* dataSource, const int dataSize) {
		std::string shaderSource;

		shaderSource.resize(dataSize);
		std::memcpy(const_cast<char*>(shaderSource.c_str()), dataSource, dataSize);

		return this->createShader(type, shaderSource);
	}

	ShaderPtr ModernModule::createShader(ShaderType::Enum type, const std::string &shaderSource) {
		ShaderPtr shader = this->createShader(type);

		shader->setSourceCode(shaderSource);

		return shader;
	}

	/*
	ShaderProgramPtr ModernModule::createShaderProgram(const std::list<std::pair<int, char*>> &vertexShaders,  const std::list<std::pair<int, char*>> &fragmentShaders)
	{
	}
	*/
}}
