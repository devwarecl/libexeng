/**
 * @file ISceneRenderer.hpp
 * @brief Definition of the ISceneRenderer interface.
 */


/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_SCENERENDERER_HPP__
#define __EXENG_SCENEGRAPH_SCENERENDERER_HPP__

#include <exeng/Config.hpp>

namespace exeng { namespace scenegraph {
    class EXENGAPI Scene;
    class EXENGAPI Camera;
    
    /**
     * @brief Interface to a undetermined scene renderer.
     */
	class EXENGAPI ISceneRenderer {
    public:
        virtual ~ISceneRenderer();
        
        /**
         * @brief Render the specified scene.
         * @param scene The scene to render. Cannot be a nullptr. Throws a std::invalid_argument exception.
         */
        virtual void renderScene(const Scene *scene, const Camera *camera) = 0;
    };
}}

#endif // __EXENG_SCENEGRAPH_SCENERENDERER_HPP__
