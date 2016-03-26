
#pragma once

#ifndef __xe_rt_softwarerenderer_hpp__
#define __xe_rt_softwarerenderer_hpp__

#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/sg/Renderer.hpp>
#include <xe/sg/Ray.hpp>
#include <xe/sg/IntersectInfo.hpp>

namespace xe { namespace rt {
    class SoftwareRenderer : public xe::sg::Renderer {
    public:
        explicit SoftwareRenderer(xe::gfx::GraphicsDriver *driver);
        virtual ~SoftwareRenderer();
        
		virtual void beginFrame(const xe::Vector4f &color) override;
		virtual void endFrame() override;

		virtual void render(xe::sg::Light *) override;
		virtual void render(xe::sg::Camera *) override;
		virtual void render(xe::sg::Geometry *) override;
		virtual void render(xe::gfx::Mesh *) override;

		virtual void setModel(const xe::Matrix4f &) override;
		
    private:
        int computeOffset(const xe::Vector2i &pixel, const xe::Vector2i &size);
        
        xe::Vector2i computePixel(const int offset, const xe::Vector2i &size);
        
        xe::sg::Ray castRay (
            const xe::Vector2f &coordsf, 
            const xe::Vector2f &sizef, 
            const xe::Vector3f &cam_pos, 
            const xe::Vector3f &cam_up, 
            const xe::Vector3f &cam_dir, 
            const xe::Vector3f &cam_right);
        
        xe::sg::IntersectInfo selectResult(const xe::sg::IntersectInfo &first, const xe::sg::IntersectInfo &candidate);
        
        std::vector<xe::sg::Ray> generateRays (
            const xe::Vector2i &size, 
            const xe::Vector3f &cam_pos, 
            const xe::Vector3f &cam_up, 
            const xe::Vector3f &cam_dir, 
            const xe::Vector3f &cam_right);
        
        void fillSurface(xe::Vector4ub *pixels, const int size, const xe::Vector4ub &color);
        
    private:
        xe::gfx::GraphicsDriver *driver = nullptr;
        xe::gfx::Texture *texture = nullptr;
        xe::Matrix4f model = xe::identity<float, 4>();
        xe::Matrix4f view = xe::identity<float, 4>();
        xe::Matrix4f proj = xe::identity<float, 4>();
        xe::Vector4f color = xe::Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
        
        xe::Vector4ub *surface = nullptr;
    };
}}

#endif
