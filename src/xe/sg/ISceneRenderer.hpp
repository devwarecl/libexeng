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

#ifndef __EXENG_SCENEGRAPH_ISCENERENDERER_HPP__
#define __EXENG_SCENEGRAPH_ISCENERENDERER_HPP__

#include <memory>
#include <functional>
#include <xe/Config.hpp>
#include <xe/sg/Forward.hpp>

namespace xe { namespace sg {
    
	class EXENGAPI ISceneRenderer {
	public:
		virtual ~ISceneRenderer();

		virtual void setScene(Scene* scene) = 0;
		virtual Scene* getScene() = 0;
		virtual const Scene* getScene() const = 0;

		virtual void renderScene(Camera* camera) = 0;
	};

	typedef std::unique_ptr<ISceneRenderer> SceneRendererPtr;
}}

#endif // __EXENG_SCENEGRAPH_SCENERENDERER_HPP__
