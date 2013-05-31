#include "Application.hpp"
#include <stdexcept>
#include <iostream>

#include <exeng/Exeng.hpp>
#include <memory>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

namespace raytracer {
    int Application::run(const StringVector& cmdLine) {
        
        std::unique_ptr<Application> app;
        
        try {
            app.reset(Application::instance);
            int exitCode = 0;
            double seconds = 0.0;
            
            app->initialize(cmdLine);
            
            while (app->getStatus() != ApplicationStatus::Stopped) {
                seconds = app->getFrameTime();
                
                app->pollEvents();
                app->update(seconds);
                app->render();
            }
            
            app->terminate();
            
            exitCode = app->getExitCode();

            return exitCode;
        } catch(const std::exception &exp) {
            std::cout << "Unhandled exception " << exp.what() << std::endl;
            return -1;
        }
    }


    bool Application::set(Application *app)  {
        if (Application::instance != nullptr) {
            delete Application::instance;
            Application::instance = nullptr;
        }
        
        Application::instance = app;
		
        return true;
    }
    
    Application *Application::instance = nullptr;
}


int main(int argc, char** argv) {
    using namespace raytracer;

    raytracer::StringVector cmdLine;

    // Inicializar la linea de comandos
    cmdLine.reserve(argc);
    cmdLine.resize(argc);

    for(int i=0; i<argc; ++i) {
        cmdLine[i] = std::string(argv[i]);
    }
    
    // Ejecutar la aplicacion
    return raytracer::Application::run(cmdLine);
}


using namespace exeng;
using namespace exeng::math;
using namespace exeng::graphics;

namespace raytracer {
class OpenGLApplication : public raytracer::Application {
public:
    OpenGLApplication() {
        this->root = nullptr;
        this->driver = nullptr;
        this->vbuffer = nullptr;
        this->vertexShader = nullptr;
        this->fragmentShader = nullptr;
        this->program = nullptr;
    }
    
    
    virtual ~OpenGLApplication () {
    }
    
    
    virtual void initialize(const StringVector& cmdLine) {
        
        // Initialize the exeng root class and plugins.
        this->root = new Root();
        this->root->getPluginManager()->load("exeng-graphics-gl3", "../exeng-graphics-gl3/");
        
        // initialize the gl3 driver, in windoed mode
        this->driver = this->root->getGraphicsManager()->createDriver();
        
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
        VertexField field(VertexAttrib::Position, 3, DataType::Float32);
        format.fields.push_back(field);
        
        this->vbuffer = this->driver->createVertexBuffer(format, 3);
        
        {
            VertexArray<Vector3f> array(this->vbuffer);
            
            array[0] = Vector3f(0.0f, 1.0f, 0.0f);
            array[1] = Vector3f(1.0f, 0.0f, 0.0f);
            array[2] = Vector3f(-1.0f, 0.0f, 0.0f);
        }
        
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
    }

    
    virtual void terminate() {
        this->program->removeShader(this->fragmentShader);
        this->program->removeShader(this->vertexShader);
        
        delete this->program;
        delete this->vbuffer;
        delete this->driver;
        delete this->root;
    }
    
    
    virtual double getFrameTime() const {
        return 0.0;
    }
    
    
    virtual void pollEvents() {
        this->driver->pollEvents();
    }
    
    
    virtual ApplicationStatus getStatus() const {
        return ApplicationStatus::Running;
    }
    
    
    virtual void update(double seconds) {
    }
    
    
    virtual void render() {
        Color clearColor(0.2f, 0.2f, 0.8f, 1.0f);
        this->driver->beginFrame(clearColor, ClearFlags::Color);
        this->driver->setShaderProgram(this->program);
        this->driver->setVertexBuffer(this->vbuffer);
        this->driver->render(Primitive::TriangleStrip, 3);
        this->driver->endFrame();
        
    }
    
    virtual int getExitCode() const {
        return 0;
    }
    
    
private:
    Root *root;
    GraphicsDriver *driver;
    VertexBuffer *vbuffer;
    Shader *vertexShader;
    Shader *fragmentShader;
    ShaderProgram *program;    
};
}


namespace {
    using namespace raytracer;
    static const bool b = Application::set( new OpenGLApplication() );
}
