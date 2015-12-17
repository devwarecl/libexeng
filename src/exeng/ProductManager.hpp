
#ifndef __EXENG_PRODUCTMANAGER_HPP__
#define __EXENG_PRODUCTMANAGER_HPP__

#include "ProductLoader.hpp"

namespace exeng {
	template<typename Product, typename ProductLoader>
	class ProductManager {
	public:
		virtual ~ProductManager() {}

		virtual Product* get(const std::string &productId) = 0;

		virtual void addLoader(ProductLoader *loader) = 0;

		virtual void removeLoader(ProductLoader *loader) = 0;
	};
}

#endif
