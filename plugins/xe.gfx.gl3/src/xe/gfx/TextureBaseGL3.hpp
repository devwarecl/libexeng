/**
 * @file TextureGL3.hpp
 * @brief Definition of the OpenGL 3 Texture class
 */


/*
 * Copyright (c) 2016 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#pragma once

#ifndef __xe_gfx_texturebasegl3_hpp__
#define __xe_gfx_texturebasegl3_hpp__

#include <xe/gfx/Texture.hpp>

#include "GL3.hpp"

namespace xe { namespace gfx {

	class TextureBaseGL3 : public Texture {
	public:
		TextureBaseGL3();

		virtual ~TextureBaseGL3();


	protected:
		GLuint id = 0;
		PixelFormat::Enum format;

		
	};
}}

#endif
