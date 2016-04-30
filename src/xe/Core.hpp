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

#include <xe/sys/PluginManager.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/TextureManager.hpp>
#include <xe/gfx/MeshManager.hpp>
#include <xe/sg/SceneManager.hpp>
#include <xe/cm/ComputeManager.hpp>

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

		xe::sys::PluginManager pluginManager;
    };
}

#endif
