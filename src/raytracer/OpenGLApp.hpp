
#ifndef __RAYTRACER_OPENGLAPP_HPP__
#define __RAYTRACER_OPENGLAPP_HPP__

#include <stdexcept>
#include <iostream>

#include <exeng/Exeng.hpp>
#include <memory>

namespace raytracer {
class OpenGLApp : public exeng::framework::Application {
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
    
    
private:
    exeng::Root *root;
    exeng::graphics::GraphicsDriver *driver;
    exeng::graphics::VertexBuffer *triangleVertexBuffer;
    exeng::graphics::VertexBuffer *squareVertexBuffer;
    exeng::graphics::Shader *vertexShader;
    exeng::graphics::Shader *fragmentShader;
    exeng::graphics::ShaderProgram *program;
	exeng::graphics::Texture *texture;
    exeng::math::Matrix4f triangleTransform;
};
}

#endif  //__RAYTRACER_APPLICATION_HPP__
