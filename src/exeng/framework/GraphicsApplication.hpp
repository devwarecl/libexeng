/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
#define __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__

#include <boost/scoped_ptr.hpp>

#include <exeng/Root.hpp>
#include <exeng/framework/Application.hpp>
#include <exeng/system/PluginManager.hpp>
#include <exeng/graphics/GraphicsManager.hpp>
#include <exeng/scenegraph/SceneManager.hpp>
#include <exeng/scenegraph/MeshManager.hpp>

namespace exeng { namespace framework {
    class GraphicsApplication : public exeng::framework::Application {
    public:
        GraphicsApplication();
        
        virtual ~GraphicsApplication();
        
        virtual void initialize();
        
        virtual void terminate();
        
        virtual void initializePlugins() = 0;
        virtual void terminatePlugins() = 0;
        
        virtual void initializeAssets() = 0;
        virtual void terminateAssets() = 0;
        
    private:
        boost::scoped_ptr<exeng::Root> root;
        boost::scoped_ptr<exeng::scenegraph::SceneManager> sceneManager;
        boost::scoped_ptr<exeng::scenegraph::MeshManager> meshManager;
    };
}}


namespace exeng { namespace framework {

    GraphicsApplication::GraphicsApplication() : 
        root(new exeng::Root()),
        sceneManager( new exeng::scenegraph::SceneManager() ),
        meshManager( new exeng::scenegraph::MeshManager() )
    {
    }
    
    
    GraphicsApplication::~GraphicsApplication() {}
    
    
    void GraphicsApplication::initialize() {
        this->initializePlugins();
        this->initializeAssets();
    }
    
    
    void GraphicsApplication::terminate() {
        this->terminateAssets();
        this->terminatePlugins();
    }
}}

#include <exeng/framework/GraphicsApplication.inl>

#endif // __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
