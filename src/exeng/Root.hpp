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
        class EXENGAPI SceneManager;
    }
    
    namespace graphics {
        class EXENGAPI GraphicsManager;
        class EXENGAPI TextureManager;
    }
    
    /**
    * @brief The root class of the multimedia engine. 
    * 
    * Holds all the extensible interfaces of the engine.
    */
    class EXENGAPI Root {
    public:
        Root();
        ~Root();
        
        Version getVersion() const;
        
        exeng::system::PluginManager* getPluginManager();
        const exeng::system::PluginManager* getPluginManager() const;
        
        exeng::scenegraph::MeshManager* getMeshManager();
        const exeng::scenegraph::MeshManager* getMeshManager() const;
        
        exeng::graphics::GraphicsManager* getGraphicsManager();
        const exeng::graphics::GraphicsManager* getGraphicsManager() const;
        
        exeng::scenegraph::SceneManager* getSceneManager();
        const exeng::scenegraph::SceneManager* getSceneManager() const;
        
    private:
        struct Private;
        Private *impl;
    };
}

#endif	//__EXENG_ROOT_HPP__
