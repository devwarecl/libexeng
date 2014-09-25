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

#include "PluginManager.hpp"

#include <cassert>
#include <stdexcept>
#include <map>
#include <memory>
#include <iostream>
#include <exeng/Root.hpp>
#include <exeng/system/Library.hpp>
#include <exeng/system/Plugin.hpp>
#include <exeng/system/PluginLibrary.inl>

namespace exeng { namespace system {
    /**
     * @brief Private attributes of the plugin manager.
     */
    typedef std::map<std::string, std::unique_ptr<Plugin>> PluginMap;

    struct PluginManager::Private {
        PluginMap plugins;      //! Currently loaded plugins.
        Root* root = nullptr;   //! Root object
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
        delete this->impl;
        this->impl = nullptr;
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
    
    void PluginManager::load(const std::string &name, const std::string &path_) {
        assert(this->impl != nullptr);
            
        std::string path = path_;
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
            if (path[path.size()-1] != '/') {
                path += '/';
            }
                
            libname = path + libname;
        }
        
        // check if the library is loaded previously
        PluginMap &plugins = this->impl->plugins;
        
        if (plugins.find(name) == plugins.end()) {
            // std::string keyName = name;
            auto library = std::unique_ptr<Library>(new Library(libname));
            auto pluginLibrary = std::unique_ptr<Plugin>(new PluginLibrary(std::move(library)));

            plugins[name] = std::move(pluginLibrary);
            plugins[name]->initialize(this->getRoot());
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
}}
