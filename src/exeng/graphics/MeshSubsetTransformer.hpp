
#pragma once

#ifndef __exeng_graphics_meshsubsettransformer_hpp__
#define __exeng_graphics_meshsubsettransformer_hpp__

#include <exeng/Config.hpp>
#include <exeng/Matrix.hpp>

namespace xe { namespace gfx {

	class EXENGAPI MeshSubset;
	class EXENGAPI MeshSubsetTransformer {
	public:
		MeshSubsetTransformer() {}
		~MeshSubsetTransformer() {}

		void transform(MeshSubset *subset, const Matrix4f &transformation);
	};
}}

#endif	// __exeng_graphics_meshsubsettransformer_hpp__
