
#ifndef __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
#define __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__

#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/scenegraph/SceneRenderer.hpp>

namespace exeng { namespace scenegraph {
    
    /**
     * @brief Quick'n dirty Scene Renderer.
     */
    class EXENGAPI GenericSceneRenderer : public SceneRenderer {
    public:
        GenericSceneRenderer(exeng::graphics::GraphicsDriver *graphicsDriver);
        
        virtual ~GenericSceneRenderer();
        
        virtual const Scene* getScene() const override;
        
        virtual void setScene(const Scene *scene) override;
        
        virtual void renderScene(const Camera *camera) override;
        
    private:
        struct Impl;
        Impl *impl = nullptr;
    };
}}

#endif  // __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
