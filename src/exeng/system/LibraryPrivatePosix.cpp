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

#include <exeng/DetectEnv.hpp>
#include <exeng/system/LibraryPrivate.hpp>

#if defined(EXENG_LINUX) || defined(EXENG_UNIX)

#include <dlfcn.h>
#include <stdexcept>
#include <cassert>

namespace exeng {
    namespace system {
        Library::Private::Private() : handle(nullptr) {}
        
        
        void Library::Private::load(const std::string &name) {
            void *handle = nullptr;
            
            // Prevent the handle for the exeng shared object.
            if (name.empty() == true) {
                throw std::runtime_error("The module name cannot be a empty string");
            }
            
            // Get the module handle
            handle = ::dlopen(name.c_str(), RTLD_NOW | RTLD_LOCAL);
            
            // Report the error as a Exception
            if (handle == NULL) {
                std::string strError = std::string("POSIX specific error: ") + ::dlerror();
                throw std::runtime_error(strError);
            }
            
            this->handle = handle;
        }

        
        void Library::Private::unload() {
            if (this->handle != nullptr) {
                ::dlclose(this->handle);
                this->handle = nullptr;
            }
        }
        
        
        FunctionPtr Library::Private::getFunctionPtr(const std::string &name) {
            void *fnptr = nullptr;
            
            if (this->handle == nullptr) {
                throw std::runtime_error("The library must be loaded first.");
            }
            
            fnptr = ::dlsym( this->handle, name.c_str() );
            
            if (fnptr == NULL) {
                std::string strError = std::string("POSIX specific error: ") + ::dlerror();
                throw std::runtime_error(strError);
            }
            
            return fnptr;
        }
    }
}

#endif
