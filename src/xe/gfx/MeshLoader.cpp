/**
 * @file IMeshLoader.cpp
 * @brief IMeshLoader destructor implementation.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <xe/gfx/MeshLoader.hpp>

namespace xe { namespace gfx {
    
	MeshLoader::MeshLoader() {}

	MeshLoader::~MeshLoader() {}

	void MeshLoader::setGraphicsDriver(GraphicsDriver *driver) {
		this->graphicsDriver = driver;
	}

	GraphicsDriver* MeshLoader::getGraphicsDriver() {
		return this->graphicsDriver;
	}
}}
