
#ifndef __EXENG_PRODUCTMANAGER_HPP__
#define __EXENG_PRODUCTMANAGER_HPP__

#include "ProductLoader.hpp"

namespace exeng {
	template<typename ProductType>
	class ProductManager {
	public:
		virtual ~ProductManager() {}

		virtual ProductType* get(const std::string &productId) = 0;

		virtual void addLoader(ProductLoader<ProductType> *loader) = 0;

		virtual void removeLoader(ProductLoader<ProductType> *loader) = 0;
	};
}

#endif
