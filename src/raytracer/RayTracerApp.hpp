
#ifndef __RAYTRACER_RAYTRACERAPP_HPP__
#define __RAYTRACER_RAYTRACERAPP_HPP__

#include <exeng/Exeng.hpp>
#include <vector>
#include <list>
#include <boost/scoped_ptr.hpp>

#include "samplers/Sampler.hpp"

namespace raytracer {    

typedef std::list<exeng::scenegraph::SceneNode*> SceneNodeList;
typedef SceneNodeList::iterator SceneNodeListIt;

/**
 *  @brief Define la forma en que se generara la imagen trazada
 */
struct CameraView {
    CameraView() :  size(320, 200), pixelSize(1.0f),  gamma(0.0f), invGamma(0.0) {}
    exeng::math::Size2i size;   //! Tamaño de la pantalla
    float pixelSize;            //! Tamaño de cada pixel
    float gamma;                //! Factor gamma
    float invGamma;             //! Inverso del factor gamma
};


class RayTracerApp : public exeng::framework::Application, public exeng::input::IEventHandler {
public:
    RayTracerApp();
    
    virtual ~RayTracerApp();
    
    virtual void initialize(const exeng::framework::StringVector& cmdLine);

    virtual double getFrameTime() const;
    
    virtual void pollEvents();
    
    virtual exeng::framework::ApplicationStatus getStatus() const;
    
    virtual void update(double seconds);
    
    virtual void render();
    
    virtual int getExitCode() const;
    
    virtual void terminate();
    
    virtual void handleEvent(const exeng::input::EventData &data);
    
    
private:
    std::uint32_t 
    pointToOffset(const exeng::math::Vector2i &point) const;
    
    void 
    putPixel(const exeng::math::Vector2i &point, std::uint32_t color);
    
    std::uint32_t 
    getPixel(const exeng::math::Vector2i &point) const;
    
    exeng::scenegraph::Ray 
    castRay(const exeng::math::Vector2f &pixel) const;
    
	/*
    exeng::scenegraph::Ray 
    castRay(const exeng::math::Vector2f &pixel, const exeng::math::Vector2f &sample) const;
	*/
    
    void 
    flattenHierarchy(SceneNodeList &out, exeng::scenegraph::SceneNode* node) const;

    exeng::scenegraph::IntersectInfo 
    intersectRay(const SceneNodeList &nodes, const exeng::scenegraph::Ray &ray) const;

    exeng::graphics::Color 
    traceRay(const SceneNodeList &nodeList, const exeng::math::Vector2i &pixel) const;
    
	/*
    exeng::graphics::Color 
    traceRayMultisampled(const SceneNodeList &nodeList, const exeng::math::Vector2i &pixel) const;
    */

    void clear();
    
    void present();
    
    void loadScene();
    
private:
    //! El color por defecto a usar en caso de que ningun rayo colisione con la escena.
    std::uint32_t defaultColor;
    
    //! La forma en que la escena se proyecta en la pantalla.
    CameraView cameraView;
    
    boost::scoped_ptr<exeng::Root> root;
    boost::scoped_ptr<exeng::graphics::Material> material;
    boost::scoped_ptr<exeng::graphics::GraphicsDriver> driver;
    boost::scoped_ptr<exeng::graphics::VertexBuffer> vertexBuffer;
    boost::scoped_ptr<exeng::graphics::Texture> texture;
    boost::scoped_ptr<exeng::scenegraph::Scene> scene;
    
    //! Implementa el antialias de nuestra escena
    boost::scoped_ptr<raytracer::samplers::Sampler> sampler;
    
    exeng::framework::ApplicationStatus applicationStatus;
    
    void *backbuffer;

    mutable uint32_t lastTime;

    uint32_t fpsCurrent;
    double fpsLastTime;
    double fpsCurrentTime;

	exeng::math::Vector3f eye;
};

}

#endif	//__RAYTRACER_RAYTRACERAPP_HPP__
