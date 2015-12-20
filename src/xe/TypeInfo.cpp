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

#include <xe/TypeInfo.hpp>

namespace xe {
	const std::string invalidTypePtr = "TypeInfo: Empty TypeInfo value.";

	TypeInfo::TypeInfo() : typeInfo(nullptr) {}

	TypeInfo::TypeInfo(const std::type_info& info) : typeInfo(nullptr) {
		this->setStdTypeInfo(info);
	}

	void TypeInfo::setStdTypeInfo(const std::type_info& info) {
		this->typeInfo = const_cast<std::type_info*>(&info);
	}

	const std::type_info& TypeInfo::getStdTypeInfo() const {
		if (this->isEmpty() == true) {
			throw std::logic_error(xe::invalidTypePtr);
        }

		return *this->typeInfo;
	}

	bool TypeInfo::operator== (const TypeInfo& other) const {
        return *this->typeInfo == *other.typeInfo;
	}

	bool TypeInfo::operator!= (const TypeInfo& other) const {
        return ! (*this == other);
	}

	bool TypeInfo::operator< (const TypeInfo& other) const {
		return this->typeInfo->before(*other.typeInfo);
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
