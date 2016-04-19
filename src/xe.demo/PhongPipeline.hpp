
#pragma once

#ifndef __xe_sg_phongrenderer_hpp__
#define __xe_sg_phongrenderer_hpp__

#include <xe/gfx/Forward.hpp>
#include <xe/gfx/ShaderProgram.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/VertexFormat.hpp>
#include <xe/sg/Pipeline.hpp>

namespace xe { namespace sg {
    class PhongPipeline : public xe::sg::Pipeline {
    public:
        explicit PhongPipeline(xe::gfx::GraphicsDriver *graphicsDriver);
    
        virtual ~PhongPipeline();
    
        virtual void beginFrame(const xe::Vector4f &color) override;
        virtual void endFrame() override;
    
        virtual void render(xe::sg::Light *) override;
        virtual void render(xe::sg::Camera *) override;
        virtual void render(xe::sg::Geometry *) override;
        virtual void render(xe::gfx::Mesh *) override;
    
        virtual void setModel(const xe::Matrix4f &) override;
    
        const xe::gfx::VertexFormat* getVertexFormat() const;
    
        const xe::gfx::MaterialFormat* getMaterialFormat() const;
    
    private:
        xe::gfx::GraphicsDriver *graphicsDriver = nullptr;
        xe::gfx::ModernModule *programmableModule = nullptr;
        xe::gfx::ShaderProgramPtr shaderProgram;
    
        xe::gfx::VertexFormat vertexFormat;
        xe::gfx::MaterialFormat materialFormat;
    };
}}

#endif
