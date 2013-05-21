/**
 *  @brief Define la interfaz privada de la implementacion de la clase RayTracerApp
 */

#ifndef __RAYTRACER_RAYTRACERAPPPRIVATE_HPP__
#define __RAYTRACER_RAYTRACERAPPPRIVATE_HPP__

#include <list>
#include <memory>

#include <SDL/SDL.h>
#include <exeng/graphics/Color.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/scenegraph/Geometry.hpp>
#include <exeng/scenegraph/Sphere.hpp>
#include <exeng/scenegraph/SceneNode.hpp>
#include <exeng/scenegraph/Scene.hpp>

#include "RayTracerApp.hpp"
#include "SphereGeometry.hpp"
#include "RayTracerApp.hpp"
#include "./samplers/Sampler.hpp"

typedef std::list<exeng::scenegraph::SceneNode*> SceneNodeList;
typedef SceneNodeList::iterator SceneNodeListIt;

using namespace exeng;
using namespace exeng::math;
using namespace exeng::scenegraph;
using namespace exeng::graphics;

namespace raytracer {
    
    /**
     *  @brief Define la forma en que se generara la imagen trazada
     */
    struct CameraView {
    public:
        /**
         *  @brief Define los atributos por defecto.
         */
        CameraView() {
            this->size = Vector2i(320, 200);
            this->pixelSize = 1.0f;
            this->gamma = 0.0f;
            this->invGamma = 0.0f;
        }
        
    public:
        /**
         *  @brief Porte de la pantalla
         */
        Vector2i size;              
        
        /**
         *  @brief El tamaño de cada pixel
         */
        float pixelSize;            
        
        /**
         *  @brief El factor gamma
         */
        float gamma;
        
        /**
         *  @brief El inverso del factor gamma
         */
        float invGamma;             
    };
    
    
    /**
     *  @brief Atributos y metodos privados de la aplicacion
     */
    struct RayTracerApp::Private {        
    public:
        
        /**
         *  @brief Asigna valores por defecto a la aplicacion
         */
        Private();
        
        /**
         * @brief Convierte una posicion bidimensional en una unidimensional
         */
        std::uint32_t pointToOffset(const Vector2i &point) const;
        
        /**
         *  @brief Establece el color de un pixel
         */
        void putPixel(const Vector2i &point, std::uint32_t color);
        
        /**
         * @brief Devuelve el color de un pixel
         */
        std::uint32_t getPixel(const Vector2i &point) const;
        
        /**
         * @brief Crea un rayo a partir de las coordenadas de pantalla indicadas
         */
        Ray castRay(const exeng::math::Vector2f &pixel) const;
        
        
        /**
         * @brief Crea un rayo a partir de las coordenadas de pantalla indicadas, con el punto
         * de muestra indicado
         */
        Ray castRay(const exeng::math::Vector2f &pixel, const exeng::math::Vector2f &sample) const;
        
        /**
         *  @brief Aplana la jerarquia de un nodo de escena.
         */
        void flattenHierarchy(SceneNodeList &out, SceneNode* node) const;

        /**
         *  @brief Detecta si existe colision entre un rayo y algun nodo de la lista de nodos, 
         *  devolviendo la informacion colision con el objeto mas cercano al rayo indicado.
         *  @return Devuelve el estado de la interseccion
         */
        IntersectInfo intersectRay(const SceneNodeList &nodes, const Ray &ray) const;
        
        
        /**
         *  @brief Calcula el color del pixel indicado
         */
        Color traceRay(const SceneNodeList &nodeList, const exeng::math::Vector2i &pixel) const;
        
        
        /**
         *  @brief Limpia el backbuffer
         */
        void clear();
        
        /**
         *  @brief Presenta los resultados actuales a la pantalla
         */
        void present();
        
        
        /**
         *  @brief Carga la escena
         */
        void loadScene();
        
        
    public:
        
        /**
         *  @brief El color por defecto en caso de que ningun rayo colisione con la escena
         */
        std::uint32_t defaultColor;
        
        /**
         *  @brief El backbuffer SDL. Guarda el resultado del render.
         */
        SDL_Surface *backbuffer;
        
        /**
         *  @brief Estado intermedio de un evento de SDL
         */
        SDL_Event event;
        
        /**
         *  @brief Estado de ejecucion de la aplicacion.
         */
        bool running;
        
        /**
         *  @brief La forma en que la escena se proyecta en la pantalla.
         */
        CameraView cameraView;
        
        /**
         *  @brief La escena actual de la aplicacion. 
         */
        std::unique_ptr<Scene> scene;
        
        /**
         *  @brief Implementa el antialias de nuestra escena
         */
        std::unique_ptr<raytracer::samplers::Sampler> sampler;
    };
}

#endif  //__RAYTRACER_RAYTRACERAPPPRIVATE_HPP__
