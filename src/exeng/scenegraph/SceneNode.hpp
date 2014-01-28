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


#ifndef __EXENG_SCENE_SCENENODE_HPP__
#define __EXENG_SCENE_SCENENODE_HPP__

#include <vector>

#include <exeng/Object.hpp>
#include <exeng/math/TMatrix.hpp>

namespace exeng { namespace scenegraph {

class EXENGAPI SceneNode;
class EXENGAPI SceneNodeData;

typedef std::vector<SceneNode*> SceneNodeVector;
typedef SceneNodeVector::iterator SceneNodeVectorIt;

/**
 * @brief Nodo de un grafo de escena. Representa a cualquier entidad existente en un 
 * grafo de escena, y que puede ser representada en cualquier tipo de medio. 
 */
class EXENGAPI SceneNode : public Object {
public:
    SceneNode();
    explicit SceneNode(const std::string& name);

    virtual ~SceneNode();

    virtual std::string toString() const;
    
    exeng::math::Matrix4f getTransform() const;
    
    void setTransform(const exeng::math::Matrix4f& transform);
    
    std::string getName() const;
    
    void setName(const std::string &name);
    
    int getChildCount() const;
    
    SceneNode* getChildPtr(int index) const;
    
    SceneNode* getChildPtr(const std::string& name) const;
    
    SceneNode* getChildPtr(const std::string& name);
    
    bool existChild(const std::string& name) const;
    
    bool hasParent() const;

    SceneNode* getParentPtr() const;
    
    void setParentPtr(SceneNode* parent);

    SceneNode* findNodePtr(const std::string &name) const;
    
    SceneNode* addChildPtr(SceneNode *childPtr);
    
    SceneNode* removeChildPtr(const std::string& name);

    SceneNode* removeChildPtr(SceneNode* childRef);

    SceneNode* addChildPtr(const std::string& name);
    
    void orphan();
    
    void setDataPtr(SceneNodeData* data);

    SceneNodeData* getDataPtr() const;
    
    const SceneNodeVector& getChilds() const;
    
private:
    struct Private;
    Private *impl;
};

}}

#endif
