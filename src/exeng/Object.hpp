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



#ifndef __EXENG_OBJECT_HPP__
#define __EXENG_OBJECT_HPP__

#include <string>

#include "Config.hpp"
#include "DataTypes.hpp"
#include "TypeInfo.hpp"

namespace exeng {
	/**
	 * @brief Base class of the class hierarchy of the multimedia engine. 
	 */
	
	class EXENGAPI Object {
	public:
		virtual ~Object() = 0;
		
		/**
		 * @brief Get a string representation of the object.
		 */
		virtual std::string	toString() const;
		
		/**
		 * @brief Get a exact copy of the object attributes. Derived classes must override this method.
		 */
		virtual Object* clone() const;

		/**
		 * @brief Check if two given objects are equal.
		 */
		virtual bool equals(const Object &other) const;

		/**
		 * @brief Check if one object if lesser than the other.
		 */
		virtual bool lesserThan(const Object& other) const;

		/**
		 * @brief Copy the contents of the other object on the current one.
		 */
		virtual void assign(const Object& other);

		/**
		 * @brief Equality operator overload.
		 */
		bool operator== (const Object& other) const;

		/**
		 * @brief Inequality operator overload.
		 */
		bool operator!= (const Object& other) const;

		/**
		 * @brief Lesser than operator overload.
		 */
		bool operator< (const Object& other) const;

		/**
		 * @brief Greater than operator overload
		 */
		bool operator> (const Object& other) const;

		/**
		 * @brief Equal or lesser than operator overload.
		 */
		bool operator<= (const Object& other) const;

		/**
		 * @brief Equal or greater than operator overload.
		 */
		bool operator>= (const Object& other) const;

		/**
		 * @brief Asignation operator overload.
		 */
		Object& operator= (const Object& other);

		/**
		 * @brief Get the TypeInfo of the object.
		 */
		virtual TypeInfo getTypeInfo() const;
	};
}

#endif	//__EXENG_OBJECT_HPP__
