/**
 * @file GraphicsDriver.cpp
 * @brief Stub implementation of the graphics driver abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "GraphicsDriver.hpp"

namespace xe { namespace gfx {
	GraphicsDriver::~GraphicsDriver() {}
    
    Material2Ptr GraphicsDriver::createMaterial(const MaterialFormat2 *) {
        return Material2Ptr();
    }
}}
