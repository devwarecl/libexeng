
/**
 * nVidia Matrix Multiplication Example
 */

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
        this->start = ::GetTickCount();
    }

    ~Timer() {
        std::cout << ::GetTickCount() - this->start;
    }

private:
    std::uint32_t start = 0;
};

const char MatrixTestCL1KernelSource[] = 
    "typedef struct { \n"
    "   int width; \n"
    "   int height; \n"
    "   __global float *elements; \n"
    "} Matrix; \n"
    "\n"
    "#define BLOCK_SIZE 16 \n"
    "\n"
    "void MatrixMultiply(Matrix matA, Matrix matB, Matrix matC) { \n"
    "   float valueC = 0.0f; \n"
    "   int row = get_global_id(1); \n"
    "   int col = get_global_id(0); \n"
    "\n"
    "   for (int e=0; e<matA.width; ++e) { \n"
    "       valueC += matA.elements[row*matA.width + e] * matB.elements[e*matB.width + col]; \n"
    "   } \n"
    "\n"
    "   matC.elements[row*matC.width + col] = valueC; \n"
    "} \n"
    "\n"
    "__kernel void MatrixMultiplyKernel( \n"
    "   int widthA, int heightA, __global float* elementsA, \n"
    "   int widthB, int heightB, __global float* elementsB, \n"
    "   int widthC, int heightC, __global float* elementsC) { \n"
    "\n"
    "   Matrix matrixA{widthA, heightA, elementsA}; \n"
    "   Matrix matrixB{widthB, heightB, elementsB}; \n"
    "   Matrix matrixC{widthC, heightC, elementsC}; \n"
    "\n"
    "   MatrixMultiply(matrixA, matrixB, matrixC); \n"
    "} \n"
;

class MatrixTestCL1 {
public:
    struct Matrix {
        int width;
        int height;
        cl::Memory elements;
    };

    void compute(cl::Context &context) {
        cl::Buffer buffer;
    }

private:
    const int BLOCK_SIZE = 16;
};


class PerformanceTest {
public:


public:
    PerformanceTest() {
        std::string src = "";

        src += "typedef struct { float m11, m12, m21, m22; } Matrix2;\n";
        src += "\n";
        src += "#define BLOCK_SIZE " + std::to_string(MATRIX_BLOCK_SIZE);
        src += "\n";
        src += "float determinant(Matrix2 *matrix) {\n";
        src += "    return matrix->m11*matrix->m22 - matrix->m12*matrix->m21;\n";
        src += "}\n";
        src += "\n";
        src += "__kernel void computeDeterminant(int matrixCount, __global float *determinantBuffer, __global Matrix2* matrixBuffer, __local Matrix2 matrixCache[BLOCK_SIZE]) { \n";
        src += "    const int groupIndex = get_group_id(0); \n";
        src += "    const int localIndex = get_local_id(0); \n";
        src += "    const int index = groupIndex*BLOCK_SIZE + localIndex; \n";
        src += "    matrixCache[localIndex] = *(matrixBuffer + index); \n";
        src += "    barrier(CLK_LOCAL_MEM_FENCE); \n";
        src += "    Matrix2 matrix = matrixCache[localIndex]; \n";
        src += "    determinantBuffer[index] = determinant(&matrix); ";
        src += "}\n";

        this->kernelSource = src;
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

        // Create Context
        cl_context_properties properties [] = {
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
            std::cout << msg << std::endl;
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
        std::vector<float> determinants;
        std::vector<exeng::Matrix2f> matrices;

        cl::Buffer determinantBuffer;
        cl::Buffer matrixBuffer;

        {
            Timer time;
            std::cout << "Generating " << MATRIX_COUNT << " matrices ... ";
            matrices = this->generateMatrices(MATRIX_COUNT);

            determinantBuffer = cl::Buffer(this->context, CL_MEM_WRITE_ONLY, sizeof(float)*matrices.size());
            matrixBuffer = cl::Buffer(
                this->context, 
                CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
                sizeof(exeng::Matrix2f)*matrices.size(), 
                const_cast<exeng::Matrix2f*>(matrices.data())
            );

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
            this->determinant_cl(determinantBuffer, matrixBuffer, matrices.size());
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
    void determinant_cl(cl::Buffer determinantBuffer, cl::Buffer matrixBuffer, int count) {

        this->kernel.setArg(0, count);
        this->kernel.setArg(1, determinantBuffer);
        this->kernel.setArg(2, matrixBuffer);
        this->kernel.setArg(3, MATRIX_BLOCK_SIZE*sizeof(exeng::Matrix2f), nullptr);
        
        // Run the kernel
        cl::Event event;
        cl_int errorCode = 0;

        const int groupSize = count/MATRIX_BLOCK_SIZE;
        const int localSize = MATRIX_BLOCK_SIZE;
        errorCode = this->queue.enqueueNDRangeKernel(this->kernel, cl::NullRange, cl::NDRange(groupSize), cl::NDRange(localSize), nullptr, &event);
        event.wait();

        if (errorCode != CL_SUCCESS) {
            throw std::runtime_error("Error durante la ejecucion del kernel.");
        }
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
        /*
        std::cout << "[" << std::endl;

        for (float determinant : determinants) {
            std::cout << determinant << " ";
        }

        std::cout << "]" << std::endl;
        */
    }

private:
    cl::Platform platform;
    cl::Device device;
    cl::Context context;
    cl::Program program;
    cl::Kernel kernel;
    cl::CommandQueue queue;

    std::string kernelSource;

    const int MATRIX_COUNT      = 4096*4096;
    const int MATRIX_BLOCK_SIZE = 16*16*2;
};

int main(int argc, char **arg) {
    /*
    ::PerformanceTest test;

    test.initialize();
    test.testPerformance();
    */

    std::cout << MatrixTestCL1KernelSource << std::endl;

    return 0;
}
