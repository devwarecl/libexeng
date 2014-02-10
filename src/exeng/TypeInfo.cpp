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

#include <cassert>
#include <string>
#include <stdexcept>

#include <exeng/TypeInfo.hpp>

namespace exeng {
	const std::string invalidTypePtr = "TypeInfo: Debe asignar primero un objeto std::type_info";

	TypeInfo::TypeInfo() : typeInfo(nullptr) {}


	TypeInfo::TypeInfo(const std::type_info& info) : typeInfo(nullptr) {
		this->setStdTypeInfo(info);
	}


	void TypeInfo::setStdTypeInfo(const std::type_info& info) {
		this->typeInfo = const_cast<std::type_info*>(&info);
	}


	const std::type_info& TypeInfo::getStdTypeInfo() const {
		if (this->isEmpty() == true) {
			throw std::logic_error(exeng::invalidTypePtr);
        }

		return *this->typeInfo;
	}


	bool TypeInfo::operator== (const TypeInfo& other) const {
		return this->getStdTypeInfo() == other.getStdTypeInfo();
	}


	bool TypeInfo::operator!= (const TypeInfo& other) const {
		return this->getStdTypeInfo() != other.getStdTypeInfo();
	}


	bool TypeInfo::operator< (const TypeInfo& other) const {
		auto &info1 = this->getStdTypeInfo();
		auto &info2 = other.getStdTypeInfo();

		return info1.before(info2);
	}


	bool TypeInfo::operator> (const TypeInfo& other) const {
		return !(*this <= other);
	}


	bool TypeInfo::operator<= (const TypeInfo& other) const {
		return (*this == other) || (*this < other);
	}


	bool TypeInfo::operator>= (const TypeInfo& other) const {
		return !(*this < other);
	}


	bool TypeInfo::isEmpty() const {
		return this->typeInfo == nullptr;
	}
}
