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

#ifndef __EXENG_SCENEGRAPH_LIGHT_HPP__
#define __EXENG_SCENEGRAPH_LIGHT_HPP__

#include <exeng/Vector.hpp>
#include <exeng/Enum.hpp>
#include <exeng/scenegraph/SceneNodeData.hpp>

namespace exeng { namespace scenegraph {
    /**
     * @brief Available instanciable light types.
     */
    struct LightType : public Enum {
        enum Enum {
            Directional,
            Point,
            Spot
        };
    };

    class EXENGAPI Light : public SceneNodeData {
        friend class Scene;

    public:
        Light();
        virtual ~Light();

        /**
         * @brief 
         */
        LightType::Enum getLightType() const;
            
        /**
         * @brief 
         */
        void setLightType(LightType::Enum lightType);
            
        /**
         * @brief 
         */
        void setPosition(const exeng::Vector3f& pos);
            
        /**
         * @brief 
         */
        exeng::Vector3f getPosition() const;
            
        /**
         * @brief 
         */
        void setTarget(const exeng::Vector3f& target);
            
        /**
         * @brief 
         */
        exeng::Vector3f getTarget() const;
            
        /**
         * @brief 
         */
        void setRange(float range);
            
        /**
         * @brief 
         */
        float getRange() const;
            
    private:
        struct Private;
        Private *impl;
    };
}}

#endif // __EXENG_SCENEGRAPH_LIGHT_HPP__
