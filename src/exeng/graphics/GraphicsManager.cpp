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


#include <exeng/graphics/GraphicsManager.hpp>

#include <stdexcept>
#include <map>
#include <sstream>
#include <cassert>
#include <boost/range/algorithm/find_if.hpp>

namespace exeng { namespace graphics {
    typedef std::map<GraphicsDriverInfo, IGraphicsDriverFactory*> GraphicsDriverFactoryMap;
    
    struct GraphicsManager::Private {
         GraphicsDriverFactoryMap factories;
    };
    
    GraphicsManager::GraphicsManager() : impl(new GraphicsManager::Private()) {
    }

    GraphicsManager::~GraphicsManager() {
        delete this->impl;
        this->impl = nullptr;
    }

    void GraphicsManager::addDriverFactory(IGraphicsDriverFactory* factory) {
        assert( this->impl != nullptr );
        
        if (factory == nullptr) {
            throw std::invalid_argument("GraphicsManager::addDriverFactory: the factory can't be null");
        }
        
        GraphicsDriverInfo driverInfo = factory->getDriverInfo();
        this->impl->factories.insert({driverInfo, factory});
    }

    void GraphicsManager::removeDriverFactory(IGraphicsDriverFactory* factory) {
        assert( this->impl != nullptr );
        
        if (factory == nullptr) {
            throw std::invalid_argument("GraphicsManager::addDriverFactory -> The factory can't be a null pointer.");
        }

        GraphicsDriverFactoryMap &factories = this->impl->factories;
        auto key = factory->getDriverInfo();
        auto pos = factories.find(key);
        
        if (pos == factories.end()) {
            throw std::runtime_error("GraphicsManager::addDriverFactory -> The factory isn't in the graphics manager instance.");
        }
        
        factories.erase(pos);
    }
    
    GraphicsDriver* GraphicsManager::createDriver() {
        assert( this->impl != nullptr );
        
        //! TODO: Actually, implement the algorithm
        for (auto element : this->impl->factories) {
            return element.second->create();
        }
        
        return nullptr;
    }
    
    GraphicsDriver* GraphicsManager::createDriver(const GraphicsDriverInfo &info) {
        assert( this->impl != nullptr );
        
        auto &factories = this->impl->factories;
        auto pos = factories.find(info);
        
        if (pos == factories.end()) {
            throw std::runtime_error("GraphicsManager::createDriver -> Driver with the specified info not registered.");
        }
        
        return pos->second->create();
    }
}}
