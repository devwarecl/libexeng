/**
 * @file Root.hpp
 * @brief Define the main class of the Engine.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_ROOT_HPP__
#define __EXENG_ROOT_HPP__

#include <exeng/Config.hpp>
#include <exeng/Version.hpp>

namespace exeng {
	namespace system {
		class EXENGAPI PluginManager;
	}

    namespace scenegraph {
        class EXENGAPI MeshManager;
    }
    
    /**
     * @brief The root class of the multimedia engine. 
     *
     * Permits the creation of various objects of several modules.
     */
	class EXENGAPI Root {
	public:
		Root();
		~Root();
        
        /**
         * @brief Get the current plugin manager.
         */
		exeng::system::PluginManager* getPluginManager();
        
        /**
         * @brief Get the current plugin manager.
         */
		const exeng::system::PluginManager* getPluginManager() const;
        
        /**
         * @brief Get the current mesh manager.
         */
        exeng::scenegraph::MeshManager* getMeshManager();
        
        /**
         * @brief Get the current mesh manager.
         */
        const exeng::scenegraph::MeshManager* getMeshManager() const;
        
        /**
         * @brief getVersion
         */
        Version getVersion() const;
        
	private:
		struct Private;
		Private *impl;
	};
}

#endif	//__EXENG_ROOT_HPP__
