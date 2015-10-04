
#include "SoftwareRenderer.hpp"

#include <exeng/Exception.hpp>
#include <exeng/graphics/MeshSubset.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/Camera.hpp>
#include <exeng/scenegraph/Intersect.hpp>
#include <exeng/scenegraph/IntersectInfo.hpp>

#include "exeng.raytracer/samplers/Sampler.hpp"
#include "exeng.raytracer/samplers/JitteredSampler.hpp"

namespace exeng { namespace raytracer { namespace renderers {

    using namespace exeng::graphics;
    using namespace exeng::scenegraph;
	using namespace ::raytracer::samplers;

    struct SoftwareRenderer::Private {
        Texture *renderTarget = nullptr;
		void* textureData = nullptr;
        Matrix4f modelView = identity<float, 4>();
		const AssetLibrary *assets = nullptr;
		const MaterialLibrary *materialLibrary = nullptr;
		const Camera *camera = nullptr;
		Sampler *sampler = nullptr;
    };

	inline int offset(const Vector2i &pixel, const Vector2i &size) {
		assert(pixel.x >= 0);
		assert(pixel.y >= 0);
		assert(pixel.x < size.x);
		assert(pixel.y < size.y);

        return pixel.y*size.x + pixel.x;
    }

	inline int put_pixel(std::uint32_t *pixels, const Vector2i &pixel, const Vector2i &size, const std::uint32_t color) {
		*(pixels + offset(pixel, size)) = color;
	}

	inline Ray cast_ray(const Vector2i &pixel, const Vector2i &size, const Camera *camera, const Vector2f &sample) {
		const Vector2f coordsf = pixel + sample;

		const Vector3f cam_pos = camera->getPosition();
		const Vector3f cam_up = camera->getUp();
		const Vector3f cam_dir = normalize(camera->getLookAt() - cam_pos);
		const Vector3f cam_right = normalize(cross(cam_dir, cam_up));
    
		const Vector2f normalized_coords = (coordsf / (size - Vector2f(1.0f, 1.0f)) ) - Vector2f(0.5f, 0.5f);
		const Vector3f image_point = normalized_coords.x * cam_right + normalized_coords.y * cam_up + cam_pos + cam_dir;
    
		const Ray ray = {
			cam_pos, 
			normalize(image_point - cam_pos) + Vector3f(sample.x, sample.y, 0.0f)
		};
    
		return ray;
	}
	
	inline IntersectInfo trace_ray(const Ray &ray, std::list<SceneNode *> nodes) {
		IntersectInfo info;
		IntersectInfo result;

		result.distance = std::numeric_limits<float>::infinity();

		for (SceneNode *node : nodes) {
			Geometry *geometry = static_cast<Geometry*>(node->getData());

			if (geometry->hit(ray, &info) && info.distance < result.distance) {
				result = info;
			}
		}

		return result;
	}

	inline Vector4f convert(std::uint32_t color) {
		typedef Vector<std::uint8_t, 4> Vector4ub;
		const float factor = 1.0f/255.0f;
		
		return factor * (Vector4f)Vector4ub((const std::uint8_t*)(&color));
	}

	inline std::uint32_t convert(Vector4f color) {
		return 0;
	}

    SoftwareRenderer::SoftwareRenderer(Texture *renderTarget, const AssetLibrary *assets, const MaterialLibrary *materialLibrary, Sampler *sampler) {
        this->impl = std::make_unique<SoftwareRenderer::Private>();
        this->impl->renderTarget = renderTarget;
		this->impl->assets = assets;
		this->impl->materialLibrary = materialLibrary;
		this->impl->sampler = sampler;
    }

    SoftwareRenderer::~SoftwareRenderer() {}

    void SoftwareRenderer::setTransform(const Matrix4f &transform) {
        this->impl->modelView = transform;
    }

	void SoftwareRenderer::renderNodeData(const SceneNodeData *data) {
        Matrix4f modelView = this->impl->modelView;
    }

	void SoftwareRenderer::prepareCamera(const Camera *camera) {
		this->impl->camera = camera;
	}

	void SoftwareRenderer::beginFrame(const Vector4f &color) {
		this->impl->textureData = this->impl->renderTarget->lock();

	}

    void SoftwareRenderer::endFrame() {

	}
}}}
