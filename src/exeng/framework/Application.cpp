/**
 * @file Application.cpp
 * @brief Implementation of the Application class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <exeng/framework/Application.hpp>
#include <memory>
#include <iostream>

namespace exeng { namespace framework {

Application::~Application() {}

int Application::run(Application *theApp, const StringVector& cmdLine) {
    
    std::unique_ptr<Application> app(theApp);
    
    int exitCode = 0;
    double seconds = 0.0;
    
    app->initialize(cmdLine);
    
    while (app->getStatus() != ApplicationStatus::Terminated) {
        seconds = app->getFrameTime();
        
        app->pollEvents();
        app->update(seconds);
        app->render();
    }
    
    app->terminate();
    
    exitCode = app->getExitCode();
    return exitCode;
    
    /*
    try {
        int exitCode = 0;
        double seconds = 0.0;
        
        app->initialize(cmdLine);
        
        while (app->getStatus() != ApplicationStatus::Terminated) {
            seconds = app->getFrameTime();
            
            app->pollEvents();
            app->update(seconds);
            app->render();
        }
        
        app->terminate();
        
        exitCode = app->getExitCode();
        return exitCode;
        
    } catch(const std::exception &exp) {
        std::cout << "Unhandled exception:" << std::endl ;
        std::cout << exp.what() << std::endl;
        return -1;
    }
    */
}

}}
