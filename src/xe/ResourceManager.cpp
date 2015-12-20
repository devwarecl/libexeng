///**
// * @file ResourceManager.cpp
// * @brief Implement the resource factory methods
// */
//
//
///*
// * Copyright (c) 2013 Felipe Apablaza.
// *
// * The license and distribution terms for this file may be
// * found in the file LICENSE in this distribution.
// */
//
//#include "ResourceManager.hpp"
//
//#include <cassert>
//#include <map>
//#include <list>
//#include <boost/checked_delete.hpp>
//#include <xe/Exception.hpp>
//
//namespace xe {
//
//	struct ResourceManager::Impl {
//		mutable std::map<std::string, ResourcePtr> resources;
//		std::list<ResourceLoader*> loaders;
//
//		Resource* get(const std::string &uri) {
//			// Search for already loaded resources
//			auto resourceIterator = this->resources.find(uri);
//			if (resourceIterator != std::end(this->resources)) {
//				return resourceIterator->second.get();
//			}
//
//			//! TODO: Validate the supplied uri
//
//			// search for a suitable loader
//			Resource* resource = nullptr;
//			for (ResourceLoader *loader : this->loaders) {
//				if (loader->tryLoad(uri)) {
//					std::unique_ptr<Resource> resourcePtr = loader->load(uri);
//
//					resource = resourcePtr.get();
//					this->resources[uri] = std::move(resourcePtr);
//					break;
//				}
//			}
//
//			return resource;
//		}
//	};
//
//	ResourceManager::ResourceManager() {
//		this->impl = new ResourceManager::Impl();
//	}
//
//	ResourceManager::~ResourceManager() {
//		boost::checked_delete(this->impl);
//	}
//
//	Resource* ResourceManager::get(const std::string &uri) {
//		assert(this->impl != nullptr);
//
//		return this->impl->get(uri);
//	}
//
//	const Resource* ResourceManager::get(const std::string &uri) const {
//		assert(this->impl != nullptr);
//
//		return this->impl->get(uri);
//	}
//
//	void ResourceManager::put(const std::string &uri, ResourcePtr resource) {
//		this->impl->resources[uri] = std::move(resource);
//	}
//
//	void ResourceManager::addLoader(ResourceLoader *loader)
//	{
//		assert(this->impl != nullptr);
//
//#if defined(EXENG_DEBUG)
//		if (loader == nullptr) {
//			EXENG_THROW_EXCEPTION("The supplied ResourceLoader instance can't be a null pointer.");
//		}
//#endif
//
//		this->impl->loaders.push_back(loader);
//	}
//
//	void ResourceManager::removeLoader(ResourceLoader *loader)
//	{
//		assert(this->impl != nullptr);
//
//#if defined(EXENG_DEBUG)
//		if (loader == nullptr) {
//			EXENG_THROW_EXCEPTION("The supplied ResourceLoader instance can't be a null pointer.");
//		}
//#endif
//
//		this->impl->loaders.remove(loader);
//	}
//
//	std::list<ResourceLoader*>& ResourceManager::getLoaders()
//	{
//		return this->impl->loaders;
//	}
//}
