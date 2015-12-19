/**
 *  @brief Implementa los metodos de la clase JitteredSampler, ademas de algunas funciones soporte.
 */

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "JitteredSampler.hpp"

using xe::Vector2f;

namespace raytracer { namespace samplers {
        
JitteredSampler::JitteredSampler(int sampleCount) {
    this->sampleCount = sampleCount;
    this->generateSamples();
}


/**
    * @brief Regresa un numero aleatorio entre -0.5 y 0.5
    */
float randomFloat() {
    const float randMax = static_cast<float>(RAND_MAX);
    
    float value = static_cast<float>(std::rand()) / randMax;
    
    return value - 0.5f;
}


void JitteredSampler::generateSamples() {
    int n = static_cast<int>(std::sqrt(this->sampleCount));
    Vector2f sampledPoint;
    
    for (int p=0; p<this->setCount; ++p) {
        for (int j=0; j<n; ++j) {
            for (int k=0; k<n; ++k) {
                sampledPoint.x = (k + randomFloat()) / n;
                sampledPoint.y = (j + randomFloat()) / n;
                
                this->sampleArray.push_back(sampledPoint);
            }
        }
    }
}
}}
