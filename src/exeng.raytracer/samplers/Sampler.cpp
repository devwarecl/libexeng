
#include <ctime>
#include <cstdlib>
#include <cstdint>

#include "Sampler.hpp"

using exeng::math::Vector2f;

namespace raytracer { namespace samplers {
    
    Sampler::Sampler() {
        // Inicializa el generador de numeros aleatorios
        auto time = std::time(nullptr);
        std::srand(static_cast<std::uint32_t>(time));
    
        this->sampleCount = 0;
        this->setCount = 1;
        this->count = 0;
        this->jump = 0;
    }


    Sampler::~Sampler() {
    }


    Vector2f Sampler::sampleUnitSquare() const {
        auto sampleIndex = this->count++ % (this->sampleCount * this->setCount);
        return this->sampleArray[sampleIndex];
    }


    void Sampler::shuffleSamples() {
    }    


    int Sampler::getSampleCount() const {
        return this->sampleCount;
    }

    const exeng::math::Vector2f* Sampler::getSampleData() const {
        return this->sampleArray.data();
    }
}}
