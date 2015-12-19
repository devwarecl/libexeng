
#ifndef __EXENG_GRAPHICS_SHADERLIBRARY_HPP__
#define __EXENG_GRAPHICS_SHADERLIBRARY_HPP__

#include <memory>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/graphics/Shader.hpp>
#include <exeng/graphics/ShaderProgram.hpp>

namespace xe { namespace gfx {	

	class EXENGAPI ShaderLibrary {
	public:
		explicit ShaderLibrary(GraphicsDriver *driver);

		virtual ~ShaderLibrary();
	
		Shader* getShader(const std::string &name);

		Shader* createShader(const std::string &name, ShaderType::Enum type);

		ShaderProgram* getProgram(const std::string &name);

		ShaderProgram* createProgram(const std::string &name);

	private:
		struct Private;
		Private *impl = nullptr;
	};

	typedef std::unique_ptr<ShaderLibrary> ShaderLibraryPtr;
}}

#endif	// __EXENG_GRAPHICS_SHADERLIBRARY_HPP__
