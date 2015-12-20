
#ifndef __exeng_raytracer_raytracerapp_hpp__
#define __exeng_raytracer_raytracerapp_hpp__

#include <xe/input/EventData.hpp>
#include <xe/input/IEventHandler.hpp>
#include <xe/fw/GraphicsApplication.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/sg/SceneNodeAnimator.hpp>

#include "samplers/Sampler.hpp"

namespace xe { namespace raytracer {

	class ButtonPressHandler;
	class MoveAction;

    class RayTracerApp2 : public xe::fw::GraphicsApplication, public xe::input::IEventHandler {
    public:
        RayTracerApp2();
        virtual ~RayTracerApp2();

    public:
        virtual xe::BufferPtr getAssetsXmlData() override;
        virtual xe::gfx::GraphicsDriverPtr createGraphicsDriver() override;
        virtual xe::sg::AssetLibraryPtr createAssetLibrary() override;
        virtual xe::sg::SceneRendererPtr createSceneRenderer(xe::gfx::GraphicsDriver *graphicsDriver) override;
        virtual bool onInitialize() override;

        virtual void handleEvent(const xe::input::EventData &data) override;

        virtual void update(float seconds) override;
        virtual void render() override;

	private:
		void updateNodeRotation(float seconds, xe::sg::SceneNode *node);

		void updateCamera(float seconds);

    private:
        std::string RayTracerApp2::getPluginPath();

    private:
        xe::sg::Camera *camera = nullptr;
        xe::gfx::Mesh *screenMesh = nullptr;
        xe::gfx::Material *screenMaterial = nullptr;

		std::unique_ptr<ButtonPressHandler> buttonPressHandler;
		std::unique_ptr<MoveAction> moveAction;

		std::unique_ptr<::raytracer::samplers::Sampler> sampler;

		float rotationAngle = 0.0f;
    };
}}

#endif	// __exeng_raytracer_raytracerapp_hpp__
