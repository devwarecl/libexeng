
#pragma once

#ifndef __xe_rt_raytracerapp_hpp__
#define __xe_rt_raytracerapp_hpp__

#include <xe/ApplicationRT.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/MaterialLibrary.hpp>
#include <xe/sg/Scene.hpp>
#include <xe/sg/SceneRenderer.hpp>
#include <xe/sg/Pipeline.hpp>

#include "PerspectiveCamera.hpp"

namespace xe { namespace rt {

    class RayTracerApp : public ApplicationRT {
    public:
        RayTracerApp();
        virtual ~RayTracerApp();
    
        virtual void initialize();
		virtual void terminate();

		virtual void doEvents();
		virtual void update(const float seconds);
		virtual void render();

		virtual bool isRunning() const;
    
    private:
        xe::gfx::GraphicsDriverPtr createGraphicsDriver();
    
        xe::sg::ScenePtr createScene();
    
    private:
        bool running = false;
        xe::gfx::GraphicsDriverPtr graphicsDriver;
        xe::gfx::MaterialLibraryPtr materialLibrary;
        xe::sg::ScenePtr scene;
        PerspectiveCamera camera;
    
		xe::sg::PipelinePtr pipeline;
        xe::sg::SceneRendererPtr sceneRenderer;
        xe::gfx::MeshManager *meshManager = nullptr;
        xe::gfx::TextureManager *textureManager = nullptr;
        xe::input2::IInputManager *inputManager = nullptr;
        xe::input2::KeyboardStatus *keyboardStatus = nullptr;
    };
}}

#endif 
