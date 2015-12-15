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

namespace exeng {
    namespace system {
        class EXENGAPI PluginManager;
    }
    
    namespace scenegraph {
        class EXENGAPI MeshManager;
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
    class EXENGAPI Core {
    public:
        Core();
        ~Core();
        
        Version getVersion() const;
        
        exeng::system::PluginManager* getPluginManager();
        const exeng::system::PluginManager* getPluginManager() const;
        
        exeng::scenegraph::MeshManager* getMeshManager();
        const exeng::scenegraph::MeshManager* getMeshManager() const;
        
        exeng::graphics::GraphicsManager* getGraphicsManager();
        const exeng::graphics::GraphicsManager* getGraphicsManager() const;
        
		exeng::graphics::TextureManager* getTextureManager();
        const exeng::graphics::TextureManager* getTextureManager() const;
        
    private:
        struct Private;
        Private *impl = nullptr;
    };
}

#endif
