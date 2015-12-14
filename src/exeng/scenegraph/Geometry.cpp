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

#include <exeng/scenegraph/Geometry.hpp>

namespace exeng { namespace scenegraph {
    Geometry::~Geometry() { }

	TypeInfo Geometry::getTypeInfo() const {
		return TypeId<Geometry>();
	}
}}
