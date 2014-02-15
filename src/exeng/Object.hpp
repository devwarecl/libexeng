/**
 * @file Object.hpp
 * @brief exeng base blass.
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
#include <exeng/Config.hpp>
#include <exeng/TypeInfo.hpp>

namespace exeng {
    
	/**
	 * @brief Base class of the class hierarchy of the multimedia engine. 
	 */
	class EXENGAPI Object {
	public:
        Object();
        
		virtual ~Object();
		
		/**
		 * @brief Get a string representation of the object.
		 */
		virtual std::string	toString() const;
		
        /**
         * @brief Checks if the object can be cloned. 
         * 
         * Returns false for his default implementation. Derived clases must override this method
         * in order to implement the exeng::Object::clone virtual method.
         */
        virtual bool isClonable() const;
        
		/**
		 * @brief Get a exact copy of the object attributes. 
		 */
		virtual Object* clone() const;

		/**
		 * @brief Check if two given objects are equal.
		 */
		virtual bool equals(const Object &other) const;

		/**
		 * @brief Get the TypeInfo of the object.
		 */
		virtual TypeInfo getTypeInfo() const;
	};
}

#endif	//__EXENG_OBJECT_HPP__
