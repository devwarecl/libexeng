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
#include <exeng/Config.hpp>

namespace exeng { namespace scenegraph {
    
    class EXENGAPI Scene;
    class EXENGAPI Camera;
    
	class EXENGAPI SceneRenderer {
	public:
		virtual ~SceneRenderer() {}

		virtual void setScene(const Scene* scene) = 0;
		virtual const Scene* getScene() const = 0;

		virtual void render(const Camera* camera) = 0;
	};

	typedef std::unique_ptr<SceneRenderer> SceneRendererPtr;

	//typedef std::function<void(const SceneNodeData *data)> SceneNodeDataRenderer;

 //   /**
 //    * @brief Interface to a scene renderer
 //    */
	//class EXENGAPI SceneRenderer {
 //   public:
	//	SceneRenderer();
 //       virtual ~SceneRenderer();
 //       
 //       /**
 //        * @brief Get the current scene.
 //        */
 //       const Scene* getScene() const;
 //       
 //       /**
 //        * @brief Set the current scene.
 //        * @param scene The scene to render. Cannot be a nullptr.
 //        * @throw std::invalid_argument When the scene is a nullptr (On debug builds).
 //        */
 //       void setScene(const Scene *scene);
 //       
 //       /**
 //        * @brief Render the current scene using the camera
 //        * @param camera The current scene to render.
 //        * @throw std::invalid_argument When the supplied camera doesn't belong to the current scene.
 //        */
 //       virtual void renderScene(const Camera *camera) = 0;
	//
	//	/**
	//	 * @brief Register a scene node data renderer of the specified data type.
	//	 */
	//	void registerRenderer(const TypeInfo &typeInfo, const SceneNodeDataRenderer &renderer);
	//
	//	/**
	//	 * @brief Unregister a scene node data renderer of the specified data type.
	//	 */
	//	void unregisterRenderer(const TypeInfo &typeInfo);
	//
	//protected:
	//	/**
	//	 * @brief Render the specified scene node data.
	//	 */
	//	void renderSceneNodeData(const SceneNodeData *data);
	//
	//	/**
	//	 * @brief Preprocess the scene.
	//	 */
	//	virtual void preprocessScene();
	//
	//private:
	//	struct Impl;
	//	Impl *impl = nullptr;
 //   };

	//inline void SceneRenderer::preprocessScene() {}
}}

#endif // __EXENG_SCENEGRAPH_SCENERENDERER_HPP__
