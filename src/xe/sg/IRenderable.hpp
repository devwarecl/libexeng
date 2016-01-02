#pragma once

#ifndef __xe_sg_irenderable_hpp__
#define __xe_sg_irenderable_hpp__

#include <xe/Config.hpp>
#include <xe/sg/Forward.hpp>

namespace xe { namespace sg {
	class EXENGAPI IRenderable {
	public:
		virtual ~IRenderable() {}
		virtual void renderWith(xe::sg::IRenderer *renderer) = 0;
	};
}}

#endif 
