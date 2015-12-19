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

namespace xe {
	
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
        
        xe::sys::PluginManager* getPluginManager();
        const xe::sys::PluginManager* getPluginManager() const;
        
        xe::gfx::MeshManager* getMeshManager();
        const xe::gfx::MeshManager* getMeshManager() const;
        
        xe::gfx::GraphicsManager* getGraphicsManager();
        const xe::gfx::GraphicsManager* getGraphicsManager() const;
        
		xe::gfx::TextureManager* getTextureManager();
        const xe::gfx::TextureManager* getTextureManager() const;
        
		xe::sg::SceneManager* getSceneManager();
        const xe::sg::SceneManager* getSceneManager() const;

    private:
        struct Private;
        Private *impl = nullptr;
    };
}

#endif
