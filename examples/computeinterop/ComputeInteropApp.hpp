
#pragma once 

#ifndef __computeinteropapp_hpp__
#define __computeinteropapp_hpp__

#include <xe/ApplicationRT.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/MaterialLibrary.hpp>
#include <xe/sg/Scene.hpp>
#include <xe/sg/SceneRenderer.hpp>
#include <xe/sg/Renderer.hpp>

#include "PerspectiveCamera.hpp"
#include "PhongRenderer.hpp"
#include "MeshManipulator.hpp"

class ComputeInteropApp : public xe::ApplicationRT {
public:
	ComputeInteropApp();
	virtual ~ComputeInteropApp();

	virtual void initialize() override;
	virtual void terminate() override;

	virtual void doEvents() override;
	virtual void update(const float seconds) override;
	virtual void render() override;

	virtual bool isRunning() const override;

private:
	xe::gfx::GraphicsDriverPtr createGraphicsDriver();

	xe::sg::ScenePtr createScene();

private:
	bool running = false;
	xe::gfx::GraphicsDriverPtr graphicsDriver;
	xe::gfx::MaterialLibraryPtr materialLibrary;
	xe::sg::ScenePtr scene;
	PerspectiveCamera camera;

	std::unique_ptr<PhongRenderer> renderer;
	std::unique_ptr<MeshManipulator> meshManipulator;

	xe::sg::SceneRendererPtr sceneRenderer;
	xe::gfx::MeshManager *meshManager = nullptr;
	xe::gfx::TextureManager *textureManager = nullptr;
	xe::input2::IInputManager *inputManager = nullptr;
	xe::input2::KeyboardStatus *keyboardStatus = nullptr;
};

#endif 
