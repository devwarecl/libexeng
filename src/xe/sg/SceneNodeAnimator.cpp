
#include "SceneNodeAnimator.hpp"

namespace xe { namespace sg {

	SceneNodeAnimator::SceneNodeAnimator()
	{
		this->setSceneNode(nullptr);
	}

	SceneNodeAnimator::SceneNodeAnimator(SceneNode *node)
	{
		this->setSceneNode(node);
	}

	SceneNodeAnimator::~SceneNodeAnimator() {}

	void SceneNodeAnimator::setSceneNode(SceneNode *node)
	{
		this->sceneNode = node;
	}

	SceneNode* SceneNodeAnimator::getSceneNode()
	{
		return this->sceneNode;
	}

	const SceneNode* SceneNodeAnimator::getSceneNode() const
	{
		return this->sceneNode;
	}
}}
