/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_CAMERA_HPP__
#define __EXENG_SCENEGRAPH_CAMERA_HPP__

#include <exeng/Object.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/math/TSize.hpp>
#include <exeng/math/TBoundary.hpp>
#include <exeng/scenegraph/SceneNodeData.hpp>

namespace exeng { namespace scenegraph {

/** 
 * @brief enum class ProjectionType
 */
enum class CameraProjectionType {
    Orthographic,
    Perspective
};

/**
 * @brief CameraProjection
 */
struct CameraProjection {
    exeng::math::Boxf box;
    exeng::scenegraph::CameraProjectionType type;
    
    CameraProjection() {
        this->box.set(1.0f);
        this->type = CameraProjectionType::Orthographic;
    }
};

/**
 * @brief Camera class
 */
class EXENGAPI Camera : public SceneNodeData {
public:
    Camera();
    virtual ~Camera();
    
    void 
    setOrientation(const exeng::math::Vector3f &pos, const exeng::math::Vector3f& lookAt);
    
    
    void 
    setPosition(const exeng::math::Vector3f &position);
    
    exeng::math::Vector3f 
    getPosition() const;
    
    
    void 
    setLookAt(const exeng::math::Vector3f &lookAt);
    
    exeng::math::Vector3f 
    getLookAt() const;
    
    
    exeng::math::Vector3f 
    getUp() const;
    
    void 
    setUp(const exeng::math::Vector3f &up);
    
    
    void 
    setViewport(const exeng::math::Rectf &viewport);
    
    exeng::math::Rectf 
    getViewport() const;
    
    
    void 
    setProjection(const CameraProjection &proj);
    
    CameraProjection 
    getProjection() const;

private:
    struct Private;
    Private *impl;
};

}}

#endif // __EXENG_SCENEGRAPH_CAMERA_HPP__
