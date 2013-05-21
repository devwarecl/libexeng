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

#include <stdexcept>
#include <map>
#include <cassert>

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <exeng/Root.hpp>
#include <exeng/system/Library.hpp>
#include <exeng/system/Plugin.hpp>
#include <exeng/system/PluginLibrary.hpp>
#include <exeng/system/PluginManager.hpp>

namespace exeng {
    namespace system {

        /**
         * @brief Private attributes of the plugin manager.
         */
        struct PluginManager::Private {
        public:
            Private() : root(nullptr) {}
            
        public:
            //! Currently loaded plugins.
            boost::ptr_map< std::string, Plugin> plugins;
            
            //! Root object
            Root* root;         
        };

        
        PluginManager::PluginManager(Root* root) : impl(nullptr) {
            if (root == nullptr) {
                char msg[] = "PluginManager::PluginManager: The root object can't be nullptr.";
                throw std::invalid_argument(msg);
            }
            
            this->impl = new PluginManager::Private();
            this->impl->root = root;
        }


        PluginManager::~PluginManager() {
            boost::checked_delete(this->impl);
        }
        
        
        void PluginManager::load(const std::string &name) {
            assert(this->impl != nullptr);
            // The library filename.
            std::string libraryName;    
            
#if defined(EXENG_WINDOWS)
            libraryName = name + std::string(".dll");
#elif defined(EXENG_UNIX)
            libraryName = std::string("lib") + name + std::string(".so");
#else
#  warning Unsupported platform. This can cause platform dependent code in client side.
            libraryName = name
#endif
            
            // check if the library is loaded previously
            if (this->impl->plugins.find(name) == this->impl->plugins.end()) {    
                Library *library = new  Library();
                library->load(libraryName);
                
                std::string keyName = name;
                this->impl->plugins.insert(keyName, new PluginLibrary(library));
            }
        }


        void PluginManager::unload(const std::string &name) {
            assert(this->impl != nullptr);
            
            auto &plugins = this->impl->plugins;
            
            // simplemente busca y elimina el elemento indicado
            auto it = plugins.find(name);
            
            if (it != plugins.end()) {
                plugins.erase(name);
            }
        }
    }
}
