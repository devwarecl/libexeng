
#include <iostream>
#include <vector>
#include <random>
#include <cstdint>
#include <exeng/Matrix.hpp>
#include <CL/cl.hpp>
#include <Windows.h>

class Timer {
public:
    Timer() {
        // this->start = exeng::Timer::getTime();
        this->start = ::GetTickCount();
    }

    ~Timer() {
        std::cout << ::GetTickCount() - this->start;
    }

private:
    std::uint32_t start = 0;
};

class PerformanceTest {
public:
    PerformanceTest() {
        const std::string kernelSource = 
            "typedef struct { float m11, m12, m21, m22; } Matrix2;\n"
            "\n"
            "float determinant(const Matrix2 &matrix) {\n"
            "    return matrix.m11*matrix.m22 - matrix.m12*matrix.m21;\n"
            "};\n"
            "\n"
            "kernel void computeDeterminant(global float *determinantBuffer, read_only global Matrix2* matrixBuffer) { \n"
            "    const int index = get_global_id(0); \n"
            "    determinantBuffer[index] = determinant(matrixBuffer[index]); ";
            "}\n";
    }

    void initialize() {
        cl_int errorCode = 0;

        // Obtener la primera plataforma OpenCL (implementacion de OpenCL)
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        cl::Platform platform = platforms[0];
        
        // Obtener el primer dispositivo de OpenCL de tipo GPU
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

        std::vector<cl::Device> selectedDevices = {device};
            
        cl::Context context = cl::Context(selectedDevices, &properties[0], nullptr, nullptr, nullptr);

        // Compilar el programa
        cl::Program::Sources sources = {{kernelSource.c_str(), kernelSource.size() + 1}};
        cl::Program program(context, sources, &errorCode);
        errorCode = program.build({device}, nullptr, nullptr, nullptr);
        if (errorCode != CL_SUCCESS) {
            std::string msg = std::string("Error al compilar el programa OpenCL.") + program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) + ".";
            throw std::runtime_error(msg.c_str());
        }

        // Crear el kernel a partir del programa (el kernel es una instancia del programa para un cierto device).
        cl::Kernel kernel(program, "computeDeterminant", &errorCode);
        if (errorCode != CL_SUCCESS) {
            throw std::runtime_error("Error al crear un kernel para OpenCL.");
        }

        // Crear la cola de comandos, que permitira 
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
    }

    void testPerformance() {
        const int MATRIX_COUNT = 100000;

        std::vector<float> determinants;
        std::vector<exeng::Matrix2f> matrices;

        {
            Timer time;
            std::cout << "Generating " << MATRIX_COUNT << " matrices ... ";
            matrices = this->generateMatrices(MATRIX_COUNT);
        }
        std::cout << "[ms]" << std::endl;

        {
            Timer time;
            std::cout << "Consolidating those matrices (C++) ...";
            determinants = this->determinant_cpp(matrices);
        }
        std::cout << "[ms]" << std::endl;
        std::cout << "The final matrix is:" << std::endl;
        this->display(determinants);

        {
            Timer time;
            std::cout << "Consolidating those matrices (CL) ...";
            determinants = this->determinant_cl(matrices);
        }
        std::cout << "[ms]" << std::endl;
        std::cout << "The final matrix is:" << std::endl;
        this->display(determinants);
    }

private:            
    /**
     * @brief Generates a sequence of matrices
     */
    std::vector<exeng::Matrix2f> generateMatrices(const int matrixCount) {
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
        
        std::mt19937 generator;
        generator.seed(10);

        std::vector<exeng::Matrix2f> result;

        for (int i=0; i<matrixCount; ++i) {
            exeng::Matrix2f matrix;

            for (int i=0; i<4; ++i) {
                matrix[i] = dist(generator);
            }
            
            result.push_back(matrix);
        }

        return result;
    }

    /**
     * @brief Consolidate a matrix sequence in just one.
     */
    std::vector<float> determinant_cl(const std::vector<exeng::Matrix2f> &matrices) {

        cl::Buffer determinantBuffer = cl::Buffer(this->context, CL_MEM_WRITE_ONLY, sizeof(float)*matrices.size());
        cl::Buffer matrixBuffer = cl::Buffer(
            this->context, 
            CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
            sizeof(exeng::Matrix2f)*matrices.size(), 
            const_cast<exeng::Matrix2f*>(matrices.data())
        );

        this->kernel.setArg(0, determinantBuffer);
        this->kernel.setArg(1, matrixBuffer);
        
        // Run the kernel
        cl::Event event;
        cl_int errorCode = 0;

        errorCode = this->queue.enqueueNDRangeKernel(this->kernel, cl::NullRange, cl::NDRange(matrices.size()), cl::NullRange, nullptr, &event);
        event.wait();
        if (errorCode != CL_SUCCESS) {
            throw std::runtime_error("Error durante la ejecucion del kernel.");
        }

        // Get the result back
        std::vector<float> determinants;
        determinants.resize(matrices.size());

        errorCode = this->queue.enqueueReadBuffer(
            determinantBuffer, 
            CL_TRUE, 0, 
            sizeof(float)*determinants.size(), 
            determinants.data()
        );

        event.wait();
        if (errorCode != CL_SUCCESS) {
            throw std::runtime_error("Error durante la ejecucion del kernel.");
        }
        
        // Wait for queue completion
        errorCode = this->queue.finish();
        if (errorCode != CL_SUCCESS) {
            throw std::runtime_error("Error durante la ejecucion del kernel.");
        }

        return determinants;
    }

    /**
     * @brief Consolidate a matrix sequence in just one.
     */
    std::vector<float> determinant_cpp(const std::vector<exeng::Matrix2f> &matrices) {
        std::vector<float> result;

        for (const exeng::Matrix2f &matrix : matrices) {
            result.push_back(exeng::abs(matrix));
        }

        return result;
    }
    
    /**
     * @brief Display a matrix in screen
     */
    void display(const std::vector<float> &determinants) {
        std::cout << "[" << std::endl;

        for (float determinant : determinants) {
            std::cout << determinant << " " << std::endl;
        }

        std::cout << "]" << std::endl;
    }

private:
    cl::Platform platform;
    cl::Device device;
    cl::Context context;
    cl::Program program;
    cl::Kernel kernel;
    cl::CommandQueue queue;

    std::string kernelSource;
};

int main(int argc, char **arg) {
    ::PerformanceTest test;

    test.initialize();
    test.testPerformance();

    return 0;
}
