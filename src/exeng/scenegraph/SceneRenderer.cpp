/**
 * @file ISceneRenderer.cpp
 * @brief Definition of the ISceneRenderer interface destructor.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include "SceneRenderer.hpp"

#include <map>	
#include <cassert>
#include <boost/checked_delete.hpp>

namespace exeng { namespace scenegraph {

	struct SceneRenderer::Impl 
	{
		const Scene *scene = nullptr;
		std::map<TypeInfo, SceneNodeDataRenderer> renderers;
	};

	SceneRenderer::SceneRenderer()
	{
		this->impl = new SceneRenderer::Impl();
	}

	SceneRenderer::~SceneRenderer() 
	{
		boost::checked_delete(this->impl);
	}

	const Scene* SceneRenderer::getScene() const
	{
		return this->impl->scene;
	}
    
    void SceneRenderer::setScene(const Scene *scene)
	{
		this->impl->scene = scene;
		this->preprocessScene();
	}

	void SceneRenderer::registerRenderer(const TypeInfo &typeInfo, const SceneNodeDataRenderer &renderer)
	{
		assert(this->impl != nullptr);

		auto &renderers = this->impl->renderers;
		renderers.insert({typeInfo, renderer});
	}

	void SceneRenderer::unregisterRenderer(const TypeInfo &typeInfo)
	{
		assert(this->impl != nullptr);

		this->impl->renderers.erase(typeInfo);
	}

	void SceneRenderer::renderSceneNodeData(const SceneNodeData *data)
	{
		assert(this->impl != nullptr);

#if defined(EXENG_DEBUG)
		if (data == nullptr) {
			throw std::runtime_error("SceneRenderer::renderSceneNodeData: The Scene Node data can't be a null pointer.");
		}
#endif
		TypeInfo typeInfo = data->getTypeInfo();

		auto &renderers = this->impl->renderers;
		auto rendererIt = renderers.find(typeInfo);

#if defined(EXENG_DEBUG)
		if (rendererIt == renderers.end()) {
			std::string msg = "";

			msg += "SceneRenderer::renderSceneNodeData: Couldn't find a node data renderer for the type" ;
			msg += "'" + std::string(typeInfo.getStdTypeInfo().name()) + "'";

			throw std::runtime_error(msg);
		}
#endif
		rendererIt->second(data);
	}
}}
