
#include <ctime>
#include <cstdlib>

#include "Sampler.hpp"

using exeng::math::Vector2f;

namespace raytracer {
    namespace samplers {
        Sampler::Sampler() {
            // Inicializa el generador de numeros aleatorios
            std::srand(std::time(nullptr));
            
            this->sampleCount = 0;
            this->setCount = 1;
            this->count = 0;
            this->jump = 0;
        }
        
        
        Sampler::~Sampler() {
        }
        
        
        Vector2f Sampler::sampleUnitSquare() {
            auto sampleIndex = this->count++ % (this->sampleCount * this->setCount);
            return this->sampleArray[sampleIndex];
        }
        
        
        void Sampler::shuffleSamples() {
        }    
        
        
        int Sampler::getSampleCount() const {
            return this->sampleCount;
        }
    }
}
