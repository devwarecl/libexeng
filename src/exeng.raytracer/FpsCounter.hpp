
#ifndef __RAYTRACER_FPSCOUNTER_HPP__
#define __RAYTRACER_FPSCOUNTER_HPP__

namespace raytracer {
    /**
     * @brief Simple frames per second counter
     */
    class FpsCounter {
    public:
        FpsCounter();
        
        void update(double seconds);
        
        double getCurrentFps() const;
        double getAverageFps() const;
        
        double getCurrentTime() const;

        // TODO: Find a better name.
        bool overflow() const;
        
    private:
        double currentSeconds;  //! Total ellapsed time for the current frame.
        double seconds;         //! Total ellapsed time.
        double framesDrawn;     //! Total frames drawn.
        double framesPerSecond; //! Current frames per second total.
        bool overTime = false;
    };
}

#endif  //__RAYTRACER_FPSCOUNTER_HPP__
