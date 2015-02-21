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

#include "Application.hpp"
#include <iostream>

namespace exeng { namespace framework {
    
    Application::Application()
    {
        this->root = new Root();
    }
    
    Application::~Application()  
    {
        if (this->root) {
            delete this->root;
        }
    }
    
    int Application::execute(Application &app, int argc, char** argv) 
    {
        int exitCode = 0;
        
        try {
            exitCode = app.run(argc, argv);
        } catch (std::exception &exp) {
            std::cout << "Unhandled Exception:" << std::endl;
            std::cout << exp.what() << std::endl;
        }
        
        return exitCode;
    }
}}
