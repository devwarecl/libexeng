/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#pragma once

#ifndef __xe_sg_scene_hpp__
#define __xe_sg_scene_hpp__

#include <memory>
#include <xe/Object.hpp>
#include <xe/Vector.hpp>
#include <xe/Core.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/MaterialLibrary.hpp>
#include <xe/gfx/ShaderLibrary.hpp>
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
        explicit Scene();
        
        virtual ~Scene();
        
        SceneNode* getRootNode();
        const SceneNode* getRootNode() const;

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
