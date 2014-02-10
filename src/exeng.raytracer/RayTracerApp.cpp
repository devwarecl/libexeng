
#include <exeng.raytracer/RayTracerApp.hpp>
#include <exeng.raytracer/samplers/JitteredSampler.hpp>
#include <exeng.raytracer/tracers/SoftwareTracer.hpp>
#include <exeng.main/Main.hpp>

#include <algorithm>
#include <cassert>
#include <cfloat>
#include <stdexcept>
#include <cstdint>
#include <list>
#include <array>

#include <exeng/graphics/HeapVertexBuffer.hpp>
#include <exeng/graphics/Material.hpp>

namespace raytracer {
    
    using namespace exeng;
    using namespace exeng::math;
    using namespace exeng::scenegraph;
    using namespace exeng::graphics;
    using namespace exeng::framework;
    using namespace exeng::input;
    
    using namespace raytracer::samplers;
    
    /**
     * @brief Check for collisions between a box and a ray
     * @todo Put a epsilon value
     */
    bool intersect(const Boxf &box, const Ray &ray, IntersectInfo *info) {
        Vector3f minEdge = box.getMin();
        Vector3f maxEdge = box.getMax();
        
        Vector3f rayPoint = ray.getPoint();
        Vector3f rayDirection = ray.getDirection();
        
        float near = -std::numeric_limits<float>::max();
        float far = std::numeric_limits<float>::max();
        
        // For each coord, get the near and far intersection distances
        for (int coord=0; coord<3; ++coord) {
            
            // Ray is parallel to current coordinate
            if (rayDirection[coord] == 0.0f) { 
                if (rayPoint[coord] < minEdge[coord] || rayPoint[coord] > maxEdge[coord]) {
                    if ( info != nullptr ) {
                        info->intersect = false;
                    }
                    
                    return false;
                }
                
                continue;
            }
            
            // Ray is not parallel. Continue compute of the intersection
            // TODO: cache the inv direction of the ray, for calculation speed-up
            float invRayDirection = 1.0f / rayDirection[coord];
            float t1 = (minEdge[coord] - rayPoint[coord]) / invRayDirection;
            float t2 = (maxEdge[coord] - rayPoint[coord]) / invRayDirection;
            
            if (t1 > t2) {
                std::swap(t1, t2);
            }
            
            if (t1 > near) {
                near = t1;
            }
            
            if (t2 < far) {
                far = t2;
            }
            
            if (near > far) {
                if (info != nullptr) {
                    info->intersect = false;
                }
                
                return false;
            }
            
            if (far < 0.0f) {
                if (info != nullptr) {
                    info->intersect = false;
                }
                
                return false;
            }
        }
        
        // Compute intersection point
        if (info != nullptr) {
            info->intersect = true;
            info->point = ray.getPointAt(near);
            
            // Compute face normal
            info->normal = Vector3f::zero();
            
            const float epsilon = 0.00001f;
            
            for (int coord=0; coord<3; ++coord) {
                if (abs(info->point[coord] - minEdge[coord]) <= epsilon) {
                    info->normal[coord] = -1.0f;
                    break;
                }
                
                if (abs(info->point[coord] - maxEdge[coord]) <= epsilon) {
                    info->normal[coord] = 1.0f;
                    break;
                }
            }
            
            info->distance = near;
        }
        
        return true;
    }
    
    
    bool intersect(const Plane &plane, const Ray &ray, IntersectInfo *info) {
        return plane.intersect(ray, info);
    }
    
    
    bool intersect(const Sphere &sphere, const Ray &ray, IntersectInfo *info) {
        return sphere.intersect(ray, info);
    }
    
    
    template<typename Solid>
    class BasicGeometry : public exeng::scenegraph::Geometry {
    public:
        BasicGeometry() : material(nullptr) {}
        
        BasicGeometry(const Solid solid_, const exeng::graphics::Material* material_) : solid(solid_), material(material_) {}
        
        virtual bool hit(const exeng::scenegraph::Ray &ray, exeng::scenegraph::IntersectInfo *intersectInfo) {
            bool intersection = intersect(this->solid, ray, intersectInfo);
            
            if (intersection==true && intersectInfo!=nullptr) {
                intersectInfo->materialPtr = this->material;
            }
            
            return intersection;
        }
        
        virtual exeng::math::Boxf getBox() const {
            return Boxf();
        }
    
        Solid solid;
        const exeng::graphics::Material* material;
    };
    
    
    RayTracerApp::RayTracerApp() 
        : 
            defaultColor(0xFFFFFFFF), 
            applicationStatus(ApplicationStatus::Running),
            lastTime(Timer::getTime()), 
            fpsCurrent(0), 
            fpsLastTime(0.0), 
            fpsCurrentTime(0.0) {
        
        for (int i=0; i<ButtonCode::Count; ++i) {
            this->buttonStatus[i] = ButtonStatus::Release;
        }
    }
    
    
    RayTracerApp::~RayTracerApp() {
        this->terminate();
    }
    
    
    void RayTracerApp::initialize(const StringVector& cmdLine) {
        // Initialize the exeng root class and plugins.
        std::string path;
    
    #ifdef EXENG_WINDOWS
    #  ifdef EXENG_DEBUG
        path = "../../bin/Debug/";
    #  else
        path = "../../bin/Release/";
    #  endif
    #else 
        // con ruta actual ${PROJECT}
        path = "../exeng-graphics-gl3/";
    #endif
    
        this->root.reset(new Root());
        this->root->getPluginManager()->load("exeng-graphics-gl3", path);
        
        // initialize the gl3 driver, in windowed mode
        this->driver.reset(this->root->getGraphicsManager()->createDriver());
        this->driver->addEventHandler(this);
        
        this->driver->initialize();
        DisplayMode mode = this->driver->getDisplayMode();
        
        // create the geometry (a single triangle)
        auto vertexBuffer = this->driver->createVertexBuffer(VertexFormat::makeVertex2D(), 4);
        {        
            VertexArray<Vertex2D> array(vertexBuffer);
            
            array[0].coord = Vector3f(-1.0f,  1.0f, 0.0f);
            array[0].texCoord = Vector2f(0.0f,  1.0f);
            
            array[1].coord = Vector3f( 1.0f,  1.0f, 0.0f);
            array[1].texCoord = Vector2f(1.0f,  1.0f);
            
            array[2].coord = Vector3f(-1.0f, -1.0f, 0.0f);
            array[2].texCoord = Vector2f(0.0f,  0.0f);
            
            array[3].coord = Vector3f( 1.0f, -1.0f, 0.0f);
            array[3].texCoord = Vector2f(1.0f,  0.0f);
        }
        this->vertexBuffer.reset(vertexBuffer);
        
        // create a texture for the render targets
        auto texture = this->driver->createTexture(
            TextureType::Tex2D, 
            Vector3f(static_cast<float>(mode.size.width), 
            static_cast<float>(mode.size.height)), 
            ColorFormat::getColorFormatR8G8B8A8()
        );
        
        struct Texel {
            std::uint8_t red;
            std::uint8_t green;
            std::uint8_t blue;
            std::uint8_t alpha;
        };
        
        Texel *textureData = reinterpret_cast<Texel*>(texture->lock());
        for (int i=0; i<mode.size.width * mode.size.height; ++i) {
            textureData[i].red      = 255;
            textureData[i].green    = 255;
            textureData[i].blue     = 255;
            textureData[i].alpha    = 255;
        }
        texture->unlock();
        
        this->texture.reset(texture);
        
        this->material.reset( new exeng::graphics::Material() );
        this->material->getLayer(0)->setTexture(texture);
        
        this->sampler.reset(new JitteredSampler(25));
        this->sampler->generateSamples();
        
        this->scene.reset(new Scene());
        this->scene->setBackgroundColor(Color(1.0f, 1.0f, 1.0f, 1.0));
        
        this->loadScene();
        
        this->camera.reset( new Camera() );
        this->camera->setLookAt(Vector3f(0.0f, 0.0f, 0.0f));
        this->camera->setPosition(Vector3f(0.0f, 2.0f, -75.0f));
        this->camera->setUp(Vector3f(0.0f, 1.0f, 0.0f));
        
        // this->tracer.reset(new raytracer::tracers::SoftwareTracer(this->texture.get(), this->scene.get(), this->sampler.get()));
        this->tracer.reset(new raytracer::tracers::SoftwareTracer(this->texture.get(), this->scene.get(), nullptr));
    }
    
    
    double RayTracerApp::getFrameTime() const {
        uint32_t lastTime = Timer::getTime();
        double frameTime = static_cast<double>(lastTime - this->lastTime) / 1000.0;
        this->lastTime = lastTime;
    
        return frameTime;
    }
    
    
    void RayTracerApp::pollEvents() {
        this->driver->pollEvents();
    }
    
    
    ApplicationStatus RayTracerApp::getStatus() const {
        return this->applicationStatus;
    }
    
    
    void RayTracerApp::update(double seconds) {
        // Actualizar los cuadros por segundo
        if (this->fpsCurrentTime >= 1.0) {
            uint32_t fps = this->fpsCurrent;
            this->fpsCurrent = 0;
            this->fpsCurrentTime = 0.0;
    
            std::cout << "FPS: " << fps << std::endl;
        } else {
            this->fpsCurrent += 1;
            this->fpsCurrentTime += seconds;
        }
    
        // actualiza la camara en funcion de la entrada por teclado
        if (this->buttonStatus[ButtonCode::KeyEsc]) {
            this->applicationStatus = ApplicationStatus::Terminated;
        }
    
        if (this->buttonStatus[ButtonCode::KeyUp]) {
            auto cameraPosition = this->camera->getPosition();
            cameraPosition.z += 2.5f;
            this->camera->setPosition(cameraPosition);
        }
    
        if (this->buttonStatus[ButtonCode::KeyDown]) {
            auto cameraPosition = this->camera->getPosition();
            cameraPosition.z -= 2.5f;
            this->camera->setPosition(cameraPosition);
        }
    
        if (this->buttonStatus[ButtonCode::KeyRight]) {
            auto cameraPosition = this->camera->getPosition();
            cameraPosition.x += 2.5f;
            this->camera->setPosition(cameraPosition);
        }
    
        if (this->buttonStatus[ButtonCode::KeyLeft]) {
            auto cameraPosition = this->camera->getPosition();
            cameraPosition.x -= 2.5f;
            this->camera->setPosition(cameraPosition);
        }
    }
    
    void RayTracerApp::render() {
        this->clear();
        this->tracer->render(this->camera.get());
        this->present();
    }
    
    int RayTracerApp::getExitCode() const {
        return 0;
    }
    
    
    void RayTracerApp::terminate() {
        this->driver->terminate();
    }
    
    
    void RayTracerApp::clear() {
        this->driver->beginFrame(Color(0.0f, 0.0f, 0.0f, 1.0f));
    }
    
    
    void RayTracerApp::present() {
        this->driver->setMaterial(this->material.get());
        this->driver->setVertexBuffer(this->vertexBuffer.get());
        this->driver->render(Primitive::TriangleStrip, 4);
        this->driver->endFrame();
    }
    
    
    void RayTracerApp::loadScene() {
        // Crear una escena de juguete, con una esfera al centro de la escena.
        // TODO: Cargar esta escena desde un archivo XML, o similar
        auto rootNode = this->scene->getRootNodePtr();
        auto sphereGeometry = new BasicGeometry<Sphere>();
        auto sphereGeometry2 = new BasicGeometry<Sphere>();
        
        Material *sphereGeometryMaterial = new Material();
        sphereGeometryMaterial->setProperty("diffuse", Vector4f(1.0f, 0.5f, 0.25f, 1.0f));
        sphereGeometry->material = sphereGeometryMaterial;
        sphereGeometry->solid.setAttributes(25.0f, Vector3f(-50.0f, 0.0f, 0.0f));
        
        Material *sphereGeometry2Material = new Material();
        sphereGeometry2Material->setProperty("diffuse", Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
        sphereGeometry2->material = sphereGeometry2Material;
        sphereGeometry2->solid.setAttributes(40.0f, Vector3f(60.0f, 0.0f, 0.0f));
        
        // sphereGeometry3->sphere.setAttributes(200.0, Vector3f(0.0f, 100.0f, 0.0f));
        // sphereGeometry3->material.setProperty("diffuse", Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
        // auto vertexBuffer = new HeapVertexBuffer(nullptr, 
        
        rootNode->addChildPtr("sphereGeometry")->setDataPtr(sphereGeometry);
        rootNode->addChildPtr("sphereGeometry2")->setDataPtr(sphereGeometry2);
        // rootNode->addChildPtr("sphereGeometry3")->setDataPtr(sphereGeometry3);
        
        Mesh *mesh = new Mesh(1);
        
        VertexBuffer *vertexBuffer = new HeapVertexBuffer(nullptr, VertexFormat::makeStandardVertex(), 6);
        {
            VertexArray<StandardVertex> vertices(vertexBuffer);
            
            vertices[0].coord = Vector3f(0.0f, 15.0f, 0.0f);
            vertices[0].normal = Vector3f(0.0f, 0.0f, -1.0f);
            vertices[0].texCoord = Vector2f(0.0f, 0.0f);
            
            vertices[1].coord = Vector3f(15.0f, -15.0f, 0.0f);
            vertices[1].normal = Vector3f(0.0f, 0.0f, -1.0f);
            vertices[1].texCoord = Vector2f(1.0f, 0.0f);
            
            vertices[2].coord = Vector3f(-15.0f, -15.0f, 0.0f);
            vertices[2].normal = Vector3f(0.0f, 0.0f, -1.0f);
            vertices[2].texCoord = Vector2f(0.0f, 1.0f);
        }
        
        this->meshMaterial.reset( new exeng::graphics::Material() );
        this->meshMaterial->setProperty("diffuse", Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
        
        /*
        mesh->getPart(0)->setVertexBuffer(vertexBuffer);
        mesh->getPart(0)->setPrimitiveType(Primitive::TriangleList);
        mesh->getPart(0)->setMaterial(this->meshMaterial.get());
        rootNode->addChildPtr("triangleMesh")->setDataPtr(mesh);
        */
    
        Geometry* planeGeometry = new BasicGeometry<Plane>(
            Plane( Vector3f(0.0f, -1.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f) ),
            this->meshMaterial.get()
        );
        
        // Mostrar una caja en pantalla
        this->boxMaterial.reset( new exeng::graphics::Material() );
        this->boxMaterial->setProperty("diffuse", Vector4f(1.0f, 0.3f, 0.2f, 1.0f));
    
        Geometry* boxGeometry = new BasicGeometry<Boxf>(
            Boxf(-Vector3f(18.0f) + Vector3f(0.0f, 5.0f, 0.0f), Vector3f(18.0f) + Vector3f(0.0f, 5.0f, 0.0f)),
            this->boxMaterial.get()
        );
        
        rootNode->addChildPtr("boxGeometry")->setDataPtr(boxGeometry);
        rootNode->addChildPtr("planeGeometry")->setDataPtr(planeGeometry);
    }
    
    
    void RayTracerApp::handleEvent(const EventData &data) {
        if (data.eventType == TypeId<InputEventData>()) {
            const InputEventData &inputEventData = data.cast<InputEventData>();
            this->buttonStatus[ inputEventData.buttonCode ] = inputEventData.buttonStatus;
        } else if (data.eventType == TypeId<CloseEventData>()) {
            this->applicationStatus = ApplicationStatus::Terminated;
        }
    }
}


namespace exeng { namespace main {
	int main(int argc, char **argv) {
		return exeng::framework::RunApplication<raytracer::RayTracerApp>(exeng::framework::StringVector());
	}
}}

