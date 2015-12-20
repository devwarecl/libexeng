/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_TYPEINFO_HPP__
#define __EXENG_TYPEINFO_HPP__

#include <typeinfo>
#include <xe/Config.hpp>

namespace xe {

	/**
	 *  @brief std::type_info wrapper.
	 */
	class EXENGAPI TypeInfo {
	public:
		TypeInfo();
    
		TypeInfo(const std::type_info& info);

		void setStdTypeInfo(const std::type_info& info);

		const std::type_info& getStdTypeInfo() const;

		bool operator== (const TypeInfo& other) const;
		bool operator!= (const TypeInfo& other) const;

		bool operator< (const TypeInfo& other) const;
		bool operator> (const TypeInfo& other) const;

		bool operator<= (const TypeInfo& other) const;
		bool operator>= (const TypeInfo& other) const;

		bool isEmpty() const;

	private:
		std::type_info *typeInfo;
	};


	/**
	 * @brief Build a TypeInfo object based on the specified type.
	 */
	template<typename Type>
	static TypeInfo TypeId() {
		return TypeInfo(typeid(Type));
	}
}

#endif
