
#pragma once

#ifndef __xe_gfx_programmablepipeline_hpp__
#define __xe_gfx_programmablepipeline_hpp__

#include <memory>
#include <list>
#include <vector>
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
		
		/**
         * @brief Set the current shader program with the specified one.
         */
		virtual void setShaderProgram(const ShaderProgram *program) = 0;

		virtual const ShaderProgram* getShaderProgram() const = 0;

		virtual void setProgramParam(const std::string &name, const int count, const int dim, DataType::Enum dataType, const void *value) = 0;

		template <typename Type>
		void setProgramParam(const std::string &name, Type value) {
			this->setProgramParam(name, 1, 1, DataTypeTraits<Type>::Enum, &value);
		}

		template<typename Type, int Size>
		void setProgramParam(const std::string &name, const Vector<Type, Size> &value) {
			static_assert(Size >= 0, "");
			static_assert(Size <= 4, "");

			this->setProgramParam(name, 1, Size, DataTypeTraits<Type>::Enum, &value);
		}

		template<typename Type, int Size>
		void setProgramParam(const std::string &name, const int count, const Vector<Type, Size> *values) {
			static_assert(Size >= 0);
			static_assert(Size <= 4);
			assert(values);
			assert(count > 0);

			this->setProgramParam(name, count, Size, DataTypeTraits<Type>::Enum, values);
		}

		template<typename Type>
		void setProgramParam(const std::string &name, const std::vector<Type> &values) {
			assert(values.size() > 0);

			this->setProgramParam(name, values.size(), 1, DataTypeTraits<Type>::Enum, values.data());
		}

		template<typename Type, int Size>
		void setProgramParam(const std::string &name, const std::vector<Vector<Type, Size>> &values) {
			static_assert(Size >= 0);
			static_assert(Size <= 4);
			assert(values.size() > 0);

			this->setProgramParam(name, values.size(), Size, DataTypeTraits<Type>::Enum, values.data());
		}
		
		virtual void setProgramMatrix(const std::string &name, const int count, const xe::Matrix4f *matrices) = 0;

		void setProgramMatrix(const std::string &name, const xe::Matrix4f &matrix) {
			this->setProgramMatrix(name, 1, &matrix);
		}

		void setProgramMatrix(const std::string &name, const std::vector<xe::Matrix4f> &matrices) {
			this->setProgramMatrix(name, matrices.size(), matrices.data());
		}

		virtual ShaderProgramPtr createShaderProgram(const std::list<std::string> &vertexShaderSrcs, const std::list<std::string> &fragmentShaderSrcs);

		virtual ShaderProgramPtr createShaderProgram(std::string &vertexShaders, std::string &fragmentShaders);

		virtual ShaderProgramPtr createShaderProgram(const std::list<ShaderSource> &shaderSources);
	};
}}

#endif	// __EXENG_GRAPHICS_MODERNMODULE_HPP__
