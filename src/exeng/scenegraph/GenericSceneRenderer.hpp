
#ifndef __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
#define __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__

#include <stack>
#include <exeng/Matrix.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/scenegraph/SceneRenderer.hpp>
#include <exeng/scenegraph/SceneNode.hpp>

namespace exeng { namespace scenegraph {
    
    /**
     * @brief Quick'n dirty Scene Renderer.
     */
    class EXENGAPI GenericSceneRenderer : public SceneRenderer {
    public:
        GenericSceneRenderer(exeng::graphics::GraphicsDriver *graphicsDriver);
        virtual ~GenericSceneRenderer();
        
        virtual void renderScene(const Camera *camera) override;

	private:
		void renderSceneNode(std::stack<Matrix4f> *matrixStack, const SceneNode *node);

	private:
		exeng::graphics::GraphicsDriver *graphicsDriver = nullptr;
    };
}}

#endif  // __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
