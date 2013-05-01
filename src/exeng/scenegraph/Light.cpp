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

#include "Light.hpp"

struct exeng::scenegraph::Light::Private {
    exeng::math::Vector3f position;
    exeng::math::Vector3f target;
    exeng::scenegraph::LightType::Enum lightType;
    float range;
    
    Private() {
        this->range = 1.0f;
    }
};


namespace exeng{
    namespace scenegraph {
        Light::Light() {
            this->impl = new Light::Private();
        }
        
        
        Light::~Light() {
            delete this->impl;
        }
        
        
        auto Light::getLightType() -> LightType::Enum  {
            return this->impl->lightType;
        }
        
        
        auto Light::setLightType(LightType::Enum lightType) -> void  {
            this->impl->lightType = lightType;
        }
        
        
        auto Light::setPosition(const Vector3f &pos) -> void  {
            this->impl->position = pos;
        }
        
        
        auto Light::getPosition() const -> Vector3f {
            return this->impl->position;
        }
        
        
        auto Light::setTarget(const Vector3f &target) -> void {
            this->impl->target = target;
        }
        
        
        auto Light::getTarget() -> Vector3f  {
            return this->impl->target;
        }
        
        
        auto Light::setRange(float range) -> void {
            if (range < 0.0f) {
                range = 0.0;
            }
            
            this->impl->range = range;
        }
        
        
        auto Light::getRange() const -> float {
            return this->impl->range;
        }
    }
}
