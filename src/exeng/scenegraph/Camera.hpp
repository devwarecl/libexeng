/**
 * @brief Define la interfaz para la clase de camaras, y sus clases de soporte
 */

#ifndef __EXENG_SCENEGRAPH_CAMERA_HPP__
#define __EXENG_SCENEGRAPH_CAMERA_HPP__

#include "../Object.hpp"
#include "../math/TVector.hpp"
#include "../math/TSize.hpp"
#include "../math/TBoundary.hpp"
#include "../scenegraph/SceneNodeData.hpp"

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
            auto setOrientation(const exeng::math::Vector3f &pos, const exeng::math::Vector3f& lookAt) -> void;
            
            
            /**
             * @brief setPosition
             * @param position
             */
            auto setPosition(const exeng::math::Vector3f &position) -> void;
            
            /**
             * @brief getPosition
             * @return 
             */
            auto getPosition() const -> exeng::math::Vector3f;
            
            /**
             * @brief setLookAt
             * @param lookAt
             */
            auto setLookAt(const exeng::math::Vector3f &lookAt) -> void;
            
            /**
             * @brief getLookAt
             * @return 
             */
            auto getLookAt() const -> exeng::math::Vector3f;
            
            /**
             * @brief getUp
             * @return 
             */
            auto getUp() const -> exeng::math::Vector3f;
            
            /**
             * @brief setUp
             * @param up
             */
            auto setUp(const exeng::math::Vector3f &up) -> void;
            
            /**
             * @brief setViewport
             * @param viewport
             */
            auto setViewport(const exeng::math::Rectf &viewport) -> void;
            
            /**
             * @brief getViewport
             * @return 
             */
            auto getViewport() const -> exeng::math::Rectf;
            
            
            /**
             * @brief setProjection
             * @param proj
             */
            auto setProjection(const CameraProjection &proj) -> void;
            
            
            /**
             * @brief getProjection
             * @return 
             */
            auto getProjection() const -> CameraProjection;
        
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif // __EXENG_SCENEGRAPH_CAMERA_HPP__
