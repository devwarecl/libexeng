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

#include <cassert>
#include <stdexcept>
#include <boost/checked_delete.hpp>

#include <xe/sg/Camera.hpp>
#include <xe/sg/Pipeline.hpp>

namespace xe { namespace sg {
    
    Camera::~Camera() {}

	void Camera::renderWith(xe::sg::Pipeline *renderer) {
		renderer->render(this);
	}
}}
