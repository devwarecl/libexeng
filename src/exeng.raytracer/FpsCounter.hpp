
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
        
        int getCurrentFps() const;
        
        double getCurrentTime() const;
        
    private:
        double currentSeconds;
        int framesDrawn;
        int currentFps;
    };
}

#endif  //__RAYTRACER_FPSCOUNTER_HPP__
