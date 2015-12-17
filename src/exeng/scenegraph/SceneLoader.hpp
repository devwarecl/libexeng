/**
 * @file SceneLoader.hpp
 * @brief Declare the SceneLoader abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_SCENELOADER_HPP__
#define __EXENG_SCENEGRAPH_SCENELOADER_HPP__

#include <exeng/Config.hpp>
#include <exeng/scenegraph/Scene.hpp>

namespace exeng { namespace scenegraph {
	class EXENGAPI SceneLoader {
	public:
		virtual ~SceneLoader();
		virtual ScenePtr loadScene(const std::string &file) = 0;
	};
}}

#endif
