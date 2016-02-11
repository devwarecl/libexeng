
#include <memory>

#include <xe/fw/Application.hpp>
#include <xe/sys/Plugin.hpp>
#include <xe/sys/PluginManager.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/Vertex.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/TextureManager.hpp>
#include <xe/cm/ComputeManager.hpp>
#include <xe/cm/ComputeModule.hpp>
#include <xe.main/Main.hpp>

namespace demo {
	class DemoApplication : public xe::fw::Application {
	public:
		DemoApplication() {
			// display all available graphics drivers
			auto driverInfos = this->getGraphicsManager()->getAvailableDrivers();

			if (driverInfos.size() > 0) {
				std::cout << "Available graphic drivers:" << std::endl;
				for (const auto &driverInfo : driverInfos) {
					std::cout << driverInfo.name << std::endl;
				}

			} else {
				std::cout << "No available graphics drivers!" << std::endl;
				throw std::runtime_error("");
			}

			// select the first graphics driver
			auto graphicsDriver = this->getGraphicsManager()->createDriver(driverInfos[0]);

			this->graphicsDriver = std::move(graphicsDriver);
		}

		void initGeometry() {
			xe::gfx::Image *image = this->getGraphicsManager()->getImageToolkit()->getImage("assets/test.png");
			xe::gfx::Texture *texture = this->getTextureManager()->create("assets/test.png", image);
			xe::gfx::Material *material = nullptr;
			
			xe::gfx::StandardVertex v1, v2, v3, v4;

			v1.coord = {-1.0f, 1.0f, 0.0f};	v1.normal = { 0.0f, 0.0f, 0.0f}; v1.texCoord = {0.0f, 1.0f};
			v2.coord = { 1.0f, 1.0f, 0.0f};	v2.normal = { 0.0f, 0.0f, 0.0f}; v2.texCoord = {1.0f, 1.0f};
			v3.coord = {-1.0f, 0.0f, 0.0f};	v3.normal = { 0.0f, 0.0f, 0.0f}; v3.texCoord = {0.0f, 0.0f};
			v4.coord = { 1.0f, 0.0f, 0.0f};	v4.normal = { 0.0f, 0.0f, 0.0f}; v4.texCoord = {0.0f, 0.0f};

			std::vector<xe::gfx::StandardVertex> vertices = {v1, v2, v3, v4};

			auto vbuffer = this->graphicsDriver->createVertexBuffer(vertices);

			auto meshSubset = this->graphicsDriver->createMeshSubset(std::move(vbuffer), xe::gfx::StandardVertex::getFormat());
			auto mesh = std::make_unique<xe::gfx::Mesh>(std::move(meshSubset));
		}

        virtual int run(int argc, char **argv) override {
			// initialize the graphics driver with default settings
			this->graphicsDriver->initialize();

			auto keyboardStatus = this->graphicsDriver->getInputManager()->getKeyboard()->getStatus();

			while (!done) {
				this->graphicsDriver->getInputManager()->poll();
			
				done = keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyEsc);

				this->graphicsDriver->beginFrame({0.2f, 0.2f, 0.8f, 1.0f}, xe::gfx::ClearFlags::ColorDepth);

				this->graphicsDriver->endFrame();
			}

			this->graphicsDriver->terminate();

			return 0;
		}

	private:
		xe::gfx::GraphicsDriverPtr graphicsDriver;

		bool done = false;
	};
}

std::string program_src = R"(
    __kernel void add(__global __write_only int* out, __global __read_only int* in1, __global __read_only int* in2) {
        const int i = get_global_id(0);
        out[i] = in1[i] + in2[i];
    }
)";

class ComputeApplication : public xe::fw::Application {
public:
    
    ComputeApplication() {
        compute = this->getComputeManager()->createComputeModule();
    }
    
    xe::cm::Device* findDevice() const {
        xe::cm::Device *device = nullptr;
    
        // find device
        auto platforms = compute->enumeratePlatforms();

        std::cout << "Found " << platforms.size() << " platform(s)." << std::endl;
        
        for (xe::cm::Platform *platform : platforms) {
            auto devices = platform->enumerateDevices();
            
            std::cout << "Found " << devices.size() << " device(s)." << std::endl;
            
            for (xe::cm::Device *device_ : devices) {
                auto info = device_->getInfo();
                
                std::cout << "    " << info.getName() << ", " << info.getVendor() << std::endl;
                
                if (!device) {
                    device = device_;
                }
            }
        }
        
        return device;
    }
    
    virtual int run(int argc, char **argv) override {
        xe::cm::Device *device = findDevice();
        
        // prepare host objects
        context = device->createContext();
        queue = context->createQueue();
        program = context->createProgram(program_src);
        kernel_add = context->createKernel(program.get(), "add");
        
        // prepare test data
        const int SIZE = 10;
        const int ARRAY_SIZE = SIZE * sizeof(int);
        
        int out_array[SIZE] = {};
        int in1_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int in2_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        
        xe::BufferPtr out = context->createBuffer(queue.get(), ARRAY_SIZE, nullptr);
        xe::BufferPtr in1 = context->createBuffer(queue.get(), ARRAY_SIZE, in1_array);
        xe::BufferPtr in2 = context->createBuffer(queue.get(), ARRAY_SIZE, in2_array);
        
        // prepare execution of the kernel
        kernel_add->setArg(0, out.get());
        kernel_add->setArg(1, in1.get());
        kernel_add->setArg(2, in2.get());
        
        // execute kernel
        queue->enqueueKernel(kernel_add.get(), SIZE);
        
        // read back the results
        queue->enqueueReadBuffer(out.get(), 0, ARRAY_SIZE, out_array);
        
        // show them in console
        for (int value : out_array) {
            std::cout << value << " ";
        }
        
        std::cout << std::endl;
        
        return 0;
    }
    
private:
    xe::cm::ComputeModulePtr compute;
    xe::cm::ContextPtr context;
    xe::cm::QueuePtr queue;
    xe::cm::ProgramPtr program;
    xe::cm::KernelPtr kernel_add;
};

namespace xe { namespace main {
	int main(int argc, char** argv) {
		return xe::fw::Application::execute<demo::DemoApplication>(argc, argv);
	}
}}
