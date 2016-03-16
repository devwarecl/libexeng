/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <xe/sg/Geometry.hpp>
#include <xe/sg/Renderer.hpp>

namespace xe { namespace sg {
    Geometry::~Geometry() { }

	TypeInfo Geometry::getTypeInfo() const {
		return TypeId<Geometry>();
	}

	void Geometry::renderWith(xe::sg::Renderer *renderer) {
		renderer->render(this);
	}
}}
