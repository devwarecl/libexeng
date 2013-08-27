
#include "OpenGLApp.hpp"
#include <cstdint>

using namespace exeng;
using namespace exeng::math;
using namespace exeng::graphics;
using namespace exeng::framework;
using namespace exeng::input;

namespace raytracer {

OpenGLApp::OpenGLApp() {
    this->applicationStatus = ApplicationStatus::Running;
}


OpenGLApp::~OpenGLApp () {
    this->terminate();
}


void OpenGLApp::initialize(const StringVector& cmdLine) {
    // Initialize the exeng root class and plugins.
    std::string path;

#if defined (EXENG_WINDOWS)
    path = "";
#else
    path = "../exeng-graphics-gl3/";
#endif

    this->root.reset(new exeng::Root());
    this->root->getPluginManager()->load("exeng-graphics-gl3", path);
    
    // initialize the gl3 driver, in windowed mode
    this->driver.reset(this->root->getGraphicsManager()->createDriver());
    this->driver->addEventHandler(this);
    
    DisplayMode mode;
    mode.size = Size2i(640, 480);
    mode.redBits = 8;
    mode.greenBits = 8;
    mode.blueBits = 8;
    mode.alphaBits = 8;
    mode.status = DisplayStatus::Window;
    mode.depthBits = 16;
    mode.stencilBits = 0;
    
    this->driver->initialize(mode);
    
    // create the geometry (a single triangle)
    VertexFormat format;
    // VertexField field(VertexAttrib::Position, 3, DataType::Float32);
    
    format.fields.push_back(VertexField(VertexAttrib::Position, 3, DataType::Float32));
    format.fields.push_back(VertexField(VertexAttrib::TexCoord, 2, DataType::Float32));
    
    auto vertexBuffer = this->driver->createVertexBuffer(format, 4);
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
    this->vertexBuffer.reset(vertexBuffer);
    
    // create a texture for the render targets
    auto texture = this->driver->createTexture(TextureType::Tex2D, Vector3f(640, 480), ColorFormat::R8G8B8A8);
    
    struct Texel {
        std::uint8_t red;
        std::uint8_t green;
        std::uint8_t blue;
        std::uint8_t alpha;
    };
    
    Texel *textureData = reinterpret_cast<Texel*>(texture->lock());
    for (int i=0; i<640*480; ++i) {
        textureData[i].red      = 255;
        textureData[i].green    = 255;
        textureData[i].blue     = 255;
        textureData[i].alpha    = 255;
    }
    texture->unlock();
    
    this->texture.reset(texture);
    
    this->material.reset(new Material());
    this->material->getLayer(0)->setTexture(texture);
    
    // transformations
}


void OpenGLApp::terminate() {
}


double OpenGLApp::getFrameTime() const {
    return 0.0;
}


void OpenGLApp::pollEvents() {
    this->driver->pollEvents();
}


ApplicationStatus OpenGLApp::getStatus() const {
    return this->applicationStatus;
}


void OpenGLApp::update(double seconds) {
}


void OpenGLApp::render() {
    Color clearColor(0.2f, 0.2f, 0.8f, 1.0f);
    this->driver->beginFrame(clearColor, ClearFlags::Color);
    
    this->driver->setMaterial(this->material.get());
    this->driver->setVertexBuffer(this->vertexBuffer.get());
    this->driver->render(Primitive::TriangleStrip, 4);
    
    this->driver->endFrame();
}


int OpenGLApp::getExitCode() const {
    return 0;
}


void OpenGLApp::handleEvent(const EventData &data) {
    this->applicationStatus = ApplicationStatus::Terminated;
}

}
