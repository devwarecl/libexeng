/**
 * @file Library.cpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <boost/checked_delete.hpp>

#include <xe/sys/Library.hpp>
#include <xe/sys/LibraryPrivate.hpp>

namespace xe { namespace sys {

	Library::Library() {
		impl = new Library::Private();
	}

	Library::Library(const std::string &filename) {
		impl = new Library::Private();
		load(filename);
	}

	Library::~Library() {
		unload();
        boost::checked_delete(impl);
	}

	void Library::load(const std::string &filename) {
		assert(this);
		assert(impl);
		impl->load(filename);
	}
		
	void Library::unload() {
		assert(impl);
		impl->unload();
	}
		
	bool Library::isValid() const {
		assert(impl);
		return impl->handle?true:false;
	}
    
	std::string Library::getFileName() const {
		assert(impl);
		return impl->name;
	}
    
	std::string Library::getName() const {
		assert(impl);
		return impl->name;
	}
    
	std::string Library::toString() const {
		assert(impl);

        if (isValid() == true) {
			return getName();
        } else {
			return Object::toString();
        }
	}
    
	FunctionPtr Library::getFunctionPtr(const std::string& FunctionName) {
		assert(impl);
		return impl->getFunctionPtr(FunctionName);
	}
}}
