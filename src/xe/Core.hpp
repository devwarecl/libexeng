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

#include <xe/Config.hpp>
#include <xe/Version.hpp>

#include <xe/sys/Forward.hpp>
#include <xe/sg/Forward.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/cm/Forward.hpp>

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
        
        xe::gfx::GraphicsManager* getGraphicsManager();
        const xe::gfx::GraphicsManager* getGraphicsManager() const;
        
		xe::sg::SceneManager* getSceneManager();
        const xe::sg::SceneManager* getSceneManager() const;

		xe::cm::ComputeManager* getComputeManager();
		const xe::cm::ComputeManager* getComputeManager() const;

    private:
        struct Private;
        Private *impl = nullptr;
    };
}

#endif
