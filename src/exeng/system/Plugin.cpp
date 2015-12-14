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

#include <exeng/system/Plugin.hpp>
#include <stdexcept>

namespace exeng {
    namespace system  {
        Plugin::~Plugin() {
        }
        
        std::string Plugin::getName() const {
            throw std::logic_error("Plugin::getName not implemented");
        }

        std::string Plugin::getDescription() const  {
            throw std::logic_error("Plugin::getDescription not implemented");
        }
        
        Version Plugin::getVersion() const {
            throw std::logic_error("Plugin::getVersion not implemented");
        }

        void Plugin::initialize(Root *root) {
            throw std::logic_error("Plugin::initialize not implemented");
        }
        
        void Plugin::terminate() {
            throw std::logic_error("Plugin::terminate not implemented");
        }
        
        
        std::string Plugin::toString() const {
            return this->getName() + "\n" + this->getDescription() + "\n";
        }
    }
}
