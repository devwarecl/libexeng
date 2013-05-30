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
        
        
        Root* PluginManager::getRoot() {
            assert(this->impl != nullptr);
            assert(this->impl->root != nullptr);
            return this->impl->root;
        }
        
        
        const Root* PluginManager::getRoot() const {
            assert(this->impl != nullptr);
            assert(this->impl->root != nullptr);
            return this->impl->root;
        }
        
        
        void PluginManager::load(const std::string &name, const std::string &path) {
            assert(this->impl != nullptr);
            
            std::string libname;    // The library filename.
            std::cout << "PluginManager: Loading module '" << name << "'" << std::endl;
            
#if defined(EXENG_WINDOWS)
            libname = name + std::string(".dll");
#elif defined(EXENG_UNIX)
            libname = std::string("lib") + name + std::string(".so");
#else
#  warning Unsupported platform. This can cause platform dependent code in client side.
            libname = name;
#endif
            if (path.empty() == false) {
                libname = path + libname;
            }
            
            // check if the library is loaded previously
            auto &plugins = this->impl->plugins;
            
            if (plugins.find(name) == plugins.end()) {
                auto *library = new Library(libname);
                auto *plugin = new PluginLibrary(library);
                
                std::string keyName = name;
                plugins.insert(keyName, plugin);
                
                plugin->initialize(this->getRoot());
            }
        }
        
        
        void PluginManager::unload(const std::string &name) {
            assert(this->impl != nullptr);
            
            auto &plugins = this->impl->plugins;
            auto it = plugins.find(name);
            
            if (it != plugins.end()) {
                it->second->terminate();
                plugins.erase(name);
            }
        }
    }
}
