/**
 * @file Application.hpp
 * @brief Definition of the Application class.
 */

/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_FRAMEWORK_APPLICATION_HPP__
#define __EXENG_FRAMEWORK_APPLICATION_HPP__

#include <exeng/Config.hpp>
#include <exeng/Enum.hpp>
#include <exeng/Root.hpp>

namespace exeng { namespace framework {
    
    /**
     * @brief Application status
     */
    struct ApplicationStatus : public Enum {
        enum Enum {
            Running,
            Terminated
        };
    };
    
    /**
     * @brief Basic application framework.
     */
    class EXENGAPI Application {
    public:
        Application();
        
        virtual ~Application() = 0;
        
        /**
         * @brief Get the root object associated with the application instance.
         */
        Root* getRoot();
        
        /**
         * @brief Get the root object associated with the application instance.
         */
        const Root* getRoot() const;
        
        /**
         * @brief Run the application.
         * 
         * Must be implemented in derived classes.
         */
        virtual int run(int argc, char **argv);
        
    private:
        Root *root;
        
    private:
        static Application *instance;
        
    public:
        /**
         * @brief Get the currenly running application. If is null, 
         * then the application has been terminated.
         */
        static Application* getInstance();
        
        /**
         * @brief Executes the specified application
         * 
         * Captures all exceptions and 
         * writes its messages to the standard output
         * 
         * When execution completes, the Application object is destroyed.
         */
        static int execute(Application *app, int argc, char **argv);
        
        template<typename ApplicationClass>
        static int execute(int argc, char **argv);
    };
}}

#include <exeng/framework/Application.inl>

#endif  // __EXENG_FRAMEWORK_APPLICATION_HPP__
