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

#include <cassert>
#include <boost/checked_delete.hpp>

using namespace exeng;
using namespace exeng::math;
using namespace exeng::scenegraph;


struct exeng::scenegraph::Light::Private {
    Vector3f position;
    Vector3f target;
    LightType lightType;
    float range;
    
    Private() {
        this->range = 1.0f;
    }
};


namespace exeng{
    namespace scenegraph {
        Light::Light() : impl(new Light::Private()) {
        }
        
        
        Light::~Light() {
            boost::checked_delete(this->impl);
        }
        
        
        LightType Light::getLightType() const {
            assert(this->impl != nullptr);
            return this->impl->lightType;
        }
        
        
        void Light::setLightType(LightType lightType) {
            assert(this->impl != nullptr);
            this->impl->lightType = lightType;
        }
        
        
        void Light::setPosition(const Vector3f &pos){
            assert(this->impl != nullptr);
            this->impl->position = pos;
        }
        
        
        Vector3f Light::getPosition() const {
            assert(this->impl != nullptr);
            return this->impl->position;
        }
        
        
        void Light::setTarget(const Vector3f &target) {
            assert(this->impl != nullptr);
            this->impl->target = target;
        }
        
        
        Vector3f Light::getTarget() const {
            assert(this->impl != nullptr);
            return this->impl->target;
        }
        
        
        void Light::setRange(float range) {
            assert(this->impl != nullptr);
            
            if (range < 0.0f) {
                range = 0.0;
            }
            
            this->impl->range = range;
        }
        
        
        float Light::getRange() const {
            assert(this->impl != nullptr);
            return this->impl->range;
        }
    }
}
