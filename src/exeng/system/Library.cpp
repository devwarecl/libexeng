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
#include <stdexcept>
#include "Library.hpp"
#include "LibraryPrivate.hpp"

namespace exeng {
	namespace system {
		Library::Library() : impl(nullptr) {
			this->impl = new Library::Private();
		}


		Library::Library(const std::string &LibraryFileName) : impl(nullptr) {
			this->impl = new Library::Private();
			this->load(LibraryFileName);
		}


		Library::~Library() {
			this->unload();
			delete this->impl;
		}


		void Library::load(const std::string &filename) {
			assert(this->impl != nullptr);

			this->impl->load(filename);

            if (this->impl->handle == nullptr) {
				throw std::runtime_error("");
            }
		}

		
		void Library::unload() {
			assert(this->impl != nullptr);
			this->impl->unload();
		}

		
		bool Library::isValid() const {
			assert(this->impl != nullptr);
			return this->impl->handle != nullptr;
		}

		
		std::string Library::getFileName() const {
			assert(this->impl != nullptr);
			return this->impl->name;
		}

		
		std::string Library::getName() const {
			assert(this->impl != nullptr);
			return this->impl->name;
		}

		
		std::string Library::toString() const {
			assert(this->impl != nullptr);

            if (this->isValid() == true) {
				return this->getName();
            }
            else {
				return "<empty library object>";
            }
		}

		
		FunctionPtr Library::getFunctionPtr(const std::string& FunctionName) {
			assert(this->impl != nullptr);
			return this->impl->getFunctionPtr(FunctionName);
		}
	}
}
