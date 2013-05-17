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

#include "../math/TVector.hpp"
#include "SceneNodeData.hpp"

namespace exeng {
    namespace scenegraph {
        /**
         * @brief Available instanciable light types.
         */
        enum class LightType {
            Directional,
            Point,
            Spot
        };
        
        /**
         * @brief Documentacion pendiente
         */
        class EXENGAPI Light : public SceneNodeData {
        public:
            Light();
            
            virtual ~Light();
            
            /**
             * @brief Devuelve el tipo de luz actual de esta luz.
             * @return Miembro de la enumeracion Exeng::SceneGraph::LightType::Enum
             */
            LightType getLightType() const;
            
            /**
             * @brief Establece el tipo de luz actual de la luz.
             * @param lightType El tipo de luz a actual, miembro de la enumeracion Exeng::SceneGraph::LightType::Enum
             */
            void setLightType(LightType lightType);
            
            /**
             * @brief Establece la posicion en coordenadas locales de la luz.
             * @param pos La posicion de la luz, en coordenadas locales, como un Vector3f
             */
            void setPosition(const exeng::math::Vector3f& pos);
            
            /**
             * @brief Devuelve la posicion actual de la luz.
             * @return La posicion actual de la luz, en coordenadas locales, sin ningun tipo 
             * de transformacion
             */
            exeng::math::Vector3f getPosition() const;
            
            /**
             * @brief Establece el punto hacia el cual la luz apunta. Aplicacble solo si la luz es de tipo SpotLight.
             * @param El punto hacia el cual la luz apunta, en coordenadas locales
             */
            void setTarget(const exeng::math::Vector3f& target);
            
            /**
             * @brief Devuelve el punto hacia el cual la luz apunta. Por defecto es la posicion (0.0, -1.0, 0.0)
             * Solo aplicable si la luz es de tipo SpotLight.
             * @return El punto hacia el cual la luz apunta, como un objeto de tipo Vector3f
             */
            exeng::math::Vector3f getTarget() const;
            
            /**
             * @brief Establece el rango de la luz
             * @param range El rango de la luz. El rango de la luz corresponde al radio de influencia que tiene 
             * la luz desde su posicion en la escena. Objetos que esten fuera del rango no se veran afectados por 
             * la luz
             */
            void setRange(float range);
            
            /**
             * @brief Devuelve el rango de la luz actual. Solo aplicable para luces puntuales.
             * @return El rango actual de la luz, en unidades del Mundo.
             */
            float getRange() const;
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif // __EXENG_SCENEGRAPH_LIGHT_HPP__
