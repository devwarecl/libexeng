
// #define __CL_ENABLE_EXCEPTIONS

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>
#include <CL/cl_gl.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <exeng/Config.hpp>
#include <exeng/Vector.hpp>
#include <exeng/Matrix.hpp>

#undef CL_VERSION_1_2
#include <CL/cl.hpp>

#if defined(EXENG_UNIX)
#  include <GL/glx.h>
#endif

using namespace exeng;

namespace gl {
    void check() {
        GLenum errorCode = ::glGetError();                                          
        if (errorCode != GL_NO_ERROR) {
            // GLchar errorStr[1024] = {0};
            throw std::runtime_error("Error en el codigo OpenGL");
        }
    }
}

namespace util {
    std::string getMediaPath() {
        return std::string(SANDBOX_ROOT_FOLDER);
    }

    std::string loadFile(const std::string &filename) {
        std::ifstream fs;
        fs.open(filename.c_str(), std::ios_base::in);

        if (!fs.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo '" + filename + "'.");
        }

        std::string content;
        std::string line;

        while (!fs.eof()) {
            std::getline(fs, line);
            content += line + "\n";
        }

        return content;
    }
}

namespace simple {
    class GraphicsApplication {
    public:
        GraphicsApplication() {
        }

        ~GraphicsApplication() {
            this->terminate();
        }

        virtual void initialize() {
            ::glfwInit();

            ::glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
            ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            ::glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);

            this->window = ::glfwCreateWindow(640, 480, "Open CL/GL Interop", nullptr, nullptr);
            ::glfwMakeContextCurrent(window);

            ::ogl_LoadFunctions();

            gl::check();
        }

        virtual void terminate() {
            this->window = nullptr;
            ::glfwTerminate();
        }

        bool pollEvents() {
            ::glfwPollEvents();
            if (::glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                return false;
            }

            return true;
        }

        virtual void update(GLdouble seconds) {}
        virtual void render() {}

        int getExitCode() {
            return 0;
        }

    public:
        static int run(GraphicsApplication &app) {
            GLdouble lastTime = ::glfwGetTime();

            app.initialize();
            while (app.pollEvents()) {
                GLdouble seconds = 0.0;
                seconds = ::glfwGetTime() - lastTime;
                lastTime = ::glfwGetTime();
                app.update(seconds);
                app.render();
            }
            app.terminate();

            return app.getExitCode();
        }

    protected:
        GLFWwindow *getWindow() const {
            return this->window;
        }

        GLuint compileShader(const std::string &source, GLenum type) {
            const char *sourcePtr = source.c_str();

            GLuint shaderId = ::glCreateShader(type);
            glShaderSource(shaderId, 1, &sourcePtr, NULL);
            glCompileShader(shaderId);

            // Check Vertex Shader
            GLint result, infoLogLength;
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (result == GL_FALSE) {
                std::string errorMsg;
                errorMsg.reserve(infoLogLength + 1);
                glGetShaderInfoLog(shaderId, infoLogLength, NULL, &errorMsg[0]);
                std::cout << errorMsg << std::endl;

                throw std::runtime_error("Error al compilar el codigo: " + errorMsg);
            }

            gl::check();

            return shaderId;
        }

        GLuint linkProgram(const std::vector<GLuint> &shaderIds) {
            GLuint programId = ::glCreateProgram();
            for (GLuint shaderId : shaderIds) {
                glAttachShader(programId, shaderId);
            }
            glLinkProgram(programId);

            gl::check();

            return programId;
        }

    private:
        GLFWwindow *window = nullptr;
    };

    class ImageProcessor {
    public:
        ImageProcessor() {}

        ImageProcessor(GLuint bufferId, GLsizei bufferSize, int width, int height) {
            this->initialize(bufferId, bufferSize, width, height);
        }

        void initialize(GLuint bufferId, GLsizei bufferSize, int width, int height) {
            cl_int errorCode = 0;

            // Obtener la primera plataforma OpenCL (implementacion de OpenCL)
            // ::clGetPlatformIDs(1, &platformId, nullptr);
            std::vector<cl::Platform> platforms;
            cl::Platform::get(&platforms);
            cl::Platform platform = platforms[0];
            
            // Obtener el primer dispositivo de OpenCL de tipo GPU
            // cl_device_id deviceId;
            // ::clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 1, &deviceId, nullptr);
            std::vector<cl::Device> devices;
            cl::Device device;
            platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
            device = devices[0];

            // Crear un contexto en el dispostivo. El contexto es una coleccion de recursos (que veremos posteriormente).
            cl_context_properties properties [] = {
#if defined (WIN32)
                // We should first check for cl_khr_gl_sharing extension.
                CL_GL_CONTEXT_KHR , (cl_context_properties) ::wglGetCurrentContext() ,
                CL_WGL_HDC_KHR , (cl_context_properties) ::wglGetCurrentDC() ,
#elif defined (__linux__)
                // We should first check for cl_khr_gl_sharing extension.
                CL_GL_CONTEXT_KHR , (cl_context_properties) ::glXGetCurrentContext() ,
                CL_GLX_DISPLAY_KHR , (cl_context_properties) ::glXGetCurrentDisplay() ,
#elif defined (__APPLE__)
                CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE , (cl_context_properties) CGLGetShareGroup( CGLGetCurrentContext() ) ,
#endif
                CL_CONTEXT_PLATFORM,    (cl_context_properties) platform(),
                0, 0
            };

            // cl_context context = ::clCreateContext(properties, 1, &deviceId, nullptr, nullptr, &errorCode);
            std::vector<cl::Device> selectedDevices = {device};
            
            cl::Context context = cl::Context(selectedDevices, &properties[0], nullptr, nullptr, nullptr);

            // Compilar el programa
            std::string kernelSource = util::loadFile(util::getMediaPath() + "VertexDisplacer.cl");
            // const size_t kernelSourceSize = kernelSource.size() + 1;
            // const char* kernelSourcePtr = kernelSource.c_str();
            // cl_program program = ::clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSourceSize, &errorCode);
            // errorCode = ::clBuildProgram(program, 1, &deviceId, nullptr, nullptr, nullptr);
            cl::Program::Sources sources = {{kernelSource.c_str(), kernelSource.size() + 1}};

            cl::Program program(context, sources, &errorCode);
            errorCode = program.build({device}, nullptr, nullptr, nullptr);
            if (errorCode != CL_SUCCESS) {
                std::string msg = std::string("Error al compilar el programa OpenCL.") + program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) + ".";
                throw std::runtime_error(msg.c_str());
            }

            // Crear el kernel a partir del programa (el kernel es una instancia del programa para un cierto device).
            // cl_kernel kernel = ::clCreateKernel(program, "VertexDisplacer", &errorCode);
            cl::Kernel kernel(program, "VertexDisplacer", &errorCode);
            if (errorCode != CL_SUCCESS) {
                throw std::runtime_error("Error al crear un kernel para OpenCL.");
            }

            // Crear la cola de comandos, que permitira 
            // cl_command_queue queue = ::clCreateCommandQueue(context, deviceId, 0, &errorCode);
            cl::CommandQueue queue(context, device, 0, &errorCode);
            if (errorCode != CL_SUCCESS) {
                throw std::runtime_error("Error al crear el command queue de OpenCL.");
            }

            this->platform = platform;
            this->device = device;
            this->context = context;
            
            this->program = program;
            this->kernel = kernel;
            this->queue = queue;
            this->bufferSize = bufferSize;
            this->width = width;
            this->height = height;
        }

        void setRenderTexture(GLuint textureId) {
            cl_int errorCode = 0;

            cl::Image2DGL image = cl::Image2DGL(this->context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, textureId, &errorCode);
            // Crear un buffer de datos y copiarlo a un buffer instanciado en la memoria de video.
            // cl_mem buffer = ::clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, bufferId, &errorCode);
            // cl::BufferGL buffer(context, CL_MEM_READ_WRITE, bufferId, &errorCode);
            if (errorCode != CL_SUCCESS) {
                throw std::runtime_error("No se pudo crear el buffer CL a partir del buffer GL.");
            }

            this->bufferId = textureId;
            this->image = image;
        }

        void process() {
            cl::Event event;
            cl_int errorCode = 0;

            // Especificar los datos de entrada
            const float displace = 0.01f;
            // ::clSetKernelArg(kernel, 0, sizeof(cl_mem), &this->buffer);
            // ::clSetKernelArg(kernel, 1, sizeof(float), &displace);
            this->kernel.setArg(0, this->image);
            this->kernel.setArg(1, displace);

            // Bloquear el buffer GL
            // clEnqueueAcquireGLObjects(this->queue, 1, &this->buffer, 0, nullptr, nullptr);
            std::vector<cl::Memory> buffers = { cl::Memory(this->image) };
            errorCode = this->queue.enqueueAcquireGLObjects(&buffers, nullptr, &event);
            event.wait();
            if (errorCode != CL_SUCCESS) {
                throw std::runtime_error("Error durante la ejecucion del kernel.");
            }

            // Especificar el rango en el que vamos a ejecutar el kernel.
            // const size_t globalWorkSize[] = {bufferSize, 0, 0};
            // errorCode = ::clEnqueueNDRangeKernel(queue, this->kernel, 1, nullptr, globalWorkSize, nullptr, 0, nullptr, nullptr);
            errorCode = this->queue.enqueueNDRangeKernel(this->kernel, cl::NullRange, cl::NDRange(width, height), cl::NullRange, nullptr, &event);
            event.wait();
            if (errorCode != CL_SUCCESS) {
                throw std::runtime_error("Error durante la ejecucion del kernel.");
            }

            // Desbloquear el buffer GL
            // ::clEnqueueReleaseGLObjects(this->queue, 1, &this->buffer, 0, nullptr, nullptr);
            errorCode = this->queue.enqueueReleaseGLObjects(&buffers, nullptr, &event);
            event.wait();
            if (errorCode != CL_SUCCESS) {
                throw std::runtime_error("Error durante la ejecucion del kernel.");
            }

            // Esperar que se completen todas las operaciones de OpenCL
            // ::clFinish(this->queue);
            errorCode = this->queue.finish();
            if (errorCode != CL_SUCCESS) {
                throw std::runtime_error("Error durante la ejecucion del kernel.");
            }
        }

        ~ImageProcessor() {}

    private:
        cl::Platform platform;
        cl::Device device;
        cl::Context context;
        cl::Image2DGL image;
        cl::Program program;
        cl::Kernel kernel;
        cl::CommandQueue queue;

        int width = 0, height = 0;

        GLuint bufferId = 0;
        GLsizei bufferSize = 0;
    };

    class SimpleApplication : public GraphicsApplication {
    public:
        SimpleApplication() {
        }

        ~SimpleApplication () {
            this->terminate();
        }

        virtual void initialize() {
            GraphicsApplication::initialize();

            // Conf. varias
            ::glEnable(GL_DEPTH_TEST);
            ::glFrontFace(GL_CCW);

            // Buffer de vertices
            ::glGenVertexArrays(1, &this->vao);
            ::glBindVertexArray(vao);

            this->vertexData = {
                // Cara trasera
                -0.5f,   0.5f, -0.5f,   0.0f, 0.0f, -1.0f,      0.0f, 1.0f,  // Izquierda,  Arriba,  Atras
                 0.5f,   0.5f, -0.5f,   0.0f, 0.0f, -1.0f,      1.0f, 1.0f,  // Derecha,    Arriba,  Atras
                -0.5f,  -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,      0.0f, 0.0f,  // Izquierda,  Abajo,   Atras
                 0.5f,  -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,      1.0f, 0.0f,  // Derecha,    Abajo,   Atras

                // Cara derecha
                 0.5f,   0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // Derecha,     Arriba, Atras
                 0.5f,   0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Derecha,     Arriba, Adelante
                 0.5f,  -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Derecha,     Abajo,  Atras
                 0.5f,  -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // Derecha,     Abajo,  Adelante 

                // Cara delantera
                 0.5f,   0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  // Derecha,     Arriba, Adelante
                -0.5f,   0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // Izquierda,   Arriba, Adelante
                 0.5f,  -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,  // Derecha,     Abajo,  Adelante
                -0.5f,  -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Izquierda,   Abajo,  Adelante

                // Cara Izquierda
                -0.5f,   0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Izquierda,   Arriba, Adelante
                -0.5f,   0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // Izquierda,   Arriba, Atras
                -0.5f,  -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // Izquierda,   Abajo,  Adelante 
                -0.5f,  -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Izquierda,   Abajo,  Atras

                // Cara de Arriba
                -0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Izquierda,   Arriba, Adelante
                 0.5f,   0.5f,   0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Derecha,     Arriba, Adelante
                -0.5f,   0.5f,  -0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Izquierda,   Arriba, Atras
                 0.5f,   0.5f,  -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Derecha,     Arriba, Atras

                 // Cara Inferior
                 0.5f,  -0.5f,   0.5f,  0.0f, -1.0f, 0.0f,   1.0f, 1.0f, // Derecha,     Abajo, Adelante
                -0.5f,  -0.5f,   0.5f,  0.0f, -1.0f, 0.0f,   0.0f, 1.0f, // Izquierda,   Abajo, Adelante
                 0.5f,  -0.5f,  -0.5f,  0.0f, -1.0f, 0.0f,   1.0f, 0.0f, // Derecha,     Abajo, Atras
                -0.5f,  -0.5f,  -0.5f,  0.0f, -1.0f, 0.0f,   0.0f, 0.0f  // Izquierda,   Abajo, Atras
            };

            this->indexData = {
                0 + 0,  0 + 1,  0 + 2,  0 + 1,  0 + 3,  0 + 2, 
                4 + 0,  4 + 1,  4 + 2,  4 + 1,  4 + 3,  4 + 2, 
                8 + 0,  8 + 1,  8 + 2,  8 + 1,  8 + 3,  8 + 2, 
                12 + 0, 12 + 1, 12 + 2, 12 + 1, 12 + 3, 12 + 2, 
                16 + 0, 16 + 1, 16 + 2, 16 + 1, 16 + 3, 16 + 2, 
                20 + 0, 20 + 1, 20 + 2, 20 + 1, 20 + 3, 20 + 2
            };

            ::glGenBuffers(1, &this->vertexBuffer);
            ::glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
            ::glBufferData(GL_ARRAY_BUFFER, sizeof(float)*this->vertexData.size(), this->vertexData.data(), GL_STATIC_DRAW);

            ::glGenBuffers(1, &this->indexBuffer);
            ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
            ::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * this->indexData.size(), this->indexData.data(), GL_STATIC_DRAW);

            gl::check();

            this->programId = this->loadProgram();
            this->processor.initialize(this->textureId, 256*256*4, 256, 256);

            // Crear una textura en blanco
            ::glGenTextures(1, &this->textureId);
            ::glBindTexture(GL_TEXTURE_2D, this->textureId);
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_FLOAT, nullptr);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            this->processor.setRenderTexture(this->textureId);
        }

        virtual void terminate() {
            GraphicsApplication::terminate();
        }

        virtual void update(GLdouble seconds) {
            float speed = 2.0f * static_cast<float>(seconds);

            if (::glfwGetKey(this->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
                this->objPos += Vector3f(1.0f, 0.0f, 0.0f) * speed;
            }

            if (::glfwGetKey(this->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
                this->objPos -= Vector3f(1.0f, 0.0f, 0.0f) * speed;
            }

            if (::glfwGetKey(this->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
                this->objPos += Vector3f(0.0f, 0.0f, 1.0f) * speed;
            }

            if (::glfwGetKey(this->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
                this->objPos -= Vector3f(0.0f, 0.0f, 1.0f) * speed;
            }
        }

        virtual void render() {
            Matrix4f projMatrix = perspective<float>(60.0f, 640.0f/480.0f, 0.1f, 100.0f);
            Matrix4f modelMatrix = translate<float>(this->objPos);
            
            this->processor.process();

            ::glClearColor(0.1f, 0.2f, 0.8f, 1.0f);
            ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ::glUseProgram(this->programId);
            
            int currentTextureLocation = ::glGetUniformLocation(this->programId, "currentTexture");
            ::glActiveTexture(GL_TEXTURE0);
            ::glBindTexture(GL_TEXTURE_2D, this->textureId);
            ::glUniform1i(currentTextureLocation, 0);   // Usa la textura activa en la unidad de textura '0'.

            ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
            ::glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

            int projMatrixLocation = ::glGetUniformLocation(this->programId, "projMatrix");
            int modelMatrixLocation = ::glGetUniformLocation(this->programId, "modelMatrix");

            ::glUniformMatrix4fv(projMatrixLocation, 1, GL_TRUE, projMatrix.getPtr());
            ::glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, modelMatrix.getPtr());

            int vertexCoordLocation = ::glGetAttribLocation(this->programId, "vertexCoord");    gl::check();
            // int vertexNormalLocation = ::glGetAttribLocation(this->programId, "vertexNormal");  gl::check();
            int vertexTexCoordLocation = ::glGetAttribLocation(this->programId, "vertexTexCoord");  gl::check();

            ::glEnableVertexAttribArray(vertexCoordLocation);
            // ::glEnableVertexAttribArray(vertexNormalLocation);
            ::glEnableVertexAttribArray(vertexTexCoordLocation);

            ::glVertexAttribPointer(vertexCoordLocation,    3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
            // ::glVertexAttribPointer(vertexNormalLocation,   3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
            ::glVertexAttribPointer(vertexTexCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
            ::glDrawElements(GL_TRIANGLES, this->indexData.size(), GL_UNSIGNED_INT, (void*)0);

            ::glDisableVertexAttribArray(vertexCoordLocation);
            // ::glDisableVertexAttribArray(vertexNormalLocation);
            ::glDisableVertexAttribArray(vertexTexCoordLocation);

            ::glFinish();

            ::glfwSwapBuffers(this->getWindow());
        }

    private:
        GLuint loadProgram() {
            std::vector<GLuint> shaderIds = {
                this->compileShader(util::loadFile(util::getMediaPath() + "VertexShader.glsl"), GL_VERTEX_SHADER),
                this->compileShader(util::loadFile(util::getMediaPath() + "FragmentShader.glsl"), GL_FRAGMENT_SHADER)
            };

            return linkProgram(shaderIds);
        }

    private:
        std::vector<float> vertexData /*= {0}*/;
        std::vector<int> indexData /*= {0}*/;
        GLuint vao = 0;
        GLuint vertexBuffer = 0;
        GLuint indexBuffer = 0;
        GLuint programId = 0;
        GLuint textureId = 0;

        Vector3f objPos = {0.0f, 0.0f, 0.0f};

        ImageProcessor processor;
    };
}

/*
float lerp(float a, float b, float t) {
	return a*(1.0 - t) + b*t;
}

float clerp(float a, float b, float t) {
	t = t * 3.1415926535;
	t = (1.0 - ::cos(t)) * 0.5;

	return lerp(a, b, t);
}

float slerp(float a, float b, float c, float d, float t) {
	float p = (d - c) - (b - a);
	float q = (b - a) - p;
	float r = c - a;
	float s = b;
	float t_2 = t*t;
	float t_3 = t_2*t;

	return p*t_3 + q*t_2 + r*t + s;
}

float noise2d (int x, int y) {
	int n  = x *+ y * 57;
	n = (n << 13) ^ n;

	return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);    
}

float snoise2d(int x, int y) {
	float corners = (noise2d(x - 1, y - 1)	+ noise2d(x + 1, y - 1) + noise2d(x - 1, y + 1) + noise2d(x + 1, y + 1)) / 16.0;
	float sides	=	(noise2d(x - 1, y	 )	+ noise2d(x + 1, y	  ) + noise2d(x	   , y - 1) + noise2d(x    , y + 1)) / 8.0;
	float center =	noise2d(x, y) / 4.0;

	return corners + sides + center;
}

float lerp_noise2d(float x, float y) {
	int intX = (int)x;
	int intY = (int)y;

	float tX = x - intX;
	float tY = y - intY;

	float v1 = snoise2d(intX + 0, intY + 0);
	float v2 = snoise2d(intX + 1, intY + 0);
	float v3 = snoise2d(intX + 0, intY + 1);
	float v4 = snoise2d(intX + 1, intY + 1);

	float a = lerp(v1, v2, tX);
	float b = lerp(v3, v4, tX);

	return lerp(a, b, tY);
}

float pown(float base, int exp) {
    return pow(base, exp);
}

float perlin_noise2d(float x, float y) {
	float total = 0.0;

	int n = 4;      //octaves
	float p = 0.25; //persistence

	int freq = 0;
	int amp = 0;

	for (int i=0; i<n; ++i) {
		freq = pown(2.0, i);
		amp = pow(p, i);

		total += lerp_noise2d(x * freq, y * freq) * amp;
	}

	return total;
}
*/

int main(int argc, char **argv) {
    // std::cout <<  (perlin_noise2d(0.0f, 0.1f) + 1.0f) * 0.5f << std::endl;
    // return 0;

    using simple::SimpleApplication;
    
    SimpleApplication app;
    return SimpleApplication::run(app);
}
