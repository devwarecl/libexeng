
#include "SoftwareRenderer.hpp"

#include <xe/Exception.hpp>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/sg/Ray.hpp>
#include <xe/sg/Camera.hpp>
#include <xe/sg/Geometry.hpp>
#include <xe/sg/Intersect.hpp>
#include <xe/sg/IntersectInfo.hpp>

#include "xe.rt/samplers/Sampler.hpp"
#include "xe.rt/samplers/JitteredSampler.hpp"

namespace xe { namespace raytracer { namespace renderers {

    using namespace xe::gfx;
    using namespace xe::sg;
	using namespace ::raytracer::samplers;

	
	typedef Vector<std::uint8_t, 4> Vector4ub;

	inline int offset(const Vector2i &pixel, const Vector2i &size) {
		assert(pixel.x >= 0);
		assert(pixel.y >= 0);
		assert(pixel.x < size.x);
		assert(pixel.y < size.y);

        return pixel.y*size.x + pixel.x;
    }

	inline int put_pixel(Vector4ub *pixels, const Vector2i &pixel, const Vector2i &size, const Vector4ub &color) {
		*(pixels + offset(pixel, size)) = color;
	}

	inline Ray cast_ray(const Vector2i &pixel, const Vector2i &size, const Camera *camera) {
		const Vector2f coordsf = pixel;

		const Vector3f cam_pos = camera->getPosition();
		const Vector3f cam_up = camera->getUp();
		const Vector3f cam_dir = normalize(camera->getLookAt() - cam_pos);
		const Vector3f cam_right = normalize(cross(cam_dir, cam_up));
		
		const Vector2f normalized_coords = (coordsf / (size - Vector2f(1.0f, 1.0f)) ) - Vector2f(0.5f, 0.5f);
		const Vector3f image_point = normalized_coords.x * cam_right + normalized_coords.y * cam_up + cam_pos + cam_dir;
    
		const Ray ray = {
			cam_pos, 
			normalize(image_point - cam_pos)
		};
    
		return ray;
	}
	
	inline IntersectInfo trace_ray(const Ray &ray, std::list<SceneNode*> nodes) {
		IntersectInfo info;
		IntersectInfo result;

		result.distance = std::numeric_limits<float>::infinity();

		for (SceneNode *node : nodes) {
			Geometry *geometry = /*static_cast<Geometry*>(node->getData())*/nullptr;

			if (geometry->hit(ray, &info) && info.distance < result.distance) {
				result = info;
			}
		}

		return result;
	}

	inline Vector4f convert_color(const Vector4ub &color) {
		const float factor = 1.0f/255.0f;
		return factor * (Vector4f)color;
	}

	inline Vector4ub convert_color(const Vector4f &color) {
		return (Vector4ub)(255.0f * color);
	}

	inline void fill_backbuffer(Vector4ub *pixels, const Vector2i &size, Vector4ub color) {
		for (int i=0; i<size.x*size.y; i++) {
			*(pixels + i) = color;
		}
	}

    struct SoftwareRenderer::Private {
        Texture *renderTarget = nullptr;
		void* textureData = nullptr;
        Matrix4f modelView = identity<float, 4>();
		const AssetLibrary *assets = nullptr;
		const MaterialLibrary *materialLibrary = nullptr;
		const Camera *camera = nullptr;
		Sampler *sampler = nullptr;

		std::vector<Ray> rays;
		std::vector<IntersectInfo> synthesis;

		void generateRays() {
			rays.resize(size.x * size.y);

			for (int y=0; y<size.y; y++) {
				for (int x=0; x<size.x; x++) {
					const int i = offset({x, y}, this->size);
					rays[i] = cast_ray({x, y}, size, camera);
				}
			}

			synthesis.resize(rays.size());
			for (IntersectInfo &info : synthesis) {
				info.distance = std::numeric_limits<float>::infinity();
			}
		}

		void trace(SceneNodeData *data) {
			if (!data) {
				return;
			}

			if (data->getTypeInfo() == TypeId<Mesh>()) {
				Mesh *mesh = static_cast<Mesh*>(data);

				for (int y=0; y<size.y; y++) {
					for (int x=0; x<size.x; x++) {
						const int i = offset({x, y}, size);
						mesh->hit(rays[i], &synthesis[i]);
					}
				}
			}
		}

		void synthetize() {

		}

		Vector2i size;
    };

    SoftwareRenderer::SoftwareRenderer(Texture *renderTarget, const AssetLibrary *assets, const MaterialLibrary *materialLibrary, Sampler *sampler) {
        this->impl = std::make_unique<SoftwareRenderer::Private>();
        this->impl->renderTarget = renderTarget;
		this->impl->assets = assets;
		this->impl->materialLibrary = materialLibrary;
		this->impl->sampler = sampler;

		this->impl->size = this->impl->renderTarget->getSize();
		
    }

    SoftwareRenderer::~SoftwareRenderer() {}

    void SoftwareRenderer::setTransform(const Matrix4f &transform) {
        this->impl->modelView = transform;
    }

	void SoftwareRenderer::renderNodeData(const SceneNodeData *data) {
		assert(data);

        // Matrix4f modelView = this->impl->modelView;
		if (data->getTypeInfo() == TypeId<Geometry>()) {

		}
    }

	void SoftwareRenderer::prepareCamera(const Camera *camera) {
		this->impl->camera = camera;

		this->impl->generateRays();
	}

	void SoftwareRenderer::beginFrame(const Vector4f &color) {

	}

    void SoftwareRenderer::endFrame() {

	}
}}}
