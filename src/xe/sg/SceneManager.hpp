
#pragma once

#ifndef __XE_SG_SCENEMANAGER_HPP__
#define __XE_SG_SCENEMANAGER_HPP__

#include <string>
#include <xe/sg/Forward.hpp>

namespace xe { namespace sg {
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
