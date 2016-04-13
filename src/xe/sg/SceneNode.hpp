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

#pragma once

#ifndef __xe_sg_scenenode_hpp__
#define __xe_sg_scenenode_hpp__

#include <memory>
#include <vector>

#include <xe/Object.hpp>
#include <xe/Matrix.hpp>
#include <xe/Collection.hpp>
#include <xe/sg/Forward.hpp>

namespace xe { namespace sg {
    /**
     * @brief Node of the Scene Graph.
     * 
     * Represent any existing entity on a 3D-World
     * 
     * @TODO: Clean the interface.
     */

	class EXENGAPI SceneNode;
	typedef std::unique_ptr<SceneNode> SceneNodePtr;

    class EXENGAPI SceneNode : public Object {
    public:
        SceneNode (
			const std::string& name="", 
			SceneNode *parent=nullptr, 
			Renderable* renderable=nullptr
		);

        virtual ~SceneNode();

        virtual std::string toString() const override;
        
        xe::Matrix4f getTransform() const;
        void setTransform(const xe::Matrix4f& transform);
        
        std::string getName() const;
        void setName(const std::string &name);
        
		void setRenderable(Renderable *renderable);
		Renderable* getRenderable();
		const Renderable* getRenderable() const;

		SceneNode* getParent() const;
        void setParent(SceneNode* parent);

        int getChildCount() const;
        SceneNode* getChild(int index) const;
        SceneNode* getChild(const std::string &name) const;
        
        const SceneNode* findNode(const std::string &name) const;
		SceneNode* findNode(const std::string &name);
        
        SceneNode* addChild(SceneNodePtr child);
        SceneNodePtr removeChild(SceneNode* child);

		SceneNode* addChild(const xe::Matrix4f &transformation, xe::sg::Renderable *renderable) {
			auto sceneNode = std::make_unique<SceneNode>();

			sceneNode->setTransform(transformation);
			sceneNode->setRenderable(renderable);

			return this->addChild(std::move(sceneNode));
		}

    private:
        struct Private;
        Private *impl = nullptr;
    };
}}

#endif
