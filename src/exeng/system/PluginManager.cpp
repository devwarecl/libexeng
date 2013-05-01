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
         * @brief Plugin cargado que es cargado desde una biblioteca externa.
         * 
         * Es una interfaz orientada a objetos de los metodos exportados por el plugin
         */
        class PluginLibrary : public Plugin {
        public:
            
            /**
             * @brief Inicializa los objetos internos del plugin.
             */
            PluginLibrary(LibraryPtr libraryPtr) {
                FunctionPtr functionPtr;
                ExengGetPluginObjectProc getPluginObjectProc;

                // Validar que el parametro sea correcto
                if (!libraryPtr) {
                    throw std::invalid_argument("");
                }

                // Obtener la funcion que nos devolvera el objeto plugin
                functionPtr = libraryPtr->getFunctionPtr(EXENG_GET_PLUGIN_OBJECT_NAME_STR);
                getPluginObjectProc = (ExengGetPluginObjectProc) functionPtr;

                // Obtener el objeto de plugin
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
         * @brief Mapa de punteros inteligentes de Plugin
         */
        typedef std::map<std::string, PluginSharedPtr> PluginMap;
        
        
        /**
         * @brief Iterador del tipo PluginMap
         */
        typedef PluginMap::iterator PluginMapIt;

        
        struct PluginManager::Private {
            /**
             * @brief Los plugins actualmente cargados 
             */
            PluginMap plugins;
        };


        PluginManager::PluginManager(Root& root) : impl(NULL) {
            this->impl = new PluginManager::Private();
        }


        PluginManager::~PluginManager() {
            boost::checked_delete(this->impl);
        }
        
        
        void PluginManager::load(const std::string &name) {
            assert(this->impl != NULL);

            // el nombre de archivo de la libreria
            std::string libraryName;

            // determinar el nombre de archivo (depende del sistema operativo)
            libraryName = name;

            // determinar si la libreria solicitada estaba cargada con anterioridad
            if (this->impl->plugins.find(name) == this->impl->plugins.end()) {
                LibraryPtr libraryPtr;
                PluginSharedPtr pluginPtr;
                
                libraryPtr.reset(new Library());
                libraryPtr->load(libraryName);
                
                pluginPtr.reset( new PluginLibrary(libraryPtr) );
                
                this->impl->plugins[name] = pluginPtr;
            }
        }


        void PluginManager::unload(const std::string &name) {
            assert(this->impl != NULL);
            
            auto it = this->impl->plugins.find(name);

            // simplemente busca y elimina el elemento indicado
            if (it != this->impl->plugins.end()) {
                this->impl->plugins.erase(name);
            }
        }
    }
}
