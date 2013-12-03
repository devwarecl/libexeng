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

#include <exeng/DetectEnv.hpp>
#include <exeng/Config.hpp>
#include <exeng/TFlags.hpp>
#include <exeng/Object.hpp>
#include <exeng/Version.hpp>
#include <exeng/Root.hpp>
#include <exeng/Buffer.hpp>
#include <exeng/HeapBuffer.hpp>
#include <exeng/TypeInfo.hpp>
#include <exeng/Timer.hpp>

#include <exeng/input/IEventHandler.hpp>

#include <exeng/system/PluginManager.hpp>

#include <exeng/framework/Application.hpp>
#include <exeng/framework/Main.hpp>

#include <exeng/graphics/GraphicsManager.hpp>
#include <exeng/graphics/Color.hpp>
#include <exeng/graphics/Shader.hpp>
#include <exeng/graphics/ShaderProgram.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/graphics/IndexBuffer.hpp>
#include <exeng/graphics/VertexArray.hpp>
#include <exeng/graphics/VertexBuffer.hpp>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/graphics/Texture.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/Primitive.hpp>
#include <exeng/graphics/Image.hpp>
#include <exeng/graphics/Material.hpp>

#include <exeng/scenegraph/MeshManager.hpp>
#include <exeng/scenegraph/Camera.hpp>
#include <exeng/scenegraph/Geometry.hpp>
#include <exeng/scenegraph/IMeshLoader.hpp>
#include <exeng/scenegraph/MeshManager.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/scenegraph/MeshPart.hpp>
#include <exeng/scenegraph/IntersectInfo.hpp>
#include <exeng/scenegraph/Light.hpp>
#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/Sphere.hpp>
#include <exeng/scenegraph/Plane.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/SceneNode.hpp>
#include <exeng/scenegraph/Segment.hpp>

#include <exeng/math/Common.hpp>
#include <exeng/math/TSize.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/math/TMatrix.hpp>
#include <exeng/math/TBoundary.hpp>

/**
 * @brief The common namespace for the engine.
 */
namespace exeng {
	/**
	 * @brief Classes for rendering raw 2D and 3D graphics.
	 */
    namespace graphics {}
    
    /**
	 * @brief Common mathematical namespace
	 */
    namespace math {}
    
    /**
	 * @brief Loading for plugins and dynamic linking libraries.
	 */
    namespace system {}
    
    /**
     * @brief Scenegraph module, for rendering 3D graphics.
     */
    namespace scenegraph {}
}

#endif  //__EXENG_HPP__
