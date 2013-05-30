#include <iostream>

namespace exeng {
    namespace system {
        
        PluginLibrary::PluginLibrary(Library *library) : plugin(nullptr), library(nullptr) {
            void* ptr = nullptr;
            ExengGetPluginObjectProc getPluginObject = nullptr;
        
            // Validate non null
            if (library == nullptr) {
                throw std::invalid_argument("PluginLibrary::PluginLibrary: "
                                            "Library pointer can't be nullptr");
            }
        
            // Store the function pointer to the getter of the plugin object.
            ptr = library->getFunctionPtr(EXENG_GET_PLUGIN_OBJECT_NAME_STR);
            getPluginObject = reinterpret_cast<ExengGetPluginObjectProc>(ptr);
        
            // Store the plugin getter object.
            this->library = library;
            this->plugin = getPluginObject();
        }
        
        
        PluginLibrary::~PluginLibrary() {
            /*
            The plugin object depends on the library object, because 
            we get the plugin object from a routine from the library, AND
            that library is responsible of the lifetime of the plugin object.
            So, to avoid hard-to-find segmentation faults, first terminate the plugin,
            and later, destroy the library object.
            */
            
            assert(this->library != nullptr);
            
            this->plugin->terminate();
            this->plugin = nullptr;
            
            delete this->library;
            this->library = nullptr;
        }
        
        
        std::string PluginLibrary::getName() const {
            return this->plugin->getName();
        }
        
            
        std::string PluginLibrary::getDescription() const {
            return this->plugin->getDescription();
        }
        
        
        Version PluginLibrary::getVersion() const {
            return this->plugin->getVersion();
        }
        
        
        void PluginLibrary::initialize(Root *root) {
            this->plugin->initialize(root);
        }
        
        
        void PluginLibrary::terminate() {
            this->plugin->terminate();
        }
    }
}
