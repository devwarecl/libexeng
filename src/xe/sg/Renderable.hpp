#pragma once

#ifndef __xe_sg_irenderable_hpp__
#define __xe_sg_irenderable_hpp__

#include <xe/Config.hpp>
#include <xe/sg/Forward.hpp>

namespace xe { namespace sg {
	class EXENGAPI Renderable {
	public:
		virtual ~Renderable();
		virtual void renderWith(xe::sg::Renderer *renderer) = 0;
	};
}}

#endif 
