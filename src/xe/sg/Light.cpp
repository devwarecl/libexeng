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

#include <xe/sg/Light.hpp>
#include <xe/sg/Pipeline.hpp>

#include <cassert>
#include <boost/checked_delete.hpp>

using namespace xe;
using namespace xe::sg;

namespace xe{ namespace sg {
    struct Light::Private {
        Vector3f position;
        Vector3f target;
        Vector4f ambient;
        Vector4f diffuse;
        Vector4f specular;
        LightType::Enum lightType;
        float range = 1.0f;
    };
}}

namespace xe{ namespace sg {
    Light::Light() : impl(new Light::Private()) {
    }
        
        
    Light::~Light() {
        boost::checked_delete(impl);
    }
        
        
    LightType::Enum Light::getLightType() const {
        assert(impl);
        return impl->lightType;
    }
        
        
    void Light::setLightType(LightType::Enum lightType) {
        assert(impl);
        impl->lightType = lightType;
    }
        
        
    void Light::setPosition(const Vector3f &pos){
        assert(impl);
        impl->position = pos;
    }
        
        
    Vector3f Light::getPosition() const {
        assert(impl);
        return impl->position;
    }
        
        
    void Light::setTarget(const Vector3f &target) {
        assert(impl);
        impl->target = target;
    }
        
        
    Vector3f Light::getTarget() const {
        assert(impl);
        return impl->target;
    }
        
        
    void Light::setRange(float range) {
        assert(impl);
            
        if (range < 0.0f) {
            range = 0.0;
        }
            
        impl->range = range;
    }
        
        
    float Light::getRange() const {
        assert(impl);
        return impl->range;
    }


    void Light::setAmbient(const xe::Vector4f &color) {
        assert(impl);

        impl->ambient = color;
    }

    void Light::setDiffuse(const xe::Vector4f &color)  {
        assert(impl);

        impl->diffuse = color;
    }

    void Light::setSpecular(const xe::Vector4f &color)  {
        assert(impl);

        impl->specular = color;
    }

    xe::Vector4f Light::getAmbient() const  {
        assert(impl);

        return impl->ambient;
    }

    xe::Vector4f Light::getDiffuse() const  {
        assert(impl);

        return impl->diffuse;
    }

    xe::Vector4f Light::getSpecular() const {
        assert(impl);

        return impl->specular;
    }

	void Light::renderWith(Pipeline *renderer) {
		renderer->render(this);
	}
}}
