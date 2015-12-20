
#include "FrameCounter.hpp"

#include <cmath>

namespace xe { namespace util {
    FrameCounter::FrameCounter() {}
    
    void FrameCounter::update(double seconds) 
	{
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
    
    double FrameCounter::getCurrentFps() const 
	{
        return this->framesPerSecond;
    }
    
    double FrameCounter::getCurrentTime() const {
        return this->currentSeconds;
    }
    
    double FrameCounter::getAverageFps() const 
	{
        return this->framesDrawn / this->seconds;
    }

    bool FrameCounter::overflow() const 
	{
        return this->overTime;
    }
}}
