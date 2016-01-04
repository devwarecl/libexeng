//
//#include <xe/gfx/ImageManager.hpp>
//#include <xe/ProductManager.hpp>
//#include <xe/ProductManagerImpl.hpp>
//
//namespace xe { namespace gfx {
//	
//	struct ImageManager::Private {
//		ProductManagerImpl<ImageLoader, Image> manager;
//	};
//
//	ImageManager::ImageManager() {
//		this->impl = new ImageManager::Private();
//	}
//
//	ImageManager::~ImageManager() {
//		delete this->impl;
//	}
//
//	Image* ImageManager::getImage(const std::string &uri) {
//		return this->impl->manager.getProduct(uri);
//	}
//
//	const Image* ImageManager::getImage(const std::string &uri) const {
//		return this->impl->manager.getProduct(uri);
//	}
//
//	void ImageManager::addLoader(ImageLoader *loader) {
//		return this->impl->manager.addLoader(loader);
//	}
//
//	void ImageManager::removeLoader(ImageLoader *loader) {
//		return this->impl->manager.addLoader(loader);
//	}
//}}
