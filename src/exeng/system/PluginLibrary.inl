
namespace exeng {
    namespace system {
        
        PluginLibrary::PluginLibrary(Library *library) {
            void* ptr = nullptr;
            ExengGetPluginObjectProc getPluginObject = nullptr;
        
            // Validate non null
            if (!library) {
                throw std::invalid_argument("PluginLibrary::PluginLibrary: Library pointer can't be nullptr");
            }
        
            // Store the function pointer to the getter of the plugin object.
            ptr = library->getFunctionPtr(EXENG_GET_PLUGIN_OBJECT_NAME_STR);
            getPluginObject = reinterpret_cast<ExengGetPluginObjectProc>(ptr);
        
            // Store the plugin getter object.
            this->library.reset(library);
            this->plugin.reset(getPluginObject());
        }
        
        
        PluginLibrary::~PluginLibrary() {}
        
        
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
