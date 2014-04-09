
#include <exeng.raytracer/FpsCounter.hpp>

namespace raytracer {
    
    FpsCounter::FpsCounter() : currentSeconds(0.0),  framesDrawn(0), currentFps(0) {
    }
    
    void FpsCounter::update(double seconds) {
        this->currentSeconds += seconds;
        
        if (this->currentSeconds > 1.0) {
            this->currentFps = this->framesDrawn;
            this->framesDrawn = 0;
            this->currentSeconds -= 1.0;
        } else {
            this->framesDrawn++;
        }
    }
    
    int FpsCounter::getCurrentFps() const {
        return this->currentFps;
    }
    
    double FpsCounter::getCurrentTime() const {
        return this->currentSeconds;
    }
}
