/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_SCENE_HPP__
#define __EXENG_SCENEGRAPH_SCENE_HPP__

#include <exeng/Object.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/graphics/Color.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/scenegraph/Geometry.hpp>
#include <exeng/scenegraph/SceneNode.hpp>

namespace exeng { namespace scenegraph {    
    /**
     *  @brief Clase de grafos de escena
     */
    class EXENGAPI Scene : public Object {
    public:
        Scene();
        virtual ~Scene();
        
        /**
         * @brief Devuelven el nodo raiz de la escena
         */
        SceneNode* getRootNode();
        const SceneNode* getRootNode() const;
        
        /**
         * @brief Add the specified camera to the root node of the scene.
         */
        SceneNode* addCamera(Camera *camera, const std::string &name);
        
        /**
         * @brief Add the specified camera to the scene graph.
         */
        SceneNode* addCamera(Camera *camera, const std::string &name, SceneNode *parent);
        
        /**
         * @brief Get all camera scene nodes of the scene graph.
         */
        const SceneNodes& getCameraSceneNodes() const;
        
        /**
         * @brief Add the specified light to the root node of the scene graph.
         */
        SceneNode* addLight(Light *light, const std::string &name);
        
        /**
         * @brief Add the specified light to the scenegraph
         */
        SceneNode* addLight(Light *light, const std::string &name, SceneNode *parent);
        
        /**
         * @brief Get all camera of the scene graph.
         */
        const SceneNodes& getLightSceneNodes() const;
        
        /**
         * @brief Sets the scene background color.
         */
        void setBackColor(const exeng::graphics::Color &color);
        
        /**
         * @brief Gets the scene background color.
         */
        exeng::graphics::Color getBackColor() const;
        
        /**
         * @brief Add a new material to the scene.
         */
        exeng::graphics::Material* addMaterial(const std::string &name);
        
        /**
         * @brief Add a new Geometry to the scene. 
         * 
         * The Scene object takes ownership of the recently added object.
         */
        exeng::scenegraph::Geometry* addGeometry(exeng::scenegraph::Geometry* geometry);
        
    private:
        struct Private;
        Private* impl;
    };
}}

#endif
