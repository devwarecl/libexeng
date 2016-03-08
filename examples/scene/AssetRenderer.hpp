
#pragma once

#ifndef __assetrenderer_hpp__
#define __assetrenderer_hpp__

#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/sg/IRenderer.hpp>

class AssetRenderer : public xe::sg::IRenderer {
public:
	explicit AssetRenderer(xe::gfx::GraphicsDriver *driver_);
	virtual ~AssetRenderer() {}

	virtual void render(xe::sg::Light *light) override;
	virtual void render(xe::sg::Camera *camera) override;
	virtual void render(xe::sg::Geometry *geometry) override;
	virtual void render(xe::gfx::Mesh *mesh) override;

	virtual void setModel(const xe::Matrix4f &transformation) override;

protected:
	xe::Matrix4f computeProjViewModel() const;

private:
	xe::gfx::GraphicsDriver *driver = nullptr;
	xe::Matrix4f proj;
	xe::Matrix4f view;
	xe::Matrix4f model;
};

#endif