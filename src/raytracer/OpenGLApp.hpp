
#ifndef __RAYTRACER_OPENGLAPP_HPP__
#define __RAYTRACER_OPENGLAPP_HPP__

#include <stdexcept>
#include <iostream>

#include <exeng/Exeng.hpp>
#include <boost/scoped_ptr.hpp>

namespace raytracer {
class OpenGLApp : public exeng::framework::Application, public exeng::input::IEventHandler {
public:
    OpenGLApp();
    
    virtual ~OpenGLApp ();
    
    virtual void initialize(const exeng::framework::StringVector& cmdLine);
    
    virtual void terminate();
    
    virtual double getFrameTime() const;
    
    virtual void pollEvents();
    
    virtual exeng::framework::ApplicationStatus getStatus() const;
    
    virtual void update(double seconds);
    
    virtual void render();
    
    virtual int getExitCode() const;
    
    virtual void handleEvent(const exeng::input::EventData &data);
    
private:
    boost::scoped_ptr<exeng::Root> root;
    boost::scoped_ptr<exeng::graphics::Material> material;
    boost::scoped_ptr<exeng::graphics::GraphicsDriver> driver;
    boost::scoped_ptr<exeng::graphics::VertexBuffer> vertexBuffer;
    boost::scoped_ptr<exeng::graphics::Texture> texture;
    exeng::framework::ApplicationStatus applicationStatus;
};
}

#endif  //__RAYTRACER_APPLICATION_HPP__
