
#include "SceneLoader.hpp"

namespace xe { namespace sg {
	SceneLoader::SceneLoader(Core *core) {
		this->core = core;
	}

	SceneLoader::~SceneLoader() {}

	Core* SceneLoader::getCore() {
		return this->core;
	}
}}
