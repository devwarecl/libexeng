
#ifndef __EXENG_SCENEGRAPH_SCENENODEANIMATOR_HPP__
#define __EXENG_SCENEGRAPH_SCENENODEANIMATOR_HPP__

#include <memory>
#include <xe/sg/SceneNode.hpp>

namespace xe { namespace sg {

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

	typedef std::unique_ptr<SceneNodeAnimator> SceneNodeAnimatorPtr;
}}

#endif	// __EXENG_SCENEGRAPH_SCENENODEANIMATOR_HPP__
