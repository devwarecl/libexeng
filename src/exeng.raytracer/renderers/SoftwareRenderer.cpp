
#include "SoftwareRenderer.hpp"
#include <exeng/Exception.hpp>

namespace exeng { namespace raytracer { namespace renderers {

    using namespace exeng::graphics;
    using namespace exeng::scenegraph;

    struct SoftwareRenderer::Private {
        Texture *renderTarget = nullptr;
        Matrix4f modelView = identity<float, 4>();

        uint32_t getOffset(const Vector2i &point) {
            Vector3i size = this->renderTarget->getSize();
        
#ifdef EXENG_DEBUG
            if (point.x < 0 || point.y < 0) {
                EXENG_THROW_EXCEPTION("");
            }
        
            if (point.x >= size.x || point.y >= size.y) {
                throw std::invalid_argument("");
            }
#endif  
            int offset = point.y * size.x + point.x;
            return static_cast<uint32_t>(offset);
        }

        void putPixel(std::uint32_t *backbuffer, const Vector2i &point, const std::uint32_t color) {
            backbuffer += this->getOffset(point);
            *backbuffer = color;
        }


    };

    SoftwareRenderer::SoftwareRenderer(Texture *renderTarget) {
        this->impl = std::make_unique<SoftwareRenderer::Private>();
        this->impl->renderTarget = renderTarget;
    }

    SoftwareRenderer::~SoftwareRenderer() {}

    void SoftwareRenderer::setTransform(const Matrix4f &transform) {
        this->impl->modelView = transform;
    }

	void SoftwareRenderer::renderNodeData(const SceneNodeData *data) {
        Matrix4f modelView = this->impl->modelView;

    }
}}}
