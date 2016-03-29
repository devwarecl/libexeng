
#include "SoftwareRenderer.hpp"

#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/sg/Light.hpp>
#include <xe/sg/Camera.hpp>

namespace xe { namespace rt {
    
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
    
    inline int SoftwareRenderer::computeOffset(const xe::Vector2i &pixel, const xe::Vector2i &size) {
		assert(pixel.x >= 0);
		assert(pixel.y >= 0);
		assert(pixel.x < size.x);
		assert(pixel.y < size.y);

        return pixel.y*size.x + pixel.x;
    }
    
    inline xe::Vector2i SoftwareRenderer::computePixel(const int offset, const xe::Vector2i &size) {
        assert(offset >= 0);
        assert(offset < size.x*size.y);
        
        const int x = offset / size.y;
        const int y = offset % size.x;
        
        return xe::Vector2i(x, y);
    }
    
    inline xe::sg::Ray SoftwareRenderer::castRay (
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
    
    inline xe::sg::IntersectInfo SoftwareRenderer::selectResult(const xe::sg::IntersectInfo &first, const xe::sg::IntersectInfo &candidate) {
        if (!candidate.intersect) {
            return first;
        }
        
        if (candidate.distance < first.distance) {
            return candidate;
        }
    
        return first;
	}
    
    std::vector<xe::sg::Ray> SoftwareRenderer::generateRays (
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
    
    void SoftwareRenderer::fillSurface(xe::Vector4ub *pixels, const int size, const xe::Vector4ub &color) {
        assert(pixels);
        assert(size > 0);
        
        for (int i=0; i<size; i++) {   
            *pixels++ = color;
        }
    }
}}
