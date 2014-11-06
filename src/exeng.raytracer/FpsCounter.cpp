
#include <exeng.raytracer/FpsCounter.hpp>

#include <cmath>

namespace raytracer {
    FpsCounter::FpsCounter() : currentSeconds(0.0), seconds(0.0), framesDrawn(0.0), framesPerSecond(0.0) {
    }
    
    void FpsCounter::update(double seconds) {
        this->seconds += seconds;
        this->currentSeconds += seconds;
        
        if (currentSeconds > 1.0) {
            this->overTime = true;
        } else {
            this->overTime = false;
        }

        this->framesDrawn++;
        this->framesPerSecond = 1.0 / seconds;
        
        this->currentSeconds = std::fmod(this->currentSeconds, 1.0);
    }
    
    double FpsCounter::getCurrentFps() const {
        return this->framesPerSecond;
    }
    
    double FpsCounter::getCurrentTime() const {
        return this->currentSeconds;
    }
    
    double FpsCounter::getAverageFps() const {
        return this->framesDrawn / this->seconds;
    }

    bool FpsCounter::overflow() const {
        return this->overTime;
    }
}
