/**
 * @brief Documentacion pendiente
 */

#ifndef __EXENG_SYSTEM_PLUGINMANAGER_HPP__
#define __EXENG_SYSTEM_PLUGINMANAGER_HPP__

#include <string>

#include "../Object.hpp"

namespace exeng
{
    class EXENGAPI Root;

    namespace system
    {
        /**
         * @brief Administrador de plugins. No es instanciable directamente por el usuario
         */
        class EXENGAPI PluginManager
        {
            friend class exeng::Root;

        public:
            ~PluginManager();
            
            /**
             * @brief Devuelve una referencia al objeto central 
             */
            Root& getRoot();

            /**
             * @brief Carga el plugin que tenga el nombre indicado. 
             * 
             * En caso de que no exista, se lanza una excepcion del tipo std::runtime_error. 
             * Si el plugin es cargado exitosamente, implementa ciertas interfaces del objeto raiz indicado.
             * 
             */
            void load(const std::string &name);
            
            /**
             * @brief Descarga el plugin, liberando todos los recursos inicializados por este.
             * 
             * Durante la descarga, se remueven todos las implementaciones de interfaces puestas por el plugin
             * en el engine.
             */
            void unload(const std::string &name);

        private:
            struct Private;
            Private* impl;

            PluginManager(Root& root);
            PluginManager(const PluginManager &other);
            PluginManager& operator= (const PluginManager& other);
        };
    }
}

#endif	//__EXENG_SYSTEM_PLUGINMANAGER_HPP__
