/**
 * @file Definition of the MeshPart structure.
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_MESHPART_HPP__
#define __EXENG_SCENEGRAPH_MESHPART_HPP__

#include <cstdint>
#include <vector>

#include <exeng/math/TVector.hpp>
#include <exeng/math/TBoundary.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/IndexBuffer.hpp>
#include <exeng/graphics/VertexBuffer.hpp>
#include <exeng/graphics/Primitive.hpp>

namespace exeng { namespace scenegraph {
    /**
     * @brief Component for the Mesh class.
     */
    struct EXENGAPI MeshPart {
        const exeng::graphics::Material *material;
        exeng::graphics::VertexBuffer *vertexBuffer;
        exeng::graphics::IndexBuffer *indexBuffer;
        exeng::graphics::Primitive::Enum primitiveType;
        
        MeshPart();
    };
}}

#endif
