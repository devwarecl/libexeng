
#ifndef __RAYTRACER_FPSCOUNTER_HPP__
#define __RAYTRACER_FPSCOUNTER_HPP__

#include <exeng/Config.hpp>

namespace xe { namespace util {
    /**
     * @brief Simple frames per second counter
     */
    class EXENGAPI FrameCounter {
    public:
        FrameCounter();
        
        void update(double seconds);
        
        double getCurrentFps() const;
        double getAverageFps() const;
        
        double getCurrentTime() const;

        // TODO: Find a better name.
        bool overflow() const;
        
    private:
        double currentSeconds = 0.0f;  //! Total ellapsed time for the current frame.
        double seconds = 0.0f;         //! Total ellapsed time.
        double framesDrawn = 0.0f;     //! Total frames drawn.
        double framesPerSecond = 0.0f; //! Current frames per second total.
        bool overTime = false;
    };
}}

#endif  //__RAYTRACER_FPSCOUNTER_HPP__
