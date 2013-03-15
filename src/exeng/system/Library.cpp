
#include <cassert>
#include <stdexcept>
#include "Library.hpp"
#include "LibraryPrivate.hpp"

namespace exeng
{
	namespace system
	{
		Library::Library() : impl(NULL)
		{
			this->impl = new Library::Private();
		}


		Library::Library(const std::string &LibraryFileName) : impl(NULL)
		{
			this->impl = new Library::Private();
			this->load(LibraryFileName);
		}


		Library::~Library()
		{
			this->unload();
			delete this->impl;
		}


		void Library::load(const std::string &filename)
		{
			assert(this->impl != NULL);

			this->impl->load(filename);

			if (this->impl->handle == NULL)
				throw std::runtime_error("");
		}

		
		void Library::unload()
		{
			assert(this->impl != NULL);

			this->impl->unload();
		}

		
		bool Library::isValid() const
		{
			assert(this->impl != NULL);
			return this->impl->handle != NULL;
		}

		
		std::string Library::getFileName() const
		{
			assert(this->impl != NULL);

			return this->impl->name;
		}

		
		std::string Library::getName() const
		{
			assert(this->impl != NULL);

			return this->impl->name;
		}

		
		std::string Library::toString() const
		{
			assert(this->impl != NULL);

			if (this->isValid() == true)
				return this->getName();
			else
				return "<empty library object>";
		}

		
		FunctionPtr Library::getFunctionPtr(const std::string& FunctionName)
		{
			assert(this->impl != NULL);

			FunctionPtr functionPtr = NULL;

			functionPtr = this->impl->getFunctionPtr(FunctionName);

			return functionPtr;
		}
	}
}
