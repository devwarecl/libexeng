
#pragma once

#ifndef __xe_sg_irenderer_hpp__
#define __xe_sg_irenderer_hpp__

#include <xe/Config.hpp>
#include <xe/Matrix.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/sg/Forward.hpp>

namespace xe { namespace sg {
	class EXENGAPI IRenderer {
	public:
		virtual ~IRenderer() {}
		
		virtual void render(xe::sg::Light *) = 0;
		virtual void render(xe::sg::Camera *) = 0;
		virtual void render(xe::sg::Geometry *) = 0;
		virtual void render(xe::gfx::Mesh *) = 0;

		virtual void setTransformation(const xe::Matrix4f &) = 0;
	};
}}

#endif 
