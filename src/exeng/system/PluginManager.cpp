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

#include "../Root.hpp"
#include "Library.hpp"
#include "Plugin.hpp"

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <stdexcept>
#include <map>
#include <cassert>

namespace exeng {
    namespace system {
        typedef boost::shared_ptr<Plugin> PluginSharedPtr;
        typedef boost::scoped_ptr<Plugin> PluginScopedPtr;
        typedef boost::shared_ptr<Library> LibraryPtr;


        /**
         * @brief External library plugin object.
         * 
         * Object oriented interface to the functions exported by the dynamic library.
         */
        class PluginLibrary : public Plugin {
        public:
            
            PluginLibrary(LibraryPtr libraryPtr) {
                FunctionPtr functionPtr;
                ExengGetPluginObjectProc getPluginObjectProc;

                // Validate non null
                if (!libraryPtr) {
                    throw std::invalid_argument("");
                }

                // Store the function pointer to the plugin getter
                functionPtr = libraryPtr->getFunctionPtr(EXENG_GET_PLUGIN_OBJECT_NAME_STR);
                getPluginObjectProc = (ExengGetPluginObjectProc) functionPtr;

                // Store the plugin getter object.
                this->libraryPtr = libraryPtr;
                this->pluginPtr.reset(getPluginObjectProc());
            }


            virtual ~PluginLibrary() { }


            virtual std::string getName() const {
                return this->pluginPtr->getName();
            }

                
            virtual std::string getDescription() const {
                return this->pluginPtr->getDescription();
            }


            virtual Version getVersion() const {
                return this->pluginPtr->getVersion();
            }

            
            virtual void initialize(Root &root) {
                this->pluginPtr->initialize(root);
            }


            virtual void terminate() {
                this->pluginPtr->terminate();
            }


        private:
            LibraryPtr libraryPtr;
            PluginScopedPtr pluginPtr;
        };
        

        /**
         * @brief Plugin map of smart pointers
         * @todo Consider the use of the boost map pointer class.
         */
        typedef std::map<std::string, PluginSharedPtr> PluginMap;   
        typedef PluginMap::iterator PluginMapIt;

        
        /**
         * @brief Private attributes of the plugin manager.
         */
        struct PluginManager::Private {
        public:
            Private() : root(nullptr) {
            }
            
        public:
            PluginMap plugins;  //! The currently loaded plugins.
            Root* root;         //! The root object
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

            std::string libraryName;    // The library filename.
            libraryName = name;         // TODO: Get the library filename

            // check if the library is loaded previously
            if (this->impl->plugins.find(name) == this->impl->plugins.end()) {
                LibraryPtr libraryPtr = boost::make_shared<Library>();
                libraryPtr->load(libraryName);
                
                PluginSharedPtr pluginPtr = boost::make_shared<PluginLibrary>(libraryPtr);

                this->impl->plugins[name] = pluginPtr;
            }
        }


        void PluginManager::unload(const std::string &name) {
            assert(this->impl != nullptr);
            
            auto it = this->impl->plugins.find(name);

            // simplemente busca y elimina el elemento indicado
            if (it != this->impl->plugins.end()) {
                this->impl->plugins.erase(name);
            }
        }
    }
}
