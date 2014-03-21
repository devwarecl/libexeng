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

#include <exeng/scenegraph/MeshPart.hpp>

namespace exeng { namespace scenegraph {
    MeshPart::MeshPart() {
        this->material = nullptr;
        this->vertexBuffer = nullptr;
        this->indexBuffer = nullptr;
        this->primitiveType = exeng::graphics::Primitive::TriangleList;
    }
}}
