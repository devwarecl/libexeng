/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_SCENE_HPP__
#define __EXENG_SCENEGRAPH_SCENE_HPP__

#include <memory>
#include <xe/Object.hpp>
#include <xe/Vector.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/sg/Geometry.hpp>
#include <xe/sg/SceneNode.hpp>
#include <xe/sg/Light.hpp>
#include <xe/sg/Camera.hpp>

namespace xe { namespace sg { 
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
