
#ifndef __EXENG_PRODUCTMANAGERIMPL_HPP__
#define __EXENG_PRODUCTMANAGERIMPL_HPP__

#include "ProductManager.hpp"
#include <map>

namespace exeng {

	template<typename ProductLoader, typename Product>
	class ProductManagerImpl : public ProductManager<ProductLoader, Product> {
	public:
		virtual ~ProductManagerImpl() {}

		virtual Product* getProduct(const std::string &productId) override {
			// get already loaded resource
			auto productIt = products.find(productId);

			if (productIt != std::end(products)) {
				return productIt->second.get();
			}

			// try to load the resource using the available loaders
			for (auto *loader : loaders) {
				if (loader->tryLoad(productId)) {
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
			loaders.push_back(loader);
		}

		virtual void removeLoader(ProductLoader *loader) override {
			loaders.remove(loader);
		}

		virtual std::list<ProductLoader*> getLoaders() const override {
			return this->loaders;
		}

	private:
		std::list<ProductLoader*> loaders;
		std::map<std::string, std::unique_ptr<Product>> products;
	};
}

#endif
