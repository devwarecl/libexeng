
#include "HardwareRenderer.hpp"
#include "HardwareRendererPrivate.hpp"

#include <ostream>
#include <fstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>

namespace xe { namespace raytracer { namespace renderers {
    
    using namespace xe::gfx;
    using namespace xe::sg;

    HardwareRenderer::HardwareRenderer(Texture *renderTarget, const AssetLibrary *assets, const MaterialLibrary *materialLibrary, ::raytracer::samplers::Sampler *sampler) {
		this->impl = std::make_unique<HardwareRendererPrivate>(renderTarget, assets, materialLibrary, sampler);
    }

    HardwareRenderer::~HardwareRenderer() {}

    void HardwareRenderer::setTransform(const Matrix4f &transform) {
        this->impl->setTransform(transform);
    }

    void HardwareRenderer::renderNodeData(const SceneNodeData *data) {
        this->impl->computeSynthesisBuffer(data);
    }

    void HardwareRenderer::prepareCamera(const Camera *camera) {
        this->impl->generateRays(camera);
    }

    void HardwareRenderer::beginFrame(const Vector4f &color) {
        this->impl->clearSynthesisBuffer();
    }

    void HardwareRenderer::endFrame() {
        this->impl->computeImage();
    }
}}}
