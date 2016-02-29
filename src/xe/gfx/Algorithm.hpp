
#pragma once

#ifndef __xe_gfx_algorithm_hpp__
#define __xe_gfx_algorithm_hpp__

#include <xe/Config.hpp>
#include <xe/Buffer.hpp>
#include <xe/Matrix.hpp>
#include <xe/Vector.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/gfx/IndexFormat.hpp>
#include <xe/gfx/VertexFormat.hpp>

namespace xe { namespace gfx {
    extern EXENGAPI void transform(MeshSubset *subset, const Matrix4f &transformation);
    extern EXENGAPI void transform(Mesh *mesh, const Matrix4f &transformation);
}}

#endif	// __xe_gfx_transform_hpp__
