
#include "PluginLibrary.hpp"

#include <iostream>
#include <cassert>

namespace exeng { namespace system {    
    PluginLibrary::PluginLibrary(std::unique_ptr<Library> library_) : library(std::move(library_)) {
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

        Plugin *plugin = getPluginObject();
        if (!plugin) {
            throw std::runtime_error("PluginLibrary::PluginLibrary -> The library returned a nullptr object.");
        }

        this->plugin = plugin;
    }
    
    PluginLibrary::~PluginLibrary() {
        /*
        The plugin object depends on the library object, because 
        we get the plugin object from a routine from the library, AND
        that library is responsible of the lifetime of the plugin object.
        So, to avoid hard-to-find segmentation faults, first we must 
        terminate the plugin, and later, destroy the library object.
        */
        
        if (this->plugin) {
            this->plugin->terminate();
            this->plugin = nullptr;
        }
    }
    
    std::string PluginLibrary::getName() const {
        assert(this->plugin != nullptr);

        return this->plugin->getName();
    }
    
    std::string PluginLibrary::getDescription() const {
        assert(this->plugin != nullptr);

        return this->plugin->getDescription();
    }
    
    Version PluginLibrary::getVersion() const {
        assert(this->plugin != nullptr);

        return this->plugin->getVersion();
    }
    
    void PluginLibrary::initialize(Root *root) {
        assert(this->plugin != nullptr);

        this->plugin->initialize(root);
    }
    
    void PluginLibrary::terminate() {
        assert(this->plugin != nullptr);

        this->plugin->terminate();
    }
}}
