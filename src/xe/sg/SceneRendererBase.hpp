
#pragma once

#ifndef __xe_gfx_scenerendererbase_hpp__
#define __xe_gfx_scenerendererbase_hpp__

#include <memory>
#include <xe/Matrix.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/sg/IRenderer.hpp>
#include <xe/sg/Scene.hpp>
#include <xe/sg/SceneNode.hpp>
#include <xe/sg/ISceneRenderer.hpp>
#include <xe/sg/TransformationStack.hpp>
#include <xe/sg/Camera.hpp>

namespace xe { namespace sg {
	class SceneRendererBase : public ISceneRenderer, public IRenderer {
	public:
		SceneRendererBase();
		explicit SceneRendererBase(xe::gfx::GraphicsDriver* driver);

		virtual ~SceneRendererBase();

		void setGraphicsDriver(xe::gfx::GraphicsDriver* driver);

		xe::gfx::GraphicsDriver* getGraphicsDriver();

		const xe::gfx::GraphicsDriver* getGraphicsDriver() const;

		virtual void setScene(Scene* scene) override;

		virtual Scene* getScene() override;

		virtual const Scene* getScene() const override;

		virtual void renderScene(Camera* camera) override;

	protected:
		virtual void render(Camera *camera) override;

		virtual void render(Geometry *geometry) override;

		virtual void render(Light *light) override;

		void renderMesh(xe::gfx::Mesh *mesh);

		void renderSceneNode(SceneNode *node);

		void setTransform(const Matrix4f &transform);

	protected:
		Matrix4f getViewMatrix(const Camera *camera);

		Matrix4f getProjectionMatrix(const Camera *camera);

	private:
		xe::gfx::GraphicsDriver *driver = nullptr;
		xe::sg::TransformationStack mvpStack;
		xe::sg::Scene* scene = nullptr;
	};

	inline SceneRendererBase::SceneRendererBase() {}

	inline SceneRendererBase::SceneRendererBase(xe::gfx::GraphicsDriver* driver) {
		this->setGraphicsDriver(driver);
	}

	inline SceneRendererBase::~SceneRendererBase() {}

	inline void SceneRendererBase::setGraphicsDriver(xe::gfx::GraphicsDriver* driver) {
		this->driver = driver;
	}

	inline xe::gfx::GraphicsDriver* SceneRendererBase::getGraphicsDriver() {
		return this->driver;
	}

	inline const xe::gfx::GraphicsDriver* SceneRendererBase::getGraphicsDriver() const {
		return this->driver;
	}

	inline void SceneRendererBase::setScene(Scene* scene) {
		this->scene = scene;
	}

	inline Scene* SceneRendererBase::getScene() {
		return this->scene;
	}

	inline const Scene* SceneRendererBase::getScene() const {
		return this->scene;
	}

	inline Matrix4f SceneRendererBase::getViewMatrix(const Camera *camera) {
		Vector3f position = camera->getPosition();
		Vector3f lookAt = camera->getLookAt();
		Vector3f up = camera->getUp();

		Matrix4f viewMatrix = xe::lookat<float>(position, lookAt, up);

        return viewMatrix;
	}

	inline Matrix4f SceneRendererBase::getProjectionMatrix(const Camera *camera) {
		// TODO: Retrieve perspective information from camera
        return xe::perspective<float>(rad(60.0f), 1.33333f, 0.1f, 1000.0f);	
	}
		
	inline void SceneRendererBase::renderScene(Camera* camera) {
		camera->renderWith(this);

		this->renderSceneNode(this->scene->getRootNode());
	}

	inline void SceneRendererBase::setTransform(const Matrix4f &transform) {
		if (this->driver->getModernModule()) {
			this->driver->getModernModule()->setProgramMatrix("", transform);

		} else if (this->driver->getLegacyModule()) {
			this->driver->getLegacyModule()->setTransform(xe::gfx::Transform::World, transform);
		}
	}

	inline void SceneRendererBase::renderSceneNode(SceneNode *node) {

		// set the current transformation
		this->mvpStack.push(node->getTransform());
		Matrix4f transform = this->mvpStack.top();

		this->setTransform(transform);

		// render the renderable
		if (node->getRenderable()) {
			node->getRenderable()->renderWith(this);
		}

		// render the rest of the scene graph
		for (SceneNode *child : node->getChilds()) {
			this->renderSceneNode(child);
		}

		this->mvpStack.pop();
	}

	inline void SceneRendererBase::render(Camera *camera) {
		Matrix4f mvp = xe::identity<float, 4>();
		Matrix4f modelView = this->getViewMatrix(camera);
		Matrix4f proj = this->getProjectionMatrix(camera);

		mvp *= proj;
		mvp *= modelView;

		this->mvpStack.reset(mvp);
	}

	inline void SceneRendererBase::renderMesh(xe::gfx::Mesh *mesh) {
		for (int i=0; i<mesh->getSubsetCount(); i++) {
			xe::gfx::MeshSubset *subset = mesh->getSubset(i);

			this->driver->setMaterial(subset->getMaterial());
			this->driver->setMeshSubset(subset);
			this->driver->render(subset->getPrimitive(), subset->getVertexCount());
		}
	}

	inline void SceneRendererBase::render(Geometry *geometry) {
		auto *mesh = static_cast<xe::gfx::Mesh*>(geometry);

		this->renderMesh(mesh);
	}

	inline void SceneRendererBase::render(Light *light) {
		// TODO: Implement lighting rendering
	}
}}

#endif	// __xe_gfx_scenerendererbase_hpp__
