/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
#define __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__

#include <exeng/framework/Application.hpp>

namespace exeng { namespace framework {
    
    /**
     * @brief Default application interface for graphics applications
     */
    class GraphicsApplication : public Application {
    public:
        GraphicsApplication();
        
        virtual ~GraphicsApplication() = 0;
        
        virtual int run(int argc, char **argv);
        
    protected:
        virtual int getExitCode() const;
        
        virtual ApplicationStatus::Enum getStatus() const;
        
        virtual void initialize(int argc, char **argv);
        
        virtual void terminate();
        
        virtual void pollEvents();
        
        virtual void update(double frameTime);
        
        virtual void render();
        
    protected:
        /* App wide root object */
        Root* getRoot();
        const Root* getRoot() const;
        
    private:
        Root *root;
    };
}}


#include <exeng/framework/GraphicsApplication.inl>

#endif // __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
