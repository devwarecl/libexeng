
#include "SceneManager.hpp"

#include <exeng/ProductManagerImpl.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/SceneLoader.hpp>

namespace exeng { namespace scenegraph {

	struct SceneManager::Private {
		ProductManagerImpl<SceneLoader, Scene> manager;
	};

	SceneManager::SceneManager() {
		this->impl = new SceneManager::Private();
	}

	SceneManager::~SceneManager() {
		delete this->impl;
	}

	Scene* SceneManager::getScene(const std::string &sceneId) {
		return this->impl->manager.getProduct(sceneId);
	}

	void SceneManager::addSceneLoader(SceneLoader *loader) {
		this->impl->manager.addLoader(loader);
	}

	void SceneManager::removeSceneLoader(SceneLoader *loader) {
		this->impl->manager.removeLoader(loader);
	}
}}
