/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_SCENE_HPP__
#define __EXENG_SCENEGRAPH_SCENE_HPP__

#include <memory>
#include <exeng/Object.hpp>
#include <exeng/Vector.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/scenegraph/Geometry.hpp>
#include <exeng/scenegraph/SceneNode.hpp>
#include <exeng/scenegraph/Light.hpp>
#include <exeng/scenegraph/Camera.hpp>

namespace exeng { namespace scenegraph { 
    /**
     * @brief Scenegraph 
     */
    class EXENGAPI Scene : public Object {
    public:
        Scene();
        
        virtual ~Scene();
        
        /**
         * @brief 
         */
        SceneNode* getRootNode();
        const SceneNode* getRootNode() const;

        /**
         * @brief Create a new camera. 
         */
        Camera* createCamera();

		Camera* getCamera(int index) const;

		int getCameraCount() const;

        /**
         * @brief 
         */
        Light* createLight();

        /**
         * @brief 
         */
        SceneNode* createSceneNode(const std::string &nodeName, SceneNodeData* nodeData);

        /**
         * @brief Sets the scene background color.
         */
        void setBackColor(const Vector4f &color);
        
        /**
         * @brief Gets the scene background color.
         */
        Vector4f getBackColor() const;

    private:
        struct Private;
        Private* impl = nullptr;
    };

	typedef std::unique_ptr<Scene> ScenePtr;
}}

#endif
