
#ifndef __RAYTRACER_LOADERS_LWOMESHLOADER_HPP__
#define __RAYTRACER_LOADERS_LWOMESHLOADER_HPP__

#include <functional>
#include <map>
#include <vector>
#include <memory>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/graphics/MeshSubset.hpp>
#include <exeng/graphics/Mesh.hpp>
#include <exeng/graphics/MeshLoader.hpp>

namespace raytracer { namespace loaders {
	class LwoMeshLoader : public exeng::graphics::MeshLoader {
	public:
		LwoMeshLoader();
		virtual bool isSupported(const std::string &filename) override;
		virtual std::unique_ptr<exeng::graphics::Mesh> load(const std::string &filename, exeng::graphics::GraphicsDriver *graphicsDriver) override;

	private:
		struct Impl;
		std::unique_ptr<Impl> impl;
	};
}}

#endif // __RAYTRACER_LOADERS_LWOMESHLOADER_HPP__
