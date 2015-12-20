/**
 * @file Exeng.hpp
 * @brief Main include file. Includes the *most* used stuff.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_HPP__
#define __EXENG_HPP__

#include "xe/DetectEnv.hpp"
#include "xe/Config.hpp"
#include "xe/TFlags.hpp"
#include "xe/Object.hpp"
#include "xe/Version.hpp"
#include "xe/Core.hpp"
#include "xe/Buffer.hpp"
#include "xe/HeapBuffer.hpp"
#include "xe/StaticBuffer.hpp"
#include "xe/TypeInfo.hpp"
#include "xe/Timer.hpp"
#include "xe/Exception.hpp"

#include "xe/Common.hpp"
#include "xe/Size.hpp"
#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"
#include "xe/Boundary.hpp"

#include "xe/input/IEventHandler.hpp"

#include "xe/sys/PluginManager.hpp"

#include "xe/gfx/GraphicsManager.hpp"
#include "xe/gfx/Shader.hpp"
#include "xe/gfx/ShaderProgram.hpp"
#include "xe/gfx/GraphicsDriver.hpp"
#include "xe/gfx/VertexArray.hpp"
#include "xe/gfx/VertexFormat.hpp"
#include "xe/gfx/Texture.hpp"
#include "xe/gfx/Material.hpp"
#include "xe/gfx/Primitive.hpp"
#include "xe/gfx/Image.hpp"
#include "xe/gfx/Material.hpp"
#include "xe/gfx/MaterialLibrary.hpp"
#include "xe/gfx/MeshManager.hpp"
#include "xe/gfx/MeshLoader.hpp"
#include "xe/gfx/Mesh.hpp"

#include "xe/sg/Camera.hpp"
#include "xe/sg/Geometry.hpp"
#include "xe/sg/IntersectInfo.hpp"
#include "xe/sg/Light.hpp"
#include "xe/sg/Ray.hpp"
#include "xe/sg/Sphere.hpp"
#include "xe/sg/Plane.hpp"
#include "xe/sg/Scene.hpp"
#include "xe/sg/SceneNode.hpp"
#include "xe/sg/SceneNodeData.hpp"
#include "xe/sg/SceneNodeAnimator.hpp"
#include "xe/sg/Segment.hpp"
#include "xe/sg/TSolidGeometry.hpp"
#include "xe/sg/SceneRenderer.hpp"
#include "xe/sg/GenericSceneRenderer.hpp"

/**
 * @brief The common namespace for the engine.
 */
namespace xe {
	/**
	 * @brief Classes for rendering raw 2D and 3D graphics.
	 */
    namespace gfx {}

    /**
	 * @brief Loading for plugins and dynamic linking libraries.
	 */
    namespace sys {}
    
    /**
     * @brief Scenegraph module, for rendering 3D graphics.
     */
    namespace sg {}
}

#endif  //__EXENG_HPP__
