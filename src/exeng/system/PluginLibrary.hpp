/**
 * @file Plugin.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_SYSTEM_PLUGINLIBRARY_HPP__
#define __EXENG_SYSTEM_PLUGINLIBRARY_HPP__

#include <stdexcept>
#include <boost/scoped_ptr.hpp>
#include <exeng/system/Plugin.hpp>
#include <exeng/system/Library.hpp>

namespace exeng {
    namespace system {
    
        /**
         * @brief Manage a plugin loaded from an external library
         */
        class PluginLibrary : public Plugin {
        public:
            PluginLibrary(Library *library);
            virtual ~PluginLibrary();
            virtual std::string getName() const;
            virtual std::string getDescription() const;
            virtual Version getVersion() const;
            virtual void initialize(Root *root);
            virtual void terminate();
            
        private:
            boost::scoped_ptr<Plugin> plugin;
            boost::scoped_ptr<Library> library;
        };
    }
}

#include "PluginLibrary.inl"

#endif // __EXENG_SYSTEM_PLUGINLIBRARY_HPP__
