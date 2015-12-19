
#include "AssetsLibrary.hpp"

#include <map>
#include <exeng/StaticBuffer.hpp>
#include <exeng/Exception.hpp>

namespace xe { namespace sg {
	struct AssetLibrary::Private {
		std::map<std::string, BufferPtr> assets;
	};
	
	AssetLibrary::AssetLibrary() {
		this->impl = new AssetLibrary::Private();
	}

	AssetLibrary::~AssetLibrary() {
		delete this->impl;
	}

	void AssetLibrary::addAsset(const std::string &fileId, void* data, const int dataSize) {
#if defined(EXENG_DEBUG)
		if (!data) {
			EXENG_THROW_EXCEPTION("Asset data must be a null pointer.");
		}

		if (dataSize <= 0) {
			EXENG_THROW_EXCEPTION("Invalid buffer size");
		}
#endif
		StaticBufferPtr assetData = std::make_unique<StaticBuffer>(data, dataSize);
		this->impl->assets[fileId] = std::move(assetData);
	}

	void AssetLibrary::addAsset(const std::string &fileId, BufferPtr assetData) {
		this->impl->assets[fileId] = std::move(assetData);
	}

	Buffer* AssetLibrary::getAsset(const std::string &file) {
		return this->impl->assets[file].get();
	}

	const Buffer* AssetLibrary::getAsset(const std::string &file) const {
		return this->impl->assets[file].get();
	}
}}
