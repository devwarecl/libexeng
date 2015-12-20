
#ifndef __RAYTRACER_LOADERS_LWOMESHLOADER_HPP__
#define __RAYTRACER_LOADERS_LWOMESHLOADER_HPP__

#include <functional>
#include <map>
#include <vector>
#include <memory>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/MeshLoader.hpp>

namespace raytracer { namespace loaders {
	class LwoMeshLoader : public xe::gfx::MeshLoader {
	public:
		LwoMeshLoader();
		virtual bool isSupported(const std::string &filename) override;
		virtual std::unique_ptr<xe::gfx::Mesh> load(const std::string &filename) override;

	private:
		struct Impl;
		std::unique_ptr<Impl> impl;
	};
}}

#endif // __RAYTRACER_LOADERS_LWOMESHLOADER_HPP__
