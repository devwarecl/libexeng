
#include "OpenGLApp.hpp"

using namespace exeng;
using namespace exeng::math;
using namespace exeng::graphics;
using namespace exeng::framework;
using namespace exeng::input;

namespace raytracer {

OpenGLApp::OpenGLApp() {
    this->root = nullptr;
    this->driver = nullptr;
    this->triangleVertexBuffer = nullptr;
    this->vertexShader = nullptr;
    this->fragmentShader = nullptr;
    this->program = nullptr;
	this->texture = nullptr;
    this->applicationStatus = ApplicationStatus::Running;
}


OpenGLApp::~OpenGLApp () {
    this->terminate();
}


void OpenGLApp::initialize(const StringVector& cmdLine) {
    
    // Initialize the exeng root class and plugins.
    this->root = new Root();

    std::string path;

#if defined (EXENG_WINDOWS)
    path = "./x64/Debug/";
#else
    path = "../exeng-graphics-gl3/";
#endif

    this->root->getPluginManager()->load("exeng-graphics-gl3", path);
    
    // initialize the gl3 driver, in windowed mode
    this->driver = this->root->getGraphicsManager()->createDriver();
    
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
    VertexBuffer *vertexBuffer = nullptr;
    
    VertexFormat format;
    VertexField field(VertexAttrib::Position, 3, DataType::Float32);
    format.fields.push_back(field);
    
    vertexBuffer = this->driver->createVertexBuffer(format, 3);
    {
        VertexArray<Vector3f> array(vertexBuffer);
        
        array[0] = Vector3f( 0.0f,  0.5f, 0.0f);
        array[1] = Vector3f( 0.5f, -0.5f, 0.0f);
        array[2] = Vector3f(-0.5f, -0.5f, 0.0f);
    }
    this->triangleVertexBuffer = vertexBuffer;
    
    vertexBuffer = this->driver->createVertexBuffer(format, 4);
    {
        VertexArray<Vector3f> array(vertexBuffer);
        
        array[0] = Vector3f(-0.5f,  0.5f, 0.0f);
        array[1] = Vector3f( 0.5f,  0.5f, 0.0f);
        array[2] = Vector3f(-0.5f, -0.5f, 0.0f);
        array[3] = Vector3f( 0.5f, -0.5f, 0.0f);
    }
    
    this->squareVertexBuffer = vertexBuffer;
    
    // create the shaders
    this->vertexShader = this->driver->createShader(ShaderType::Vertex);
    this->vertexShader->setSourceCode(
                "#version 330 \n"
                "layout(location=0) in vec4 position; \n"
                "void main() { \n"
                "    gl_Position = position; \n"
                "}"
    );
    this->vertexShader->compile();
    
    this->fragmentShader = this->driver->createShader(ShaderType::Fragment);
    this->fragmentShader->setSourceCode(
                "#version 330 \n"
                "out vec4 outputColor; \n"
                "void main() { \n"
                "    outputColor = vec4(1.0, 1.0, 1.0, 1.0); \n"
                "}\n"
    );
    this->fragmentShader->compile();
    
    this->program = this->driver->createShaderProgram();
    this->program->addShader(this->vertexShader);
    this->program->addShader(this->fragmentShader);
    this->program->link();
    
    // transformations
}


void OpenGLApp::terminate() {
    this->program->removeShader(this->fragmentShader);
    this->program->removeShader(this->vertexShader);
    
    delete this->program;
    delete this->triangleVertexBuffer;
    delete this->squareVertexBuffer;
    delete this->driver;
    delete this->root;
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
    // this->driver->setShaderProgram(this->program);
    
    this->driver->setVertexBuffer(this->squareVertexBuffer);
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
