
#ifndef __RAYTRACER_SAMPLERS_SAMPLER_HPP__
#define __RAYTRACER_SAMPLERS_SAMPLER_HPP__

#include <vector>
#include <exeng/math/TVector.hpp>

namespace raytracer { namespace samplers {
    
typedef std::vector< exeng::math::Vector2f > Vector2fArray;
typedef Vector2fArray::iterator Vector2fArrayIt;

typedef std::vector<int> IntArray;
typedef IntArray::iterator IntArrayIt;


/**
*  @brief Muestreador. Permite la implementacion de distintas tecnicas 
*  de antialias.
*/
class Sampler {
public:
    
    Sampler();
    virtual ~Sampler();
    
    /**
    *  @brief Genera patrones de muestras en un cuadrado unitario
    */
    virtual void generateSamples() = 0;
    
    
    /**
    *  @brief Configura los indices randomicamente generados
    */
    void setupShuffledIndices();
    
    
    /**
    *  @brief Randomicamente remezcla las muestras en cada patron
    */
    void shuffleSamples();
    
    
    /**
    *  @brief Obtiene la siguiente muestra en el cuadrano unitario
    */
    exeng::math::Vector2f sampleUnitSquare() const;
    
    
    /**
    *  @brief Devuelve la cantidad de muestras
    */
    
    int getSampleCount() const;
    
    
protected:
    
    /**
    *  @brief Numero de puntos de muestra en un patron determinado.
    */
    int sampleCount;
    
    /**
    *  @brief El numero de patrones (conjuntos de muestra) almacenados
    */
    int setCount;
    
    /**
    *  @brief Puntos de muestra en un cuadrado unitario (pixel)
    */
    Vector2fArray sampleArray;
    
    /**
    *  @brief Indices del arreglo de muestras que estan barajados
    */
    IntArray shuffledIndices;
    
    /**
    *  @brief El numero actual de puntos de muestra usados
    */
    mutable int count;
    
    /** 
    *  @brief Salto de indice aleatorio
    */ 
    int jump;
};

}}

#endif  //__RAYTRACER_SAMPLER_HPP__
