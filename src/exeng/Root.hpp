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

namespace graphics {
    class EXENGAPI GraphicsManager;
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
    
    exeng::system::PluginManager* getPluginManager();
    const exeng::system::PluginManager* getPluginManager() const;
    
    exeng::scenegraph::MeshManager* getMeshManager();
    const exeng::scenegraph::MeshManager* getMeshManager() const;
    
    exeng::graphics::GraphicsManager* getGraphicsManager();
    const exeng::graphics::GraphicsManager* getGraphicsManager() const;
    
    Version getVersion() const;
    
private:
    struct Private;
    Private *impl;
};
}

#endif	//__EXENG_ROOT_HPP__
