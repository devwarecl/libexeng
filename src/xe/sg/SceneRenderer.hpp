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

#include <memory>
#include <functional>
#include <xe/Config.hpp>

namespace xe { namespace sg {
    
    class EXENGAPI Scene;
    class EXENGAPI Camera;
    
	class EXENGAPI SceneRenderer {
	public:
		virtual ~SceneRenderer();

		virtual void setScene(const Scene* scene) = 0;
		virtual const Scene* getScene() const = 0;

		virtual void render(const Camera* camera) = 0;
	};

	typedef std::unique_ptr<SceneRenderer> SceneRendererPtr;
}}

#endif // __EXENG_SCENEGRAPH_SCENERENDERER_HPP__
