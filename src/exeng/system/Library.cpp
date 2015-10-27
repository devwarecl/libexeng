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

#include <exeng/system/Library.hpp>
#include <exeng/system/LibraryPrivate.hpp>

namespace exeng { namespace system {

	Library::Library()
	{
		this->impl = new Library::Private();
	}

	Library::Library(const std::string &filename)
	{
		this->impl = new Library::Private();
		this->load(filename);
	}

	Library::~Library() 
	{
		this->unload();
        boost::checked_delete(this->impl);
	}

	void Library::load(const std::string &filename) 
	{
		assert(this);
		assert(this->impl);
		this->impl->load(filename);
	}
		
	void Library::unload() 
	{
		assert(this->impl != nullptr);
		this->impl->unload();
	}
		
	bool Library::isValid() const 
	{
		assert(this->impl != nullptr);
		return this->impl->handle != nullptr;
	}
    
	std::string Library::getFileName() const 
	{
		assert(this->impl != nullptr);
		return this->impl->name;
	}
    
	std::string Library::getName() const 
	{
		assert(this->impl != nullptr);
		return this->impl->name;
	}
    
	std::string Library::toString() const 
	{
		assert(this->impl != nullptr);

        if (this->isValid() == true) {
			return this->getName();
        } else {
			return Object::toString();
        }
	}
    
	FunctionPtr Library::getFunctionPtr(const std::string& FunctionName) 
	{
		assert(this->impl != nullptr);
		return this->impl->getFunctionPtr(FunctionName);
	}
}}
