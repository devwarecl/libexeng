
#pragma once

#ifndef __XE_SG_SCENEMANAGER_HPP__
#define __XE_SG_SCENEMANAGER_HPP__

#include <string>
#include <exeng/scenegraph/Forward.hpp>

namespace exeng { namespace scenegraph {
	class EXENGAPI SceneManager {
	public:
		SceneManager();

		virtual ~SceneManager();

		Scene* getScene(const std::string &sceneId);

		void addSceneLoader(SceneLoader *loader);

		void removeSceneLoader(SceneLoader *loader);

	private:
		struct Private;
		Private *impl = nullptr;
	};
}}

#endif
