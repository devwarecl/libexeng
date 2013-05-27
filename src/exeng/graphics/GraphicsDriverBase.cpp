/**
 * @file GraphicsDriverBase.cpp
 * @brief Implementation of the GraphicsDriverBase abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <exeng/graphics/GraphicsDriverBase.hpp>

#include <cassert>
#include <boost/range/algorithm/find_if.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/VertexBuffer.hpp>
#include <exeng/graphics/IndexBuffer.hpp>
#include <exeng/graphics/HeapVertexBuffer.hpp>
#include <exeng/graphics/HeapIndexBuffer.hpp>

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
            
            this->viewport.set(0.0f);
            this->material = nullptr;
        }
        
        
        GraphicsDriverBase::~GraphicsDriverBase() {
        }
        
        
        Matrix4f GraphicsDriverBase::getTransform(Transform transform) {
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
            return this->viewport;
        }
        
        
        VertexBuffer* GraphicsDriverBase::createVertexBuffer( const VertexFormat &format, 
                                                              int count ) {
            auto *vbuffer = new HeapVertexBuffer(format, count);
            this->objects.push_back(vbuffer);
            
            return vbuffer;
        }
        
        
        IndexBuffer* GraphicsDriverBase::createIndexBuffer( IndexFormat indexFormat, 
                                                            int indexCount ) {
            auto *indexBuffer = new HeapIndexBuffer();
            indexBuffer->allocate(indexFormat, indexCount);
            
            this->objects.push_back(indexBuffer);
            
            return indexBuffer;
        }
        
        
        void GraphicsDriverBase::notifyDestruction(Object *object) {
            assert (object->getCreator() == this);
            
            auto &objects = this->objects;
            auto position = boost::range::find_if(objects, [object](Object &obj){
               return &obj == object;
            });
            
            assert (position != objects.end());
            objects.erase(position);
        }
    }
}
