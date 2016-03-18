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

#include <xe/DetectEnv.hpp>
#include <xe/sys/LibraryPrivate.hpp>

#if defined(EXENG_LINUX) || defined(EXENG_UNIX)

#include <dlfcn.h>
#include <stdexcept>
#include <cassert>
#include <sstream>
#include <iostream>

namespace xe { namespace sys {
	
	void Library::Private::load(const std::string &name) {
        assert(!name.empty());
	
		void *handle = ::dlopen(name.c_str(), RTLD_NOW | RTLD_LOCAL);
        
		// Report the error as a Exception
		if (!handle) {
            std::cerr << "Error while loading module '" << name << "': " << ::dlerror() << std::endl;
		}
            
        assert(handle);
        
		this->name = name;
		this->handle = handle;
	}
        
	void Library::Private::unload() {
		if (handle != nullptr) {
			::dlclose(handle);
			handle = nullptr;
		}
	}
        
	FunctionPtr Library::Private::getFunctionPtr(const std::string &name) {
		void *fnptr = nullptr;
            
		if (handle == nullptr) {
			throw std::runtime_error("The library must be loaded first.");
		}
            
		fnptr = ::dlsym( handle, name.c_str() );
            
		if (fnptr == NULL) {
			std::string strError = std::string("POSIX specific error: ") + ::dlerror();
			throw std::runtime_error(strError);
		}
            
		return fnptr;
	}
}}

#endif
