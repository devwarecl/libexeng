/**
 * @file Application.cpp
 * @brief Implementation of the Application class.
 */

/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <exeng/framework/Application.hpp>
#include <memory>
#include <iostream>

namespace exeng { namespace framework {
    
    Application* Application::instance = nullptr;
    
    Application::Application() : root(nullptr) {
        if (Application::instance) {
            throw std::logic_error("Application::Application: Another application instance is still running. Concurrent application executions are not yet supported.");
        }
        
        this->root = new Root();
        
        Application::instance = this;
    }
    
    
    Application::~Application()  {
        Application::instance = nullptr;
        
        if (this->root) {
            delete this->root;
        }
    }
    
    
    int Application::run(int argc, char **argv) {
        throw std::logic_error("Application::run must be implemented.");
    }
    
    
    int Application::execute(Application *app, int argc, char** argv) {
        if (!app) {
            throw std::logic_error("Application::execute: The application object can't be 'nullptr'.");
        }

        return app->run(argc, argv);
    }
}}
