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
#include <exeng/Core.hpp>

namespace xe { namespace fw {
    
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
     * @brief Basic application framework
     */
    class EXENGAPI Application : public Core {
    public:
		Application() {}
		virtual ~Application() {}
        
		/**
		 * @brief Get the current state of the application.
		 */
		virtual ApplicationStatus::Enum getApplicationStatus() const = 0;

        /**
         * @brief Run the application.
         */
        virtual int run(int argc, char **argv) = 0;

    public:
        /**
         * @brief Executes the specified application
         * 
         * Captures all exceptions and writes its messages to the standard output
         * 
         * When execution completes, the Application object is destroyed.
         */
        static int execute(Application &app, int argc, char **argv);
        
        template<typename ApplicationClass>
        static int execute(int argc, char **argv) {
			return Application::execute(ApplicationClass(), argc, argv);
		}
    };
}}

#endif  // __EXENG_FRAMEWORK_APPLICATION_HPP__
