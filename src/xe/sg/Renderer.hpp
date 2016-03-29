
#pragma once

#ifndef __xe_sg_renderer_hpp__
#define __xe_sg_renderer_hpp__

#include <xe/Config.hpp>
#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/gfx/VertexFormat.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/sg/Forward.hpp>

namespace xe { namespace sg {
	class EXENGAPI Renderer {
	public:
		virtual ~Renderer();
		
		virtual void beginFrame(const xe::Vector4f &color) = 0;
		virtual void endFrame() = 0;

		virtual void render(xe::sg::Light *) = 0;
		virtual void render(xe::sg::Camera *) = 0;
		virtual void render(xe::sg::Geometry *) = 0;
		virtual void render(xe::gfx::Mesh *) = 0;

		virtual void setModel(const xe::Matrix4f &) = 0;

        virtual const xe::gfx::VertexFormat* getVertexFormat() const = 0;
    
        virtual const xe::gfx::MaterialFormat* getMaterialFormat() const = 0;
	};

	typedef std::unique_ptr<Renderer> RendererPtr;
}}

#endif 
