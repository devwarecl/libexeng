
#pragma once

#ifndef __exeng_iproductfactory_hpp__
#define __exeng_iproductfactory_hpp__

#include <memory>
#include <vector>

template<typename ProductInfo, typename Product>
class IProductMaker {
public:
	typedef std::unique_ptr<Product> ProductPtr;
	
	virtual ~IProductMaker() {}
	virtual ProductInfo* getInfo() = 0;
	virtual ProductPtr make() = 0;
};

template<typename ProductInfo, typename Product>
class IProductFactory {
public:
	typedef std::unique_ptr<Product> ProductPtr;
	
	virtual ~IProductFactory() {}
	
	virtual std::vector<ProductInfo*> enumerate() = 0;
	
	virtual ProductPtr create() = 0;
	
	virtual ProductPtr create(ProductInfo* productInfo) = 0;
	
	virtual void registerMaker(IProductMaker<ProductInfo, Product> *creator) = 0;
	
	virtual void unregisterMaker(IProductMaker<ProductInfo, Product> *creator) = 0;
};

#endif 
