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
    class EXENGAPI Core;
}

namespace exeng { namespace system {
    /**
     * @brief Administrador de plugins. No es instanciable directamente por el usuario
     */
    class EXENGAPI PluginManager {
        friend class exeng::Core;

        PluginManager(const PluginManager &other) = delete;
        PluginManager& operator= (const PluginManager& other) = delete; 

    private:
        PluginManager(Core* root);
            
    public:
        ~PluginManager();
        
        /**
         * @brief Get a pointer to the root object
         */
        Core* getCore();
            
        /**
         * @brief Get a pointer to the root object
         */
        const Core* getCore() const;
        
        /**
         * @brief Load a plugin from a dynamic module (SO/DLL).
         * @param name The name of the plugin. Under UNIX platforms, is the name of the filename,
         * without prefix and filename extension. Undex Windows platforms, is the name of the DLL name,
         * again, without the extension.
         * @param path The folder for wich load the specified plugin.
         */
        void loadPlugin(const std::string &name);
        
        /**
         * @brief Unload a plugin from the current list of loaded plugins.
         * @param name The name of the plugin. Under UNIX platforms, is the name of the filename,
         * without prefix and filename extension. Undex Windows platforms, is the name of the DLL name,
         * again, without the extension.
         */
        void unloadPlugin(const std::string &name);
        
        void setPluginPath(const std::string &path);
        
        std::string getPluginPath() const;
        
        /**
         * @brief Load all available plugins
         */
        void loadPlugins();
        
    private:
        struct Private;
        Private* impl = nullptr;
    };
}}

#endif	//__EXENG_SYSTEM_PLUGINMANAGER_HPP__
