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

#include <memory>

#include <exeng/Vector.hpp>
#include <exeng/Boundary.hpp>
#include <exeng/Buffer.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/Primitive.hpp>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/graphics/IndexFormat.hpp>

namespace exeng { namespace scenegraph {
    /**
     * @brief Component for the Mesh class.
     */
    /*
    struct MeshPart {
        const exeng::graphics::Material *material = nullptr;
        std::unique_ptr<Buffer> vertexBuffer;
        std::unique_ptr<Buffer> indexBuffer;
        exeng::graphics::Primitive::Enum primitiveType = exeng::graphics::Primitive::TriangleList;
        exeng::graphics::VertexFormat vertexFormat;
        exeng::graphics::IndexFormat::Enum indexFormat = exeng::graphics::IndexFormat::Index32;
    };
    */
}}

#endif
