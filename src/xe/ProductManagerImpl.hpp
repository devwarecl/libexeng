
#ifndef __EXENG_PRODUCTMANAGERIMPL_HPP__
#define __EXENG_PRODUCTMANAGERIMPL_HPP__

#include "ProductManager.hpp"
#include <map>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace xe {

	template<typename ProductLoader, typename Product>
	class ProductManagerImpl : public ProductManager<ProductLoader, Product> {
	public:
		virtual ~ProductManagerImpl() {}

		virtual Product* getProduct(const std::string &productId) override {
			namespace fs = boost::filesystem;

			// get an already loaded resource
			auto productIt = products.find(productId);

			if (productIt != std::end(products)) {
				return productIt->second.get();
			}

			// check if the specified file already exists.
			fs::path path = fs::path(productId);

			/*
			if (!path.has_parent_path()) {
				path = fs::path(this->getPath() + "/" + productId);
			}
			*/

			if (!fs::is_regular_file(path) || !fs::exists(path)) {
				return nullptr;
				// throw std::runtime_error("MeshManager::getMesh: Invalid file:'" + path.string() + "'");
			}

			// try to load the resource using one of the available loaders
			for (auto *loader : loaders) {
				if (loader->isSupported(productId)) {
					auto productPtr = loader->load(productId);
					auto product = productPtr.get();

					products[productId] = std::move(productPtr);
					
					return product;
				}
			}

			return nullptr;
		}

		virtual void putProduct(const std::string &productId, std::unique_ptr<Product> product) override {
			products[productId] = std::move(product);
		}

		virtual void addLoader(ProductLoader *loader) override {
			this->loaders.push_back(loader);
		}

		virtual void removeLoader(ProductLoader *loader) override {
			this->loaders.remove(loader);
		}

		virtual std::list<ProductLoader*> getLoaders() const override {
			return this->loaders;
		}

		virtual bool existProduct(const std::string &productId) const override {
			return this->products.find(productId) != std::end(this->products);
		}

	private:
		std::list<ProductLoader*> loaders;
		std::map<std::string, std::unique_ptr<Product>> products;
	};
}

#endif
