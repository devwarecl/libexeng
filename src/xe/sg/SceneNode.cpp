/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "SceneNode.hpp"

#include <cassert>
#include <vector>
#include <boost/checked_delete.hpp>
#include <boost/range/algorithm/find.hpp>

using namespace xe;
using namespace xe::sg;

namespace xe { namespace sg {

	typedef std::vector<SceneNodePtr> SceneNodePtrVector;
	typedef SceneNodePtrVector::iterator SceneNodePtrIterator;

    //! SceneNode private data
    struct SceneNode::Private {
        std::string name;
        Matrix4f transform = xe::identity<float, 4>();
        SceneNode* parent = nullptr;
        Renderable *renderable = nullptr;
		SceneNodePtrVector childs;
    };
}}

namespace xe { namespace sg {
        
    SceneNode::SceneNode(const std::string& name, SceneNode *parent, Renderable* renderable) {
        impl = new SceneNode::Private();
		
		this->setName(name);
		this->setParent(parent);
		this->setRenderable(renderable);
    }

    SceneNode::~SceneNode() {
        boost::checked_delete(impl);
    }
    
    std::string SceneNode::toString() const {
        assert(impl);

        if (!this->getParent()) {
            return this->getName();

        } else {
            return this->getParent()->toString() + "/" + this->getName();
        }
    }

    Matrix4f SceneNode::getTransform() const {
        assert(impl);

        return impl->transform;
    }

    void SceneNode::setTransform(const Matrix4f& transform) {
        assert(impl);

        impl->transform = transform;
    }

    std::string SceneNode::getName() const {
        assert(impl);

        return impl->name;
    }

    void SceneNode::setName(const std::string &name) {
        assert(impl);
		assert(this->getParent() && !this->getParent()->getChild(name));
        
        impl->name = name;
    }

    int SceneNode::getChildCount() const {
        assert(impl);
        return static_cast<int>(impl->childs.size());
    }

    SceneNode* SceneNode::getChild(int index) const {
        assert(impl);
        return impl->childs[index].get();
    }

    SceneNode* SceneNode::getChild(const std::string& name) const {
        assert(impl);

		auto &childs = impl->childs;
		auto childIt = std::find_if(childs.begin(), childs.end(), [name](const SceneNodePtr& child) {
			return child.get()->getName() == name;
		});

		SceneNode *child = nullptr;

		if (childIt != childs.end()) {
			child = childIt->get();
		}

		return child;
    }

    SceneNode* SceneNode::getParent() const {
        assert(impl);

		return impl->parent;
    }

    void SceneNode::setParent(SceneNode* parent) {
        assert(impl);

		SceneNodePtr this_;

		// remove from previous parent
		if (this->impl->parent) {
			auto &childs = parent->impl->childs;
			auto childIt = std::find_if(childs.begin(), childs.end(), [this](const SceneNodePtr &child) {
				return child.get() == this;
			});

			assert(childIt != childs.end());

			this_ = std::move(*childIt);
			childs.erase(childIt);
		}

		// update current parent
		this->impl->parent = parent;

		// append to new parent
		if (parent) {
			parent->impl->childs.push_back(std::move(this_));

		} else {
			this_.release();
		}
    }

	const SceneNode* SceneNode::findNode(const std::string &name) const {
		if (this->getName() == name) {
			return this;
		}

		for (int i=0; i<this->getChildCount(); i++) {
			const SceneNode *node = this->getChild(i)->findNode(name);

			if (node) {
				return node;
			}
		}

		return nullptr;
	}

	SceneNode* SceneNode::findNode(const std::string &name) {
		const SceneNode *node = const_cast<const SceneNode*>(this);

		node = node->findNode(name);

        return const_cast<SceneNode*>(node);
	}

    SceneNode* SceneNode::addChild(SceneNodePtr child) {
        assert(impl);
		assert(child);
		assert(!child->getParent());

		SceneNode *node = child.get();

		child->impl->parent = this;
		this->impl->childs.push_back(std::move(child));

		return node;
    }

    SceneNodePtr SceneNode::removeChild(SceneNode* child) {
        assert(impl);
		assert(child);
		assert(child->getParent());
		assert(child->getParent() == this);

		SceneNodePtr node;

		auto &childs = impl->childs;
		auto childIt = std::find_if(childs.begin(), childs.end(), [child](const SceneNodePtr &current) {
			return current.get() == child;
		});

		assert(childIt != childs.end());

		node = std::move(*childIt);
		
		childs.erase(childIt);

		node->impl->parent = nullptr;

		return node;
    }
	
	void SceneNode::setRenderable(Renderable *renderable) {
		assert(impl);

		impl->renderable = renderable;
	}

	Renderable* SceneNode::getRenderable() {
		assert(impl);

		return impl->renderable;
	}

	const Renderable* SceneNode::getRenderable() const {
		assert(impl);

		return impl->renderable;
	}
}}
