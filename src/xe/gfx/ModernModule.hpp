

#ifndef __EXENG_GRAPHICS_MODERNMODULE_HPP__
#define __EXENG_GRAPHICS_MODERNMODULE_HPP__

#include <memory>
#include <list>
#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include <xe/gfx/Shader.hpp>
#include <xe/gfx/ShaderProgram.hpp>

namespace xe { namespace gfx {

	struct ShaderSource {
		xe::gfx::ShaderType::Enum type = xe::gfx::ShaderType::Vertex;
		std::string source;

		ShaderSource() {}
		ShaderSource(xe::gfx::ShaderType::Enum type_, std::string source_) : type(type_), source(source_) {}
	};

	class EXENGAPI ModernModule {
	protected:
		virtual ~ModernModule();

	public:
        /**
         * @brief Creates a new shader of the specified type.
         * @param type A member of the ShaderType enumeration.
         * @return 
         */
        virtual ShaderPtr createShader(ShaderType::Enum type) = 0;
        
		virtual ShaderPtr createShader(ShaderType::Enum type, const char* dataSource, const int dataSize);

		virtual ShaderPtr createShader(ShaderType::Enum type, const std::string &shaderSource);

        /**
         * @brief Create a new shader program, specific to the current graphics driver.
         * @return A new shader program, instance of an derived implementation class of the 
         * ShaderProgram abstract class.
         */
        virtual ShaderProgramPtr createShaderProgram() = 0;
		
		virtual void setShaderProgram(const ShaderProgram *program) = 0;

		virtual const ShaderProgram* getShaderProgram() const = 0;

		/**
		 * @brief Set the value of the specified global variable in the currently setted material's shader program.
		 */
		virtual void setProgramGlobal(const std::string &globalName, const Vector4f &value) = 0;

		/**
		 * @brief Set the value of the specified global variable in the currently setted material's shader program.
		 */
		virtual void setProgramGlobal(const std::string &globalName, const Matrix4f &value) = 0;

		virtual void setProgramGlobal(const int index, const Vector4f &value) = 0;

		virtual void setProgramGlobal(const int index, const Matrix4f &value) = 0;

		virtual ShaderProgramPtr createShaderProgram(const std::list<std::string> &vertexShaderSrcs, const std::list<std::string> &fragmentShaderSrcs);

		virtual ShaderProgramPtr createShaderProgram(std::string &vertexShaders, std::string &fragmentShaders);

		virtual ShaderProgramPtr createShaderProgram(const std::list<ShaderSource> &shaderSources);
	};
}}

#endif	// __EXENG_GRAPHICS_MODERNMODULE_HPP__
