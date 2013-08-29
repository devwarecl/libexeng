
#include "RayTracerApp.hpp"

#include "SphereGeometry.hpp"
#include "samplers/JitteredSampler.hpp"

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <cstdint>
#include <list>
#include <boost/timer/timer.hpp>

namespace raytracer {

using namespace exeng;
using namespace exeng::math;
using namespace exeng::scenegraph;
using namespace exeng::graphics;
using namespace exeng::framework;
using namespace exeng::input;

using namespace raytracer::samplers;

RayTracerApp::RayTracerApp() : _defaultColor(0xFF000000), _backbuffer(nullptr), _applicationStatus(ApplicationStatus::Running) {
    _cameraView.size = Size2i(320, 200);
}


RayTracerApp::~RayTracerApp() {
    terminate();
}


void RayTracerApp::initialize(const StringVector& cmdLine) {
    
    // Initialize the exeng root class and plugins.
    std::string path;

#if defined (EXENG_WINDOWS)
    path = "";
#else
    path = "../exeng-graphics-gl3/";
#endif

    _root.reset(new Root());
    _root->getPluginManager()->load("exeng-graphics-gl3", path);
    
    // initialize the gl3 driver, in windowed mode
    _driver.reset(_root->getGraphicsManager()->createDriver());
    _driver->addEventHandler(this);
    
    DisplayMode mode;
    mode.size = Size2i(640, 480);
    mode.redBits = 8;
    mode.greenBits = 8;
    mode.blueBits = 8;
    mode.alphaBits = 8;
    mode.status = DisplayStatus::Window;
    mode.depthBits = 16;
    mode.stencilBits = 0;
    
    _driver->initialize(mode);
    
    // create the geometry (a single triangle)
    VertexFormat format;
    // VertexField field(VertexAttrib::Position, 3, DataType::Float32);
    
    format.fields.push_back(VertexField(VertexAttrib::Position, 3, DataType::Float32));
    format.fields.push_back(VertexField(VertexAttrib::TexCoord, 2, DataType::Float32));
    
    auto vertexBuffer = _driver->createVertexBuffer(format, 4);
    {
        struct Vertex {
            Vector3f coord;
            Vector2f texCoord;
        };
        
        VertexArray<Vertex> array(vertexBuffer);
        
        array[0].coord = Vector3f(-1.0f,  1.0f, 0.0f);
        array[0].texCoord = Vector2f(0.0f,  1.0f);
        
        array[1].coord = Vector3f( 1.0f,  1.0f, 0.0f);
        array[1].texCoord = Vector2f(1.0f,  1.0f);
        
        array[2].coord = Vector3f(-1.0f, -1.0f, 0.0f);
        array[2].texCoord = Vector2f(0.0f,  0.0f);
        
        array[3].coord = Vector3f( 1.0f, -1.0f, 0.0f);
        array[3].texCoord = Vector2f(1.0f,  0.0f);
    }
    _vertexBuffer.reset(vertexBuffer);
    
    // create a texture for the render targets
    auto texture = _driver->createTexture(TextureType::Tex2D, Vector3f(320, 200), ColorFormat::R8G8B8A8);
    
    struct Texel {
        std::uint8_t red;
        std::uint8_t green;
        std::uint8_t blue;
        std::uint8_t alpha;
    };
    
    Texel *textureData = reinterpret_cast<Texel*>(texture->lock());
    for (int i=0; i<320*200; ++i) {
        textureData[i].red      = 255;
        textureData[i].green    = 255;
        textureData[i].blue     = 255;
        textureData[i].alpha    = 255;
    }
    texture->unlock();
    
    _texture.reset(texture);
    
    _material.reset( new exeng::graphics::Material() );
    _material->getLayer(0)->setTexture(texture);
    
    _backbuffer = nullptr;
    
    _sampler.reset(new JitteredSampler(25));
    _scene.reset(new Scene());
    
    loadScene();    
}


double RayTracerApp::getFrameTime() const {
    return 0.0;
}


void RayTracerApp::pollEvents() {
    _driver->pollEvents();
}


ApplicationStatus RayTracerApp::getStatus() const {
    return _applicationStatus;
}


void RayTracerApp::update(double seconds) {
    
}


void RayTracerApp::render() {
    boost::timer::auto_cpu_timer autoTimer;
    
    SceneNodeList nodeList;
    Vector2i screenSize = _cameraView.size;
    Vector2i pixel;
    Color pixelColor;
    
    clear();
    flattenHierarchy(nodeList, _scene->getRootNodePtr());
    
    for(pixel.y=0; pixel.y<screenSize.y; ++pixel.y) {
        for(pixel.x=0; pixel.x<screenSize.x; ++pixel.x) {
            
            pixelColor = traceRay(nodeList, pixel);
            
            // Pintar el backbuffer 
            std::swap(pixelColor[0], pixelColor[1]);
            putPixel(pixel, static_cast<uint32_t>(pixelColor));
        }
    }

    present();
}


int RayTracerApp::getExitCode() const {
    return 0;
}


void RayTracerApp::terminate() {
    _driver->terminate();
}


uint32_t RayTracerApp::pointToOffset(const Vector2i &point) const {
#ifdef EXENG_DEBUG
    if (point.x < 0 || point.y < 0) {
        throw std::invalid_argument("");
    }
    
    if (point.x >= _cameraView.size.width) {
        throw std::invalid_argument("");
    }
    
    if (point.y >= _cameraView.size.height) {
        throw std::invalid_argument("");
    }
#endif  
    int offset = point.y * _cameraView.size.width + point.x;
    return static_cast<uint32_t>(offset);
}


void RayTracerApp::putPixel(const Vector2i &point, uint32_t color) {
    uint32_t offset = pointToOffset(point);
    uint32_t *data = static_cast<uint32_t*>(_backbuffer);
    
    data += offset;
    
    *data = color;
}


std::uint32_t RayTracerApp::getPixel(const Vector2i &point) const {
    auto offset = pointToOffset(point);
    auto data = static_cast<uint32_t*>(_backbuffer);
    
    data += offset;
    
    return *data;
}


Ray RayTracerApp::castRay(const Vector2f &pixel) const {
    const float pixelSize = _cameraView.pixelSize;
    const float halfWidth = _cameraView.size.width*0.5f;
    const float halfHeight = _cameraView.size.height*0.5f;
    
    Ray ray;
    
    // Trazar un rayo
    float x = pixelSize * (pixel.x - halfWidth + 0.5f);
    float y = pixelSize * (pixel.y - halfHeight + 0.5f);
    float z = -50.0f;
    
    ray.setPoint(Vector3f(x, y, z));
    ray.setDirection(Vector3f(0.0f, 0.0f, 1.0f));

    return ray;
}


Ray RayTracerApp::castRay(const exeng::math::Vector2f &pixel, const exeng::math::Vector2f &sample) const {
    const float pixelSize = _cameraView.pixelSize;
    const float halfWidth = _cameraView.size.width*0.5f;
    const float halfHeight = _cameraView.size.height*0.5f;
    
    Ray ray;
    
    // Trazar un rayo
    float x = pixelSize * (pixel.x - halfWidth + 0.5f + sample.x);
    float y = pixelSize * (pixel.y - halfHeight + 0.5f + sample.y);
    float z = -50.0f;
    
    // Hacia adelante
    ray.setPoint( Vector3f(x, y, z) );
    ray.setDirection( Vector3f(0.0f, 0.0f, 1.0f) );

    return ray;
}


void RayTracerApp::flattenHierarchy(SceneNodeList &out, SceneNode* node) const {
    // Poner los nodos de escena
    if (node != nullptr && node->getDataPtr() != nullptr) {
        if (node->getDataPtr()->getTypeInfo() == TypeInfo::get<Geometry>())  {
            out.push_back(node);
        }
    }

    for (auto child : node->getChilds()) {
        flattenHierarchy(out, child);
    }
}


IntersectInfo RayTracerApp::intersectRay(const SceneNodeList &nodes, const Ray &ray) const {
    IntersectInfo prevInfo, currentInfo, info;

    // Determinar colision con el contenido del nodo
    for (auto node : nodes) {
        Geometry* geometry = static_cast<Geometry*>( node->getDataPtr() );
        assert(geometry != nullptr);

        if (geometry->hit(ray, &currentInfo) == true) {
            if (prevInfo.distance == 0.0f == true || currentInfo.distance > prevInfo.distance) {
                info = currentInfo;
                
                assert(info.materialPtr != nullptr);
                assert(info.normal != Vector3f(0.0f));
            }

            prevInfo = currentInfo;
        }
    }

    return info;
}


Color RayTracerApp::traceRay(const SceneNodeList &sceneNodeList, const Vector2i &pixel) const {
    Color color(0.0f, 0.0f, 0.0f, 1.0f);
    Vector2f pixelSample = static_cast<Vector2f>(pixel);
    Ray ray = castRay(pixel, Vector2f(0.0, 0.0));
        
    // Intersectarlo con los objetos de la escena
    IntersectInfo info = intersectRay(sceneNodeList, ray);
        
    if (info.intersect == true)  {
        // Determinar el color
        auto factor = info.normal.dot(ray.getDirection());
            
        auto vcolor = info.materialPtr->getProperty4f("diffuse");
            
        color = Color(vcolor) * factor;
    } else {
        color = _scene->getBackgroundColor();
    }

    return color;
}


Color RayTracerApp::traceRayMultisampled(const SceneNodeList &sceneNodeList, const Vector2i &pixel) const {
    Color color(0.0f, 0.0f, 0.0f, 1.0f);
    
    Vector2f pixelSample = static_cast<Vector2f>(pixel);
    
    for (int i=0; i<_sampler->getSampleCount(); ++i) {
        // Trazar un rayo
        Vector2f sample = _sampler->sampleUnitSquare();
        Ray ray = castRay(pixelSample, sample);
        
        // Intersectarlo con los objetos de la escena
        IntersectInfo info = intersectRay(sceneNodeList, ray);
        
        if (info.intersect == true)  {

            // Determinar el color
            auto factor = info.normal.dot(ray.getDirection());
            auto vcolor = info.materialPtr->getProperty4f("diffuse");
            
            color += Color(vcolor) * factor;
        } else {
            color += _scene->getBackgroundColor();
        }
    }
    
    float sampleCountf = static_cast<float>(_sampler->getSampleCount());
    return color / sampleCountf;
}


void RayTracerApp::clear() {
    _driver->beginFrame(Color(0.0f, 0.0f, 0.0f, 1.0f));
    _backbuffer = _texture->lock();
}


void RayTracerApp::present() {
    _texture->unlock();
    _driver->setMaterial(_material.get());
    _driver->setVertexBuffer(_vertexBuffer.get());
    _driver->render(Primitive::TriangleStrip, 4);
    _driver->endFrame();
}


void RayTracerApp::loadScene() {
    // Crear una escena de juguete, con una esfera al centro de la escena.
    // TODO: Cargar esta escena desde un archivo XML, o similar
    auto rootNode = _scene->getRootNodePtr();
    auto sphereGeometry = new SphereGeometry();
    auto sphereGeometry2 = new SphereGeometry();
    auto sphereGeometry3 = new SphereGeometry();
    
    sphereGeometry->sphere.setAttributes(75.0, Vector3f(-100.0f, 0.0f, 0.0f));
    sphereGeometry->material.setProperty("diffuse", Vector4f(1.0f, 0.5f, 0.25f, 1.0f));
    
    sphereGeometry2->sphere.setAttributes(150.0, Vector3f(150.0f, 0.0f, 0.0f));
    sphereGeometry2->material.setProperty("diffuse", Vector4f(0.0f, 0.0f, 1.0f, 1.0f));

    sphereGeometry3->sphere.setAttributes(200.0, Vector3f(0.0f, 100.0f, 0.0f));
    sphereGeometry3->material.setProperty("diffuse", Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
    
    rootNode->addChildPtr("sphereGeometry")->setDataPtr(sphereGeometry);
    rootNode->addChildPtr("sphereGeometry2")->setDataPtr(sphereGeometry2);
    rootNode->addChildPtr("sphereGeometry3")->setDataPtr(sphereGeometry3);
}


void RayTracerApp::handleEvent(const EventData &data) {
    _applicationStatus = ApplicationStatus::Terminated;
}

}


EXENG_IMPLEMENT_MAIN(raytracer::RayTracerApp)
