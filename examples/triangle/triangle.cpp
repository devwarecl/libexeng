
#include <xe/fw/Application.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/Vertex.hpp>

class TriangleApplication : public xe::fw::Application {
public:
    
    xe::gfx::GraphicsDriverPtr createGraphicsDriver() {
        // display all available graphics drivers
        auto driverInfos = this->getGraphicsManager()->getAvailableDrivers();

        if (driverInfos.size() == 0) {
            std::cout << "No available graphics drivers!" << std::endl;
            throw std::runtime_error("");
        }
        
        // select the first graphics driver
        std::cout << "Available graphic drivers:" << std::endl;
        for (const auto &driverInfo : driverInfos) {
            std::cout << driverInfo.name << std::endl;
        }

        return this->getGraphicsManager()->createDriver(driverInfos[0]);
    }
    
    xe::gfx::MaterialFormat createMaterialFormat() {
        std::vector<xe::gfx::MaterialAttrib> attribs = {
            {"ambient"},
            {"diffuse"},
            {"specular"},
            {"emission"},
            {"shininess", xe::DataType::Float32, 1}
        };
        
        return xe::gfx::MaterialFormat(attribs);
    }
    
    xe::gfx::VertexFormat createVertexFormat() {
        return xe::gfx::StandardVertex::getFormat();
    }
    
    xe::gfx::MaterialPtr createMaterial() {
        auto material = std::make_unique<xe::gfx::Material>(&materialFormat);
        
        material
        
        return material;
    }
    
    xe::gfx::ShaderProgramPtr createProgram() {
        
        
    }
    
    xe::gfx::MeshSubset createSubset() {
        return xe::gfx::MeshSubset();
    }
    
    void initialize() {
        graphicsDriver = this->createGraphicsDriver();
        graphicsDriver->initialize();
        
        vertexFormat = createVertexFormat();
        materialFormat = createMaterialFormat();
        
        subset = createSubset();
        material = createMaterial();
        shader = createSubset();
    }
    
    virtual int run(int argc, char **argv) override {
        
        inputManager = graphicsDriver->getInputManager();
        
        auto keyboardStatus = inputManager->getKeyboard()->getStatus();
        
        bool done = false;
        
        while(!done) {
            inputManager->poll();
            
            done = keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyEsc);
            
            graphicsDriver->beginFrame({0.0f, 0.0f, 1.0f, 1.0f}, xe::gfx::ClearFlags::ColorDepth);
            
            graphicsDriver->endFrame();
        }
        
        return 0;
    }
    
private:
    xe::input2::IInputManager *inputManager = nullptr;
    
    xe::gfx::GraphicsDriverPtr graphicsDriver;
    xe::gfx::VertexFormat vertexFormat;
    xe::gfx::MaterialFormat materialFormat
    ;
    xe::gfx::MeshSubsetPtr subset;
    xe::gfx::MaterialPtr material;
    
    xe::gfx::ShaderProgramPtr shader;
};

int main(int argc, char **argv) {
    return xe::fw::Application::execute<TriangleApplication>(argc, argv);
}
