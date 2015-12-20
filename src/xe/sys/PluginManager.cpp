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
#include <boost/filesystem.hpp>

#include <xe/Core.hpp>
#include <xe/Exception.hpp>
#include <xe/sys/Library.hpp>
#include <xe/sys/Plugin.hpp>
#include <xe/sys/PluginLibrary.hpp>

namespace xe { namespace sys {
    namespace fs = boost::filesystem;
    
    /**
     * @brief Private attributes of the plugin manager.
     */
    typedef std::map<std::string, std::unique_ptr<Plugin>> PluginMap;

    struct PluginManager::Private 
    {
        Core* root = nullptr;
        PluginMap plugins;
        fs::path pluginPath;
    };
    
    PluginManager::PluginManager(Core* root) : impl(nullptr) 
    {
        if (root == nullptr) {
			EXENG_THROW_EXCEPTION("The root object can't be nullptr.");
        }
        
        this->impl = new PluginManager::Private();
        this->impl->root = root;
        
        this->impl->pluginPath = fs::current_path();
    }

    PluginManager::~PluginManager() 
    {
        delete this->impl;
        this->impl = nullptr;
    }
    
    Core* PluginManager::getCore() 
    {
        assert(this->impl != nullptr);
        assert(this->impl->root != nullptr);

        return this->impl->root;
    }
        
    const Core* PluginManager::getCore() const 
    {
        assert(this->impl != nullptr);
        assert(this->impl->root != nullptr);

        return this->impl->root;
    }
    
    std::string getPluginFilename(const std::string &pluginName) 
    {
#if defined(EXENG_WINDOWS)
        return pluginName + std::string(".dll");
#elif defined(EXENG_UNIX)
        return std::string("lib") + pluginName + std::string(".so");
#else
#  warning Unsupported platform. This can cause platform dependent code in client side.
        return pluginName;
#endif        
    }
    
    void PluginManager::loadPlugin(const std::string &name) 
    {
        assert(this->impl != nullptr);
        
        std::string libname = getPluginFilename(name);
        
        fs::path pluginFilename = this->impl->pluginPath;
        pluginFilename /= libname;
        
        // check if the library is loaded previously
        PluginMap &plugins = this->impl->plugins;
        
        if (plugins.find(name) == plugins.end()) {

            LibraryPtr library = std::make_unique<Library>(pluginFilename.string());
            PluginPtr pluginLibrary = std::make_unique<PluginLibrary>(std::move(library));

            plugins[name] = std::move(pluginLibrary);
            plugins[name]->initialize(this->getCore());
        }
    }
    
    void PluginManager::unloadPlugin(const std::string &name) 
    {
        assert(this->impl != nullptr);
        
        auto &plugins = this->impl->plugins;
        auto it = plugins.find(name);
            
        if (it != plugins.end()) {
            it->second->terminate();
            plugins.erase(name);
        }
    }
    
    void PluginManager::setPluginPath(const std::string &path)
    {
        assert(this->impl != nullptr);
        
        fs::path pluginPath(path);
        
        if (pluginPath.is_relative()) {
            pluginPath = fs::absolute(pluginPath);
        }
        
        pluginPath = pluginPath.normalize().parent_path();
        
        if (!fs::is_directory(pluginPath) || !fs::exists(pluginPath)) {
			EXENG_THROW_EXCEPTION("The directory '" + pluginPath.string() + "' is not valid.");
        }
        
        this->impl->pluginPath = pluginPath;
    }
    
    std::string PluginManager::getPluginPath() const
    {
        assert(this->impl != nullptr);
        
        return this->impl->pluginPath.string();
    }
    
    void PluginManager::loadPlugins() 
    {
		EXENG_THROW_EXCEPTION("Not implemented.");
    }
}}
