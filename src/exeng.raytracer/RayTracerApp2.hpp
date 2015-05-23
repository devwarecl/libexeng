
#ifndef __exeng_raytracer_raytracerapp_hpp__
#define __exeng_raytracer_raytracerapp_hpp__

#include <exeng/scenegraph/SceneNodeAnimator.hpp>
#include <exeng/input/EventData.hpp>
#include <exeng/input/IEventHandler.hpp>
#include <exeng/framework/GraphicsApplication.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/scenegraph/Mesh.hpp>

namespace exeng { namespace raytracer {

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
        std::string RayTracerApp2::getPluginPath();

    private:
        exeng::scenegraph::SceneNodeAnimatorPtr animator;
        exeng::scenegraph::Camera *camera = nullptr;
        exeng::scenegraph::Mesh *screenMesh = nullptr;
        exeng::graphics::Material *screenMaterial = nullptr;
    };
}}

#endif	// __exeng_raytracer_raytracerapp_hpp__
