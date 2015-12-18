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


#ifndef __EXENG_CORE_HPP__
#define __EXENG_CORE_HPP__

#include <exeng/Config.hpp>
#include <exeng/Version.hpp>

#include <exeng/system/Forward.hpp>
#include <exeng/scenegraph/Forward.hpp>
#include <exeng/graphics/Forward.hpp>

namespace exeng {
	
    /**
    * @brief The root class of the multimedia engine. 
    * 
    * Holds all the extensible interfaces of the engine.
    */
    class EXENGAPI Core {
    public:
        Core();
        virtual ~Core();
        
        Version getVersion() const;
        
        exeng::system::PluginManager* getPluginManager();
        const exeng::system::PluginManager* getPluginManager() const;
        
        exeng::graphics::MeshManager* getMeshManager();
        const exeng::graphics::MeshManager* getMeshManager() const;
        
        exeng::graphics::GraphicsManager* getGraphicsManager();
        const exeng::graphics::GraphicsManager* getGraphicsManager() const;
        
		exeng::graphics::TextureManager* getTextureManager();
        const exeng::graphics::TextureManager* getTextureManager() const;
        
		exeng::scenegraph::SceneManager* getSceneManager();
        const exeng::scenegraph::SceneManager* getSceneManager() const;

    private:
        struct Private;
        Private *impl = nullptr;
    };
}

#endif
