/**
 * @file Application.inl
 * @brief Definition of the Application class inline methods.
 */

/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


// Because the functions listed here are excepted to be called a big
// numbers of times, they will be stay here as inline method calls.

namespace exeng { namespace framework {    
    inline Root* Application::getRoot() {
        return this->root;
    }
    
    inline const Root* Application::getRoot() const {
        return this->root;
    }
    
    inline Application* Application::getInstance() {
        // this singleton version is ad-hoc, in the sense that the global instance is not
        // created by calls to this method. Instead, are created by the client software.
        return Application::instance;
    }
    
    
    template<typename ApplicationClass>
    inline int Application::execute(int argc, char **argv) {
        return Application::execute(new ApplicationClass(), argc, argv);
    }
}}
