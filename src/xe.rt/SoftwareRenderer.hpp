
#pragma once

#ifndef __xe_rt_softwarerenderer_hpp__
#define __xe_rt_softwarerenderer_hpp__

#include <xe/Matrix.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/sg/Renderer.hpp>

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
        xe::gfx::GraphicsDriver *driver = nullptr;
        xe::Matrix4f model = xe::identity<float, 4>();
        xe::Matrix4f view = xe::identity<float, 4>();
        xe::Matrix4f proj = xe::identity<float, 4>();
        xe::Vector4f color = xe::Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
    };
}}

#endif
