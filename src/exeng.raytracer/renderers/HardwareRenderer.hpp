
#ifndef __EXENG_RAYTRACER_RENDERERS_HARDWARERENDERER_HPP__
#define __EXENG_RAYTRACER_RENDERERS_HARDWARERENDERER_HPP__

#include <memory>
#include <exeng/graphics/MaterialLibrary.hpp>
#include <exeng/scenegraph/AssetsLibrary.hpp>
#include <exeng/scenegraph/SceneNodeData.hpp>
#include <exeng/scenegraph/GenericSceneRenderer.hpp>

#include "exeng.raytracer/samplers/Sampler.hpp"

namespace exeng { namespace raytracer { namespace renderers {

    class HardwareRendererPrivate;

    class HardwareRenderer : public exeng::scenegraph::RenderWrapper {
    public:
        explicit HardwareRenderer(exeng::graphics::Texture *renderTarget, const exeng::scenegraph::AssetLibrary *assets, const exeng::graphics::MaterialLibrary *materialLibrary, ::raytracer::samplers::Sampler *sampler);
        virtual ~HardwareRenderer();

        virtual Matrix4f getProjectionMatrix(const exeng::scenegraph::Camera *camera) override {
            return identity<float, 4>();
        }

        virtual void prepareCamera(const exeng::scenegraph::Camera *camera) override;

        virtual void beginFrame(const Vector4f &color) override;
        virtual void endFrame() override;

        virtual void setTransform(const Matrix4f &transform) override;

		virtual void renderNodeData(const exeng::scenegraph::SceneNodeData *data) override;

    private:
        std::unique_ptr<HardwareRendererPrivate> impl;
    };

    typedef std::unique_ptr<HardwareRenderer> HardwareRendererPtr;
}}}

#endif  // __EXENG_RAYTRACER_RENDERERS_HARDWARERENDERER_HPP__
