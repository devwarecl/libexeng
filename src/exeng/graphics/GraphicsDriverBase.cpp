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


#include "GraphicsDriverBase.hpp"
#include "Material.hpp"

#include <cassert>

using namespace exeng;
using namespace exeng::graphics;
using namespace exeng::math;

namespace exeng {
    namespace graphics {
        
        GraphicsDriverBase::GraphicsDriverBase() {
            this->model.identity();
            this->view.identity();
            this->projection.identity();
            this->modelView.identity();
            
            this->viewPort.set(0.0f);
            
            this->vertexBuffer = nullptr;
            this->indexBuffer = nullptr;
        }
        
        
        GraphicsDriverBase::~GraphicsDriverBase() {
        }
        
        
        DisplayMode GraphicsDriverBase::getDisplayMode() const {
            //return this->displayMode;
            
            return DisplayMode();
        }
        
        
        Matrix4f GraphicsDriverBase::getTransform(Transform transform) {
            assert( transform == Transform::World || 
                    transform == Transform::View || 
                    transform == Transform::Projection);
            
            switch (transform) {
                case Transform::World:      return this->model;
                case Transform::View:       return this->view;
                case Transform::Projection: return this->projection;
            }

			return Matrix4f();
        }
        
        
        const Material* GraphicsDriverBase::getMaterial() const {
            return this->material;
        }
        
        
        Rectf GraphicsDriverBase::getViewport() const {
            return this->viewPort;
        }
    }
}
