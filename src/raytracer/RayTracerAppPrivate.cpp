/**
 *  @brief Implementa la interfaz privada de la clase RayTracerAppPrivate
 */

#include "RayTracerAppPrivate.hpp"
#include "samplers/JitteredSampler.hpp"

#include <boost/timer/timer.hpp>

using namespace exeng;
using namespace exeng::scenegraph;
using namespace raytracer;
using namespace raytracer::samplers;

namespace raytracer {
    
    RayTracerApp::Private::Private() {
        this->defaultColor = 0xFF000000;
        this->backbuffer = nullptr;
        this->running = false;
        this->cameraView.size = Vector2i(320, 200);
        
        this->sampler.reset(new JitteredSampler(25));
        this->scene.reset(new Scene());
    }
    
    
    uint32_t RayTracerApp::Private::pointToOffset(const Vector2i &point) const {
#ifdef EXENG_DEBUG
        if (point.x < 0 || point.y < 0) {
            throw std::invalid_argument("");
        }
        
        if (point.x >= this->cameraView.size.x) {
            throw std::invalid_argument("");
        }
        
        if (point.y >= this->cameraView.size.y) {
            throw std::invalid_argument("");
        }
#endif  
        auto offset = point.y * this->cameraView.size.x + point.x;
        return static_cast<uint32_t>(offset);
    }
    
    
    void RayTracerApp::Private::putPixel(const Vector2i &point, uint32_t color) {
        uint32_t offset = this->pointToOffset(point);
        uint32_t *data = static_cast<uint32_t*>(this->backbuffer->pixels);
        
        data += offset;
        
        *data = color;
    }
    
    
    std::uint32_t RayTracerApp::Private::getPixel(const Vector2i &point) const {
        auto offset = this->pointToOffset(point);
        auto data = static_cast<uint32_t*>(this->backbuffer->pixels);
        
        data += offset;
        
        return *data;
    }
    
    
    Ray RayTracerApp::Private::castRay(const Vector2f &pixel) const {
        const auto pixelSize = this->cameraView.pixelSize;
        const auto halfSize = Vector2f(this->cameraView.size) * 0.5f;
        
        Ray ray;
        
        // Trazar un rayo
        float x = pixelSize * ( pixel.x - halfSize.x + 0.5f);
        float y = pixelSize * ( pixel.y - halfSize.y + 0.5f);
        float z = -50.0f;
        
        ray.setPoint(Vector3f(x, y, z));
        ray.setDirection(Vector3f(0.0f, 0.0f, 1.0f));

        return ray;
    }
    
    
    Ray RayTracerApp::Private::castRay(const exeng::math::Vector2f &pixel, const exeng::math::Vector2f &sample) const {
        const auto pixelSize = this->cameraView.pixelSize;
        const auto halfSize = Vector2f(this->cameraView.size) * 0.5f;
        
        Ray ray;
        
        // Trazar un rayo
        float x = pixelSize * ( pixel.x - halfSize.x + 0.5f + sample.x);
        float y = pixelSize * ( pixel.y - halfSize.y + 0.5f + sample.y);
        float z = -50.0f;
        
        // Hacia adelante
        ray.setPoint( Vector3f(x, y, z) );
        ray.setDirection( Vector3f(0.0f, 0.0f, 1.0f) );

        return ray;
    }
    
    
    void RayTracerApp::Private::flattenHierarchy(SceneNodeList &out, SceneNode* node) const {
        // Poner los nodos de escena
        if (node != nullptr && node->getDataPtr() != nullptr) {
            if (node->getDataPtr()->getTypeInfo() == TypeInfo::get<Geometry>())  {
                out.push_back(node);
            }
        }

        for (auto child : node->getChilds()) {
            this->flattenHierarchy(out, child);
        }
    }


    IntersectInfo RayTracerApp::Private::intersectRay(const SceneNodeList &nodes, const Ray &ray) const {
        IntersectInfo prevInfo, currentInfo, info;

        // Determinar colision con el contenido del nodo
        for (auto node : nodes) {
            Geometry* geometry = static_cast<Geometry*>( node->getDataPtr() );
            assert(geometry != nullptr);

            if (geometry->hit(ray, &currentInfo) == true) {
                
                bool isFirst = prevInfo.distance == 0.0f;
                bool isBetter = currentInfo.distance > prevInfo.distance;

                if (isFirst == true || isBetter == true) {
                    info = currentInfo;
                    
                    assert(info.materialPtr != nullptr);
                    assert(info.normal != Vector3f(0.0f));
                }

                prevInfo = currentInfo;
            }
        }

        return info;
    }
    
    
    Color RayTracerApp::Private::traceRay(const SceneNodeList &sceneNodeList, const Vector2i &pixel) const {
        
        Color color(0.0f, 0.0f, 0.0f, 1.0f);
        
        Vector2f pixelSample = static_cast<Vector2f>(pixel);
        
        for (int i=0; i<this->sampler->getSampleCount(); ++i) {
            
            // Trazar un rayo
            Vector2f sample = this->sampler->sampleUnitSquare();
            Ray ray = this->castRay(pixel, sample);
            
            // Intersectarlo con los objetos de la escena
            IntersectInfo info = this->intersectRay(sceneNodeList, ray);
            
            if (info.intersect == true)  {
                // Determinar el color
                auto factor = info.normal.dot(ray.getDirection());
                
                auto vcolor = info.materialPtr->getProperty4f("diffuse");
                
                color += Color(vcolor) * factor;
            } else {
                color += this->scene->getBackgroundColor();
            }
        }
        
        auto sampleCountf = static_cast<float>(this->sampler->getSampleCount());
        return color / sampleCountf;
    }
    
    
    void RayTracerApp::Private::clear() {
        SDL_Rect screenRect = {0};
        
        screenRect.w = this->cameraView.size.x;
        screenRect.h = this->cameraView.size.y;
        
        SDL_FillRect(this->backbuffer, &screenRect, 0xFF000000);
        SDL_LockSurface(this->backbuffer);
    }
    
    
    void RayTracerApp::Private::present() {
        SDL_UnlockSurface(this->backbuffer);
        SDL_Flip(this->backbuffer);
    }
    
    
    void RayTracerApp::Private::loadScene() {
        // Crear una escena de juguete, con una esfera al centro de la escena.
        // TODO: Cargar esta escena desde un archivo XML, o similar
        auto rootNode = this->scene->getRootNodePtr();
        auto sphereGeometry = new SphereGeometry();
        auto sphereGeometry2 = new SphereGeometry();
        
        sphereGeometry->sphere.setAttributes(75.0, Vector3f(-100.0f, 0.0f, 0.0f));
        sphereGeometry->material.setProperty("diffuse", Vector4f(1.0f, 0.5f, 0.25f, 1.0f));
        
        sphereGeometry2->sphere.setAttributes(150.0, Vector3f(150.0f, 0.0f, 0.0f));
        sphereGeometry2->material.setProperty("diffuse", Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
        
        rootNode->addChildPtr("sphereGeometry")->setDataPtr(sphereGeometry);
        rootNode->addChildPtr("sphereGeometry2")->setDataPtr(sphereGeometry2);
    }
}
