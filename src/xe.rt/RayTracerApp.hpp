
#pragma once

#ifndef __xe_rt_raytracerapp_hpp__
#define __xe_rt_raytracerapp_hpp__

#include <xe/ApplicationRT.hpp>

namespace xe { namespace rt {

    class RayTracerApp : public ApplicationRT {
    public:
        RayTracerApp();
        virtual ~RayTracerApp();
    
        virtual void initialize();
		virtual void terminate();

		virtual void doEvents();
		virtual void update(const float seconds);
		virtual void render();

		virtual bool isRunning() const;
    
    private:
        
    };
}}

#endif 
