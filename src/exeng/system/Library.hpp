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

#ifndef __EXENG_SYSTEM_LIBRARY_HPP__
#define __EXENG_SYSTEM_LIBRARY_HPP__

#include <string>
#include <exeng/Object.hpp>

namespace exeng { namespace system  {
    typedef void* FunctionPtr;

	/**
	 * @brief 
	 */
    class EXENGAPI Library : public Object {
    public:
        Library();    
        explicit Library(const std::string &libraryName);
        
        virtual ~Library();

        /**
         * @brief Loads the specified dynamic library.
         */
        void load(const std::string &libraryName);
            
        /**
         * @brief Unload the library
         */
        void unload();
            
        /**
         * @brief Check if the current library object is valid or not.
         */
        bool isValid() const;
            
        /**
         * @brief Get the full path (directory plus filename) of the current loaded object.
         */
        std::string getFileName() const;

        /**
		 * @brief Get the name of the library.
         */
        std::string getName() const;
            
        /**
         * @brief Get a function pointer for the specified ordinal name.
         */
        FunctionPtr getFunctionPtr(const std::string& name);
        
        virtual std::string toString() const override;

    private:
        struct Private;
        Private* impl = nullptr;

	private:
		Library(const Library& lib) = delete;
        Library& operator=(const Library& lib) = delete;
    };
}}

#endif	//__EXENG_SYSTEM_LIBRARY_HPP__
