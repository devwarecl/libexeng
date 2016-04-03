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
#include <xe/Exception.hpp>
#include <xe/sys/Plugin.hpp>
#include <xe/sys/Library.hpp>

namespace xe { namespace sys {
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
        virtual void initialize(Core *root) override;
        virtual void terminate() override;
        
    private:
        std::unique_ptr<Library> library;
		std::unique_ptr<Plugin> plugin;
    };

	inline PluginLibrary::PluginLibrary(std::unique_ptr<Library> library_) : library(std::move(library_)) {
        assert(library);
        assert(library->isValid());
	
		std::string getPluginObjectNameStr = "";

#if defined(EXENG_WINDOWS)
#  if defined(EXENG_32)
		getPluginObjectNameStr += "_";
		getPluginObjectNameStr += EXENG_GET_PLUGIN_OBJECT_NAME_STR;
		getPluginObjectNameStr += "@4";
#  else 
		getPluginObjectNameStr += EXENG_GET_PLUGIN_OBJECT_NAME_STR;
#  endif

#else 
		getPluginObjectNameStr += EXENG_GET_PLUGIN_OBJECT_NAME_STR;
#endif

        // get the plugin entry point from the library.
        void* ptr = library->getFunctionPtr(getPluginObjectNameStr);
        auto getPluginObject = reinterpret_cast<ExengGetPluginObjectProc>(ptr);

	    if (!getPluginObject) {
		    std::string msg;
		    msg += "The loaded library object ";
		    msg += "'" + library->getFileName() + "' doesn't have the exported function " ;
		    msg += "'" EXENG_GET_PLUGIN_OBJECT_NAME_STR "'.";

			EXENG_THROW_EXCEPTION(msg);
	    }

        std::unique_ptr<Plugin> plugin;

		getPluginObject(plugin);
        if (!plugin) {
			EXENG_THROW_EXCEPTION("The library returned a nullptr object.");
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
    
    inline void PluginLibrary::initialize(Core *root) {
        assert(this->plugin != nullptr);

        this->plugin->initialize(root);
    }
    
    inline void PluginLibrary::terminate() {
        assert(this->plugin != nullptr);

        this->plugin->terminate();
    }
}}

#endif // __EXENG_SYSTEM_PLUGINLIBRARY_HPP__
