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

#include <memory>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <exeng/system/Plugin.hpp>
#include <exeng/system/Library.hpp>

namespace exeng { namespace system {
    /**
     * @brief Manage a plugin loaded from an external library
     */
    class PluginLibrary : public Plugin {
    public:
        PluginLibrary(std::unique_ptr<Library> library);
        virtual ~PluginLibrary();
        virtual std::string getName() const override;
        virtual std::string getDescription() const override;
        virtual Version getVersion() const override;
        virtual void initialize(Root *root) override;
        virtual void terminate() override;
        
    private:
        std::unique_ptr<Library> library;
		std::unique_ptr<Plugin> plugin;
    };

	inline PluginLibrary::PluginLibrary(std::unique_ptr<Library> library_) : library(std::move(library_)) {
	    // check for a valid library
        if (!library) {
            throw std::invalid_argument("PluginLibrary::PluginLibrary -> Library pointer can't be nullptr");
        }
    
	    if (library->isValid() == false) {
		    throw std::logic_error("PluginLibrary::PluginLibrary -> The library object must be valid.");
	    }

        // get the plugin entry point from the library.
        void* ptr = library->getFunctionPtr(EXENG_GET_PLUGIN_OBJECT_NAME_STR);
        ExengGetPluginObjectProc getPluginObject = reinterpret_cast<ExengGetPluginObjectProc>(ptr);

	    if (!getPluginObject) {
		    std::string msg;
		    msg += "PluginLibrary::PluginLibrary -> The loaded library object ";
		    msg += "'" + library->getFileName() + "' doesn't have the exported function " ;
		    msg += "'" EXENG_GET_PLUGIN_OBJECT_NAME_STR "'.";

		    throw std::runtime_error(msg);
	    }

        auto plugin = getPluginObject();
        if (!plugin) {
            throw std::runtime_error("PluginLibrary::PluginLibrary -> The library returned a nullptr object.");
        }

        this->plugin = std::move(plugin);
    }
    
    inline PluginLibrary::~PluginLibrary() {}
    
    inline std::string PluginLibrary::getName() const {
        assert(this->plugin != nullptr);

        return this->plugin->getName();
    }
    
    inline std::string PluginLibrary::getDescription() const {
        assert(this->plugin != nullptr);

        return this->plugin->getDescription();
    }
    
    inline Version PluginLibrary::getVersion() const {
        assert(this->plugin != nullptr);

        return this->plugin->getVersion();
    }
    
    inline void PluginLibrary::initialize(Root *root) {
        assert(this->plugin != nullptr);

        this->plugin->initialize(root);
    }
    
    inline void PluginLibrary::terminate() {
        assert(this->plugin != nullptr);

        this->plugin->terminate();
    }
}}

#endif // __EXENG_SYSTEM_PLUGINLIBRARY_HPP__
