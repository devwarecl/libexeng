
#pragma once

#ifndef __xe_demoapp_hpp__
#define __xe_demoapp_hpp__

#include <xe/ApplicationRT.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/input2/IKeyboard.hpp>
#include <xe/sg/Pipeline.hpp>
#include <xe/sg/SceneRendererGeneric.hpp>
#include <xe/sg/Scene.hpp>

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
        xe::gfx::GraphicsDriverPtr graphicsDriver;
        xe::input2::IKeyboard *keyboard = nullptr;
        xe::sg::PipelinePtr pipeline;
        xe::sg::SceneRendererPtr renderer;
        xe::sg::Scene scene;
        
        bool running = false;
    };
}

#endif 
