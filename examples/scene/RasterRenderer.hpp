
#pragma once

#ifndef __rasterrenderer_hpp__
#define __rasterrenderer_hpp__

#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/sg/Pipeline.hpp>

class RasterRenderer : public xe::sg::Pipeline {
public:
	explicit RasterRenderer(xe::gfx::GraphicsDriver *driver_);
	virtual ~RasterRenderer() {}

	virtual void beginFrame(const xe::Vector4f &color) override;
	virtual void endFrame() override;

	virtual void render(xe::sg::Light *light) override;
	virtual void render(xe::sg::Camera *camera) override;
	virtual void render(xe::sg::Geometry *geometry) override;
	virtual void render(xe::gfx::Mesh *mesh) override;

	virtual void setModel(const xe::Matrix4f &transformation) override;
    
    virtual const xe::gfx::VertexFormat* getVertexFormat() const override {
        return nullptr;
    }
    
    virtual const xe::gfx::MaterialFormat* getMaterialFormat() const override {
        return nullptr;
    }
private:
	xe::gfx::GraphicsDriver *driver = nullptr;
	xe::gfx::ModernModule *programmableModule = nullptr;
};

#endif
