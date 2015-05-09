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
#include <exeng/Enum.hpp>
#include <exeng/Vector.hpp>
#include <exeng/Size.hpp>
#include <exeng/Boundary.hpp>
#include <exeng/scenegraph/SceneNodeData.hpp>

namespace exeng { namespace scenegraph {
    /** 
     * @brief 
     */
    struct CameraProjectionType : public Enum {
        enum Enum {
            Orthographic,
            Perspective
        };
    };

    /**
     * @brief CameraProjection
     */
    struct CameraProjection {
        Boxf box = Boxf(1.0);
        CameraProjectionType::Enum type = CameraProjectionType::Orthographic;
		
        CameraProjection() {}
		CameraProjection(const Boxf &box, CameraProjectionType::Enum type) {
            this->box = box;
            this->type = type;
        }

		static CameraProjection buildPerspectiveProj(float fov, float aspect, float znear, float zfar) {
			Boxf box;

			return {box, CameraProjectionType::Perspective};
		}
    };

    /**
     * @brief 
     */
    class EXENGAPI Camera : public SceneNodeData {
    public:
        Camera();
        virtual ~Camera();

        void setOrientation(const exeng::Vector3f &pos, const exeng::Vector3f& lookAt);
        
        void setPosition(const exeng::Vector3f &position);
        exeng::Vector3f getPosition() const;
        
        void setLookAt(const exeng::Vector3f &lookAt);
        exeng::Vector3f getLookAt() const;
        
        exeng::Vector3f getUp() const;
        void setUp(const exeng::Vector3f &up);
        
        void setViewport(const exeng::Rectf &viewport);
        exeng::Rectf getViewport() const;
        
        void setProjection(const CameraProjection &proj);
        CameraProjection getProjection() const;
        
        const Vector3f* getData() const;
        
    private:
        struct Private;
        Private *impl;
    };
}}

#endif // __EXENG_SCENEGRAPH_CAMERA_HPP__
