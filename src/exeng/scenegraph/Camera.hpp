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

#ifndef __EXENG_SCENEGRAPH_CAMERA_HPP__
#define __EXENG_SCENEGRAPH_CAMERA_HPP__

#include <exeng/Object.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/math/TSize.hpp>
#include <exeng/math/TBoundary.hpp>
#include <exeng/scenegraph/SceneNodeData.hpp>

namespace exeng {
    namespace scenegraph {
        
        /** 
         * @brief enum class ProjectionType
         */
        enum class CameraProjectionType {
            Orthographic,
            Perspective
        };
        
        
        /**
         * @brief The Projection struct
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
         * @brief The Camera class
         */
        class EXENGAPI Camera : public SceneNodeData {
        public:
            Camera();
            
            virtual ~Camera();
            
            /**
             * @brief Establece la orientacion de la camara
             * @param pos
             * @param lookAt
             */
            void setOrientation(const exeng::math::Vector3f &pos, const exeng::math::Vector3f& lookAt);
            
            
            /**
             * @brief setPosition
             * @param position
             */
            void setPosition(const exeng::math::Vector3f &position);
            
            /**
             * @brief getPosition
             * @return 
             */
            exeng::math::Vector3f getPosition() const;
            
            /**
             * @brief setLookAt
             * @param lookAt
             */
            void setLookAt(const exeng::math::Vector3f &lookAt);
            
            /**
             * @brief getLookAt
             * @return 
             */
            exeng::math::Vector3f getLookAt() const;
            
            /**
             * @brief getUp
             * @return 
             */
            exeng::math::Vector3f getUp() const;
            
            /**
             * @brief setUp
             * @param up
             */
            void setUp(const exeng::math::Vector3f &up);
            
            /**
             * @brief setViewport
             * @param viewport
             */
            void setViewport(const exeng::math::Rectf &viewport);
            
            /**
             * @brief getViewport
             * @return 
             */
            exeng::math::Rectf getViewport() const;
            
            
            /**
             * @brief setProjection
             * @param proj
             */
            void setProjection(const CameraProjection &proj);
            
            
            /**
             * @brief getProjection
             * @return 
             */
            CameraProjection getProjection() const;
        
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif // __EXENG_SCENEGRAPH_CAMERA_HPP__
