
#pragma once

#ifndef __xe_sg_softwarepipeline_hpp__
#define __xe_sg_softwarepipeline_hpp__

#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/sg/Pipeline.hpp>
#include <xe/sg/Ray.hpp>
#include <xe/sg/IntersectInfo.hpp>

namespace xe { namespace sg {
    class EXENGAPI SoftwarePipeline : public xe::sg::Pipeline {
    public:
        explicit SoftwarePipeline(xe::gfx::GraphicsDriver *driver);
        virtual ~SoftwarePipeline();
        
		virtual void beginFrame(const xe::Vector4f &color) override;
		virtual void endFrame() override;

		virtual void render(xe::sg::Light *) override;
		virtual void render(xe::sg::Camera *) override;
		virtual void render(xe::sg::Geometry *) override;
		virtual void render(xe::gfx::Mesh *) override;

		virtual void setModel(const xe::Matrix4f &) override;
		
		virtual const xe::gfx::VertexFormat* getVertexFormat() const override;
    
        virtual const xe::gfx::MaterialFormat* getMaterialFormat() const override;

    private:
        struct Private;
        Private *impl = nullptr;
    };
}}

#endif
