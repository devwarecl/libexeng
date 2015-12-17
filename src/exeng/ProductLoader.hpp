
#ifndef __EXENG_PRODUCTLOADER_HPP__
#define __EXENG_PRODUCTLOADER_HPP__

#include <memory>
#include <string>

namespace exeng {
	template<typename ProductType>
	class ProductLoader {
	public:
		typedef std::unique_ptr<ProductType> ProductTypePtr;

		virtual ~ProductLoader() {}
		virtual bool tryLoad(const std::string &id) const = 0;
		virtual ProductTypePtr load(const std::string &id) = 0;
	};
}

#endif
