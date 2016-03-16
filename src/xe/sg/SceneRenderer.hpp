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

#pragma once

#ifndef __xe_sg_scenerenderer_hpp__
#define __xe_sg_scenerenderer_hpp__

#include <memory>
#include <functional>
#include <xe/Config.hpp>
#include <xe/sg/Forward.hpp>

namespace xe { namespace sg {
    
	class EXENGAPI SceneRenderer {
	public:
		virtual ~SceneRenderer();

		virtual void setScene(Scene* scene) = 0;
		virtual Scene* getScene() = 0;
		virtual const Scene* getScene() const = 0;

		virtual void renderScene() = 0;
	};

	typedef std::unique_ptr<SceneRenderer> SceneRendererPtr;
}}

#endif // __EXENG_SCENEGRAPH_SCENERENDERER_HPP__
