/**
 * @file IntersectInfo.cpp
 * @brief IntersectInfo class implementation.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "IntersectInfo.hpp"

namespace exeng {
    namespace scenegraph {
        IntersectInfo::IntersectInfo() {
			this->intersect = false;
			this->distance = 0.0f;
			this->normal = exeng::math::Vector3f(0.0f);
            this->point = exeng::math::Vector3f(0.0f);
			this->materialPtr = nullptr;
		} 
    }
}
