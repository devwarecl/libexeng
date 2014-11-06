
#include <exeng.raytracer/tracers/SoftwareTracer.hpp>
#include <exeng/scenegraph/Geometry.hpp>

namespace raytracer { namespace tracers {

    using namespace exeng;
    using namespace exeng::graphics;
    using namespace exeng::scenegraph;
    using namespace raytracer::samplers;
    
    inline uint32_t SoftwareTracer::getOffset(const Vector2i &point) const {
        auto size = this->getRenderTarget()->getSize();
        
#ifdef EXENG_DEBUG
        if (point.x < 0 || point.y < 0) {
            throw std::invalid_argument("");
        }
        
        if (point.x >= size.x) {
            throw std::invalid_argument("");
        }
        
        if (point.y >= size.y) {
            throw std::invalid_argument("");
        }
#endif  
        int offset = point.y * size.x + point.x;
        return static_cast<uint32_t>(offset);
    }
    
    inline void SoftwareTracer::putPixel(std::uint32_t *backbuffer, const Vector2i &point, const std::uint32_t color) {
        backbuffer += this->getOffset(point);
        *backbuffer = color;
    }
    
    inline std::uint32_t SoftwareTracer::getPixel(std::uint32_t *backbuffer, const Vector2i &point) const {
        backbuffer += this->getOffset(point);
        return *backbuffer;
    }
    
    inline Ray SoftwareTracer::castRay(const Vector2f &pixel, const Camera *camera) const {
        // trazar el rayo usando una proyeccion ortografica
        const auto size = this->getRenderTarget()->getSize();
        const float pixelSize = 1.0f;
        const float halfWidth = (size.x - 1) * 0.5f;
        const float halfHeight = (size.y - 1) * 0.5f;
        const float d = -150.0f;    // arbitrario
        
        // Trazar un rayo
        const float x = pixelSize * (pixel.x - halfWidth + 0.5f);
        const float y = pixelSize * (pixel.y - halfHeight + 0.5f);
        const float z = -d;
        
        Ray ray;
        ray.setPoint(camera->getPosition());
        ray.setDirection(Vector3f(x, y, z));
        
        return ray;
    }
    
    inline Ray SoftwareTracer::castRay(const Vector2f &pixel, const Camera *camera, const Vector2f &sample) const {
        const auto size = this->getRenderTarget()->getSize();
        const float pixelSize = 1.0f;
        const float halfWidth = (size.x - 1) * 0.5f;
        const float halfHeight = (size.y - 1) * 0.5f;
        const float d = -150.0f;    // arbitrario
        
        // Trazar un rayo
        const float x = pixelSize * (pixel.x - halfWidth  + sample.x);
        const float y = pixelSize * (pixel.y - halfHeight + sample.y);
        const float z = -d;
        
        Ray ray;
        ray.setPoint(camera->getPosition());
        ray.setDirection(Vector3f(x, y, z));
    
        return ray;
    }
    
    inline IntersectInfo SoftwareTracer::intersectRay(const std::list<const SceneNode*> &nodes, const Ray &ray) const {
        IntersectInfo currentInfo, info;
        
        info.distance = std::numeric_limits<float>::max();
        
        // Determinar colision con el contenido del nodo
        for (auto node : nodes) {
            Geometry* geometry = static_cast<Geometry*>( node->getData() );
            assert(geometry != nullptr);
    
            if (geometry->hit(ray, &currentInfo) == true) {
                if (currentInfo.distance < info.distance) {
                    info = currentInfo;
                    
                    assert(info.material != nullptr);
                    assert(info.normal != Vector3f(0.0f));
                }
            }
        }
    
        return info;
    }
    
    inline Color SoftwareTracer::traceRayMultisampled(const std::list<const SceneNode*> &nodeList, const Vector2i &pixel, const Camera* camera) const {
        Color color(0.0f, 0.0f, 0.0f, 1.0f);
        Vector2f pixelSample = static_cast<Vector2f>(pixel);
        
        for (int i=0; i<this->getSampler()->getSampleCount(); ++i) {
            // Trazar un rayo
            Vector2f sample = this->getSampler()->sampleUnitSquare();
            Ray ray = this->castRay(pixelSample, camera, sample);
            
            // Intersectarlo con los objetos de la escena
            IntersectInfo info = this->intersectRay(nodeList, ray);
            
            if (info.intersect == true)  {
                // Determinar el color
                auto vcolor = info.material->getProperty4f("diffuse");
                color += Color(vcolor);
            } else {
                color += this->getScene()->getBackColor();
            }
        }
        
        float sampleCountf = static_cast<float>(this->getSampler()->getSampleCount());
        return color / sampleCountf;
    }
    
    
    inline Color SoftwareTracer::traceRay(const std::list<const SceneNode*> &nodeList, const Vector2i &pixel, const Camera *camera) const {
        Color color(0.0f, 0.0f, 0.0f, 1.0f);
    //    Vector2f pixelSample = static_cast<Vector2f>(pixel);
        Ray ray = this->castRay(pixel, camera);
        
        // Intersectarlo con los objetos de la escena
        IntersectInfo info = this->intersectRay(nodeList, ray);
        
        if (info.intersect == true)  {
            // Determinar el color
            auto vcolor = info.material->getProperty4f("diffuse");
            color = Color(vcolor);
            
            if (color.red < 0.0f)   {color.red = 0.0f;}
            if (color.green < 0.0f) {color.green = 0.0f;}
            if (color.blue < 0.0f)  {color.blue = 0.0f;}
            if (color.alpha < 0.0f) {color.alpha = 0.0f;}
            
        } else {
            color = this->getScene()->getBackColor();
        }
    
        return color;
    }
    
    
    inline void SoftwareTracer::flattenHierarchy(std::list<const SceneNode*> &out, const SceneNode* node) const {
        // Poner los nodos de escena
        if (node != nullptr && node->getData() != nullptr) {
            if (node->getData()->getTypeInfo() == TypeId<Geometry>())  {
                out.push_back(node);
            }
        }
        
        for (auto child : node->getChilds()) {
            this->flattenHierarchy(out, child);
        }
    }
    
    SoftwareTracer::SoftwareTracer(const Scene *scene, const Sampler *sampler) : Tracer(scene, sampler) {
    }
    
    SoftwareTracer::~SoftwareTracer() {}
    
    void SoftwareTracer::render(const Camera *camera) {
#if defined(EXENG_DEBUG)
        if (!this->getScene()) {
            throw std::runtime_error("SoftwareTracer::render: The 'scene' attribute can't be a nullptr.");
        }

        if (!camera) {
            throw std::runtime_error("SoftwareTracer::render: The camera parameter can't be a nullptr.");
        }
#endif
        uint32_t *backbuffer = static_cast<uint32_t*>(this->getRenderTarget()->lock());
        
        std::list<const SceneNode*> nodeList;
        this->flattenHierarchy(nodeList, this->getScene()->getRootNode());
        
        Vector2i pixel(0);
        Vector2i screenSize = Vector2i(this->getRenderTarget()->getSize());
        
        if (!this->getSampler()) {
            // No sampler rendering
            for(pixel.y=0; pixel.y<screenSize.y; ++pixel.y) {
                for(pixel.x=0; pixel.x<screenSize.x; ++pixel.x) {
                    Color pixelColor = this->traceRay(nodeList, pixel, camera);
                    this->putPixel(backbuffer, pixel, static_cast<uint32_t>(pixelColor));
                }
            }
        } else {
            // Sampler based rendering.
            for(pixel.y=0; pixel.y<screenSize.y; ++pixel.y) {
                for(pixel.x=0; pixel.x<screenSize.x; ++pixel.x) {
                    Color pixelColor = this->traceRayMultisampled(nodeList, pixel, camera);
                    this->putPixel(backbuffer, pixel, static_cast<uint32_t>(pixelColor));
                }
            }
        }
        
        this->getRenderTarget()->unlock();
    }
}}
