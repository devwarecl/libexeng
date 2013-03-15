/**
 * @brief Documentacion pendiente.
 */

#ifndef __EXENG_SCENEGRAPH_CAMERA_HPP__
#define __EXENG_SCENEGRAPH_CAMERA_HPP__

#include "../Object.hpp"
#include "../math/TVector.hpp"
#include "../math/TSize.hpp"
#include "../scenegraph/SceneNodeData.hpp"


namespace exeng
{
    namespace scenegraph
    {
        /**
         * @brief Un viewport
         */
        struct Viewport
        {
            exeng::math::Vector2f position;
            exeng::math::Size2f size;
            
            Viewport()
            {
                this->position = exeng::math::Vector2f(0.0f, 0.0f);
                this->size = exeng::math::Size2f(1.0f, 1.0f);
            }
        };
        
        
        /**
         * @brief The Projection struct
         */
        struct Projection
        {
            exeng::Float32 left, right;
            exeng::Float32 bottom, top;
            exeng::Float32 back, front;
            
            Projection()
            {
                this->left = this->bottom = this->back = -1.0f;
                this->right = this->top = this->front = 1.0f;
            }
        };
        
        
        /** 
         * @brief enum class ProjectionType
         */
        namespace ProjectionType
        {
            enum Enum    
            {
                Orthographic,
                Perspective
            };
        }
        
        
        /**
         * @brief The Camera class
         */
        class EXENGAPI Camera : public SceneNodeData
        {            
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
            auto setViewport(const Viewport &viewport) -> void;
            
            /**
             * @brief getViewport
             * @return 
             */
            auto getViewport() const -> Viewport;
            
            
            /**
             * @brief setProjection
             * @param proj
             */
            auto setProjection(const Projection &proj) -> void;
            
            
            /**
             * @brief getProjection
             * @return 
             */
            auto getProjection() -> Projection;
            
            
            /**
             * @brief setProjectionType
             * @param type
             */
            auto setProjectionType(ProjectionType::Enum projType) -> void;
            
            
            /**
             * @brief Regresa la proyeccion actual que usa la camara.
             * @return 
             */
            auto getProjectionType() -> ProjectionType::Enum;
            
            
        private:
            struct Private;
            Private *impl;
        };
    
    }
}

#endif // __EXENG_SCENEGRAPH_CAMERA_HPP__
