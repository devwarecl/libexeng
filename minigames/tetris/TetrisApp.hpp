
#pragma once

#ifndef __xe_demoapp_hpp__
#define __xe_demoapp_hpp__

#include <xe/ApplicationRT.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/sg/Pipeline.hpp>
#include <xe/sg/SceneRendererGeneric.hpp>
#include <xe/sg/Scene.hpp>
#include <xe/input2/IKeyboard.hpp>

#include "PerspectiveCamera.hpp"

namespace xe {

    class DemoApp : public xe::ApplicationRT {
    public:
        virtual void initialize() override;
		virtual void terminate() override;

		virtual void doEvents() override;
		virtual void update(const float seconds) override;
		virtual void render() override;

        virtual bool isRunning() const override {
            return running;   
        }
        
    private:
        xe::sg::ScenePtr createScene();
        
        xe::gfx::MeshPtr createCubeMesh(xe::gfx::Material *material);
        
        xe::gfx::MaterialPtr createMaterial(const xe::Vector4f &color);
        
    private:
        xe::gfx::GraphicsDriverPtr graphicsDriver;
        xe::input2::IKeyboard *keyboard = nullptr;
        xe::sg::PipelinePtr pipeline;
        xe::sg::SceneRendererPtr renderer;
        xe::sg::ScenePtr scene;
        
        xe::sg::PerspectiveCamera camera;
        
        xe::gfx::MeshPtr cubeMesh1;
        xe::gfx::MeshPtr cubeMesh2;
        xe::gfx::MeshPtr cubeMesh3;
        xe::gfx::MaterialPtr material1;
        xe::gfx::MaterialPtr material2;
        xe::gfx::MaterialPtr material3;
        
        bool running = false;
    };
}

#endif 
