
#pragma once

#ifndef __exeng_productfactory_hpp__
#define __exeng_productfactory_hpp__

#include "IProductFactory.hpp"
#include <map>

/**
 * @brief Extensible dynamic and parametrizable template factory.
 */
template<typename ProductInfo, typename Product>
class ProductFactory : public IProductFactory<ProductInfo, Product> {
public:
	typedef std::unique_ptr<Product> ProductPtr;
	
	virtual ~ProductFactory() {}
	
	virtual std::vector<ProductInfo*> enumerate() override {
		std::vector<ProductInfo*> infos;
		
		infos.resize(productCreators.size());
		
		int i = 0;
		for (auto &iterator : productCreators) {
			infos[i++] = iterator->first;
		}
		
		return infos;
	}
	
	virtual ProductPtr create() override {
		auto infos = this->enumerate();
		
		if (infos.size() == 0) {
			// EXENG_THROW_EXCEPTION("No product creators of type registered.");
		}
		
		return this->createProduct(infos[0]);
	}
	
	virtual ProductPtr create(ProductInfo* productInfo) override {
		if (!productInfo) {
			// EXENG_THROW_EXCEPTION("Supplied product info of type $ can't be null.");
		}
		
		auto iterator = productCreators.find(productInfo);
		
		if (iterator == std::end(productCreators)) {
			// EXENG_THROW_EXCEPTION("Product creator of type $ isn't registered.");
		}
		
		return iterator->second->create();
	}
	
	virtual void registerMaker(IProductMaker<ProductInfo, Product> *creator) override {
		productCreators[creator->getInfo()] = creator;
	}
	
	virtual void unregisterMaker(IProductMaker<ProductInfo, Product> *creator) override {
		productCreators.remove(creator->getInfo());
	}
	
private:
	std::map<ProductInfo*, IProductMaker<ProductInfo, Product>*> productCreators;
};

#endif
