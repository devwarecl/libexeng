
#include "SoftwareRenderer.hpp"

#include <xe/sg/Camera.hpp>
#include <xe/sg/Ray.hpp>
#include <xe/sg/IntersectInfo.hpp>

namespace xe { namespace rt {
    
    inline int computeOffset(const xe::Vector2i &pixel, const xe::Vector2i &size) {
		assert(pixel.x >= 0);
		assert(pixel.y >= 0);
		assert(pixel.x < size.x);
		assert(pixel.y < size.y);

        return pixel.y*size.x + pixel.x;
    }
    
    inline xe::Vector2i computePixel(const int offset, const xe::Vector2i &size) {
        assert(offset >= 0);
        assert(offset < size.x*size.y);
        
        const int x = offset / size.y;
        const int y = offset % size.x;
        
        return xe::Vector2i(x, y);
    }
    
    inline xe::sg::Ray castRay (
        const xe::Vector2f &coordsf, 
        const xe::Vector2f &sizef, 
        const xe::Vector3f &cam_pos, 
        const xe::Vector3f &cam_up, 
        const xe::Vector3f &cam_dir, 
        const xe::Vector3f &cam_right) {
		
		// normalized coordinates
		const Vector2f nc = (coordsf / (sizef - Vector2f(1.0f, 1.0f)) ) - Vector2f(0.5f, 0.5f);
		const Vector3f image_point = nc.x * cam_right + nc.y * cam_up + cam_pos + cam_dir;
    
		const xe::sg::Ray ray = {
			cam_pos, 
			xe::normalize(image_point - cam_pos)
		};
        
		return ray;
	}    
    
    inline xe::sg::IntersectInfo selectResult(const xe::sg::IntersectInfo &first, const xe::sg::IntersectInfo &candidate) {

        if (!candidate.intersect) {
            return first;
        }
        
        if (candidate.distance < first.distance) {
            return candidate;
        }
    
        return first;
	}
    
    std::vector<xe::sg::Ray> generateRays (
        const xe::Vector2i &size, 
        const xe::Vector3f &cam_pos, 
        const xe::Vector3f &cam_up, 
        const xe::Vector3f &cam_dir, 
        const xe::Vector3f &cam_right) {
        
        assert(size.x > 0);
        assert(size.y > 0);
        
        const xe::Vector2f sizef = (xe::Vector2f)size;
        const int rayCount = size.x * size.y;
        std::vector<xe::sg::Ray> rays(rayCount);
        
        for (int i=0; i<rayCount; i++) {
            xe::Vector2i coord = computePixel(i, size);
            xe::Vector2f coordf = (xe::Vector2f)coord;
            xe::sg::Ray ray = castRay(coordf, sizef, cam_pos, cam_up, cam_dir, cam_right);
            
            rays.push_back(ray);
        }
        
        return rays;
    }
    
    void fillSurface(const xe::Vector4ub *pixels, const int size, const xe::Vector4ub &color) {
        assert(pixels);
        assert(size > 0);
        
        for (int i=0; i<size; i++) {   
            *pixels++ = color;
        }
    }
    
    SoftwareRenderer::SoftwareRenderer(xe::gfx::GraphicsDriver *driver_) : driver(driver_) {
        assert(driver);
    }
    
    SoftwareRenderer::~SoftwareRenderer() {}
    
    void SoftwareRenderer::beginFrame(const xe::Vector4f &color_) {
        color = color_;
        driver->beginFrame(color, xe::gfx::ClearFlags::Color);
    }
    
    void SoftwareRenderer::endFrame() {
        driver->endFrame();
    }
    
    void SoftwareRenderer::render(xe::sg::Light *light) {
        //! TODO: Add custom code
    
    }
    
    void SoftwareRenderer::render(xe::sg::Camera *camera) {
        view = camera->computeView();
        proj = camera->computeProj();
    }
    
    void SoftwareRenderer::render(xe::sg::Geometry *geometry) {
        //! TODO: Add custom code
    }
    
    void SoftwareRenderer::render(xe::gfx::Mesh *mesh) {
        //! TODO: Add custom code
    
    }
    
    void SoftwareRenderer::setModel(const xe::Matrix4f &model_) {
        model = model_;
    }
}}

#if 0

#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/sg/Ray.hpp>
#include <xe/sg/Camera.hpp>
#include <xe/sg/Geometry.hpp>
#include <xe/sg/Intersect.hpp>
#include <xe/sg/IntersectInfo.hpp>

#include "Sampler.hpp"
#include "JitteredSampler.hpp"

namespace xe { namespace rt {

    using namespace xe::gfx;
    using namespace xe::sg;
	using namespace ::raytracer::samplers;
    
	typedef Vector<std::uint8_t, 4> Vector4ub;
    
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
    
}}

#endif
