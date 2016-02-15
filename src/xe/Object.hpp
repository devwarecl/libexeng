/**
 * @file Object.hpp
 * @brief exeng base blass.
 */


/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_OBJECT_HPP__
#define __EXENG_OBJECT_HPP__

#include <string>
#include <memory>
#include <xe/Config.hpp>
#include <xe/TypeInfo.hpp>

namespace xe {
    
    namespace io {
        class EXENGAPI Stream;
    }
    
	/**
	 * @brief Base class of the class hierarchy of the multimedia engine. 
	 */
	class EXENGAPI Object {
	public:
        Object();
        
		virtual ~Object() = 0;
		
		/**
		 * @brief Get a string representation of the object.
		 */
		virtual std::string	toString() const;
		
        /**
         * @brief Checks if the object can be cloned. 
         * 
         * Returns false for his default implementation. Derived clases must override this method
         * in order to implement the xe::Object::clone virtual method.
         */
        virtual bool isClonable() const;
        
		/**
		 * @brief Get a exact copy of the object internal data. 
		 */
		std::unique_ptr<Object> clone() const;

		/**
		 * @brief Check if two given objects are equal.
		 */
		virtual bool equals(const Object &other) const;

		/**
		 * @brief Get the TypeInfo of the object.
		 */
		virtual TypeInfo getTypeInfo() const;
        
        /**
         * @brief Check if the object can be serialized.
         */
        virtual bool isSerializable() const;
        
        /**
         * @brief Serialize the object. 
         * @todo Specify whenever to use binary or text based streamming.
         * 
         * Store the current state of the object to the specified stream, so can
         * be restored in a later time.
         * 
         * Throws a std::logic_exception if this operation is 
         * unsupported (Object::isSerializable returns false).
         */
        virtual void serialize(xe::io::Stream *outStream) const;
        
        /**
         * @brief Check if the object can be deserialized.
         */
        virtual bool isDeserializable() const;
        
        /**
         * @brief Deserialize the object
         * @todo Specify whenever to use binary or text based streamming.
         * 
         * Restore the object to a past state, stored in the specified stream.
         * 
         * Throws a std::logic_exception if this operation is 
         * unsupported (Object::isDeserializable returns false).
         */
        virtual void deserialize(const xe::io::Stream *inStream);

    protected:
        virtual Object* cloneImpl() const;
	};
}

#endif	//__EXENG_OBJECT_HPP__
