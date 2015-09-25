
#ifndef __exeng_raytracer_raytracerapp_hpp__
#define __exeng_raytracer_raytracerapp_hpp__

#include <exeng/input/EventData.hpp>
#include <exeng/input/IEventHandler.hpp>
#include <exeng/framework/GraphicsApplication.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/scenegraph/SceneNodeAnimator.hpp>

namespace exeng { namespace raytracer {

	class ButtonPressHandler;
	class MoveAction;

    class RayTracerApp2 : public exeng::framework::GraphicsApplication, public exeng::input::IEventHandler {
    public:
        RayTracerApp2();
        virtual ~RayTracerApp2();

    public:
        virtual exeng::BufferPtr getAssetsXmlData() override;
        virtual exeng::graphics::GraphicsDriverPtr createGraphicsDriver() override;
        virtual exeng::scenegraph::AssetLibraryPtr createAssetLibrary() override;
        virtual exeng::scenegraph::SceneRendererPtr createSceneRenderer(exeng::graphics::GraphicsDriver *graphicsDriver) override;
        virtual bool onInitialize() override;

        virtual void handleEvent(const exeng::input::EventData &data) override;

        virtual void update(float seconds) override;
        virtual void render() override;

	private:
		void updateNodeRotation(float seconds, exeng::scenegraph::SceneNode *node);

		void updateCamera(float seconds);

    private:
        std::string RayTracerApp2::getPluginPath();

    private:
        exeng::scenegraph::Camera *camera = nullptr;
        exeng::scenegraph::Mesh *screenMesh = nullptr;
        exeng::graphics::Material *screenMaterial = nullptr;

		std::unique_ptr<ButtonPressHandler> buttonPressHandler;
		std::unique_ptr<MoveAction> moveAction;

		float rotationAngle = 0.0f;
    };
}}

#endif	// __exeng_raytracer_raytracerapp_hpp__
