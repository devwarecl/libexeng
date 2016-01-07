
#pragma once

#ifndef __xe_gfx_meshloaderlwo_hpp__
#define __xe_gfx_meshloaderlwo_hpp__

#include <functional>
#include <map>
#include <vector>
#include <memory>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/MeshLoader.hpp>

namespace xe { namespace gfx {
	class MeshLoaderLWO : public xe::gfx::MeshLoader {
	public:
		MeshLoaderLWO();
		virtual ~MeshLoaderLWO();
		virtual bool isSupported(const std::string &filename) override;
		virtual xe::gfx::MeshPtr load(const std::string &filename) override;

	private:
		struct Private;
		std::unique_ptr<Private> impl;
	};
}}

#endif 
