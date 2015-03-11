
#ifndef __EXENG_SCENEGRAPH_SCENENODEANIMATOR_HPP__
#define __EXENG_SCENEGRAPH_SCENENODEANIMATOR_HPP__

#include <exeng/scenegraph/SceneNode.hpp>

namespace exeng { namespace scenegraph {

	class EXENGAPI SceneNodeAnimator {
	public:
		SceneNodeAnimator();
		SceneNodeAnimator(SceneNode *node);

		virtual ~SceneNodeAnimator() = 0;

		void setSceneNode(SceneNode *node);

		SceneNode* getSceneNode();

		const SceneNode* getSceneNode() const;

		virtual void update(double seconds) = 0;

	private:
		SceneNode *sceneNode = nullptr;
	};
}}

#endif	// __EXENG_SCENEGRAPH_SCENENODEANIMATOR_HPP__
