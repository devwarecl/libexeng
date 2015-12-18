
#ifndef __EXENG_PRODUCTMANAGER_HPP__
#define __EXENG_PRODUCTMANAGER_HPP__

#include <memory>
#include <string>
#include <list>

namespace exeng {
	template<typename ProductLoader, typename Product>
	class ProductManager {
	public:
		virtual ~ProductManager() {}

		virtual Product* getProduct(const std::string &productId) = 0;

		virtual void putProduct(const std::string &productId, std::unique_ptr<Product> product) = 0;

		virtual void addLoader(ProductLoader *loader) = 0;

		virtual void removeLoader(ProductLoader *loader) = 0;

		virtual std::list<ProductLoader*> getLoaders() const = 0;

		virtual bool existProduct(const std::string &productId) const = 0;
	};
}

#endif
