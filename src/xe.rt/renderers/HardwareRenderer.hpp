
#ifndef __EXENG_RAYTRACER_RENDERERS_HARDWARERENDERER_HPP__
#define __EXENG_RAYTRACER_RENDERERS_HARDWARERENDERER_HPP__

#include <memory>
#include <xe/gfx/MaterialLibrary.hpp>
#include <xe/sg/AssetsLibrary.hpp>
#include <xe/sg/SceneNodeData.hpp>
#include <xe/sg/GenericSceneRenderer.hpp>

#include "xe.rt/samplers/Sampler.hpp"

namespace xe { namespace raytracer { namespace renderers {

    class HardwareRendererPrivate;

    class HardwareRenderer : public xe::sg::RenderWrapper {
    public:
        explicit HardwareRenderer(xe::gfx::Texture *renderTarget, const xe::sg::AssetLibrary *assets, const xe::gfx::MaterialLibrary *materialLibrary, ::raytracer::samplers::Sampler *sampler);
        virtual ~HardwareRenderer();

        virtual Matrix4f getProjectionMatrix(const xe::sg::Camera *camera) override {
            return identity<float, 4>();
        }

        virtual void prepareCamera(const xe::sg::Camera *camera) override;

        virtual void beginFrame(const Vector4f &color) override;
        virtual void endFrame() override;

        virtual void setTransform(const Matrix4f &transform) override;

		virtual void renderNodeData(const xe::sg::SceneNodeData *data) override;

    private:
        std::unique_ptr<HardwareRendererPrivate> impl;
    };

    typedef std::unique_ptr<HardwareRenderer> HardwareRendererPtr;
}}}

#endif  // __EXENG_RAYTRACER_RENDERERS_HARDWARERENDERER_HPP__
