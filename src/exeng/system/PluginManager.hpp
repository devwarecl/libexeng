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

#ifndef __EXENG_SYSTEM_PLUGINMANAGER_HPP__
#define __EXENG_SYSTEM_PLUGINMANAGER_HPP__

#include <string>
#include <exeng/Object.hpp>

namespace exeng {
    class EXENGAPI Root;

    namespace system {
        /**
         * @brief Administrador de plugins. No es instanciable directamente por el usuario
         */
        class EXENGAPI PluginManager {
            friend class exeng::Root;

        private:
            PluginManager(Root* root);
            
        public:
            ~PluginManager();
            
            /**
             * @brief Devuelve una referencia al objeto central 
             */
            Root* getRoot();
            
            /**
             * @brief Load a plugin from a dynamic module (SO/DLL)
             * @param name The name of the plugin. Under UNIX platforms, is the name of the filename,
             * without prefix and filename extension. Undex Windows platforms, is the name of the DLL name,
             * again, without the extension.
             */
            void load(const std::string &name);
            
            /**
             * @brief Unload a plugin from the current list of loaded plugins.
             * @param name The name of the plugin. Under UNIX platforms, is the name of the filename,
             * without prefix and filename extension. Undex Windows platforms, is the name of the DLL name,
             * again, without the extension.
             */
            void unload(const std::string &name);

        private:
            struct Private;
            Private* impl;

            
            // Not implemented methods
        private:
            PluginManager(const PluginManager &other);
            PluginManager& operator= (const PluginManager& other); 
        };
    }
}

#endif	//__EXENG_SYSTEM_PLUGINMANAGER_HPP__
