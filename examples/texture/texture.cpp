
#include <xe/Application.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/ImageManager.hpp>
#include <xe/gfx/Vertex.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/MeshManager.hpp>
#include <xe/gfx/MeshSubsetGeneratorBox.hpp>

class TextureApplication : public xe::Application {
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
        
        material->getLayer(0)->texture = texture.get();
		material->setAttribute("ambient", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("diffuse", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("specular", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("emission", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("shininess", 1.0f);

        return material;
    }
    
    xe::gfx::ShaderProgramPtr createProgram() {

		std::string vshader_src = 
R"(#version 330
layout(location=0) in vec3 coord;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 tex_coord;

uniform mat4 mvp;

out vec3 n;
out vec2 uv;

void main() {
	gl_Position = vec4(coord, 1.0f) * mvp;
	n = normal;
	uv = tex_coord;
})";

		std::string pshader_src = 
R"(
#version 330

in vec3 n;
in vec2 uv;

out vec4 color;

uniform sampler2D tex_sampler;

uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emissive;
uniform float shininess;

void main() {
    // color = vec4(uv, 0.0f, 1.0f);
    // color = vec4(n, 1.0f);
	color = texture(tex_sampler, uv);
})";
		std::list<xe::gfx::ShaderSource> sources = {
			{xe::gfx::ShaderType::Vertex, vshader_src},
			{xe::gfx::ShaderType::Fragment, pshader_src}
		};

		auto modernModule = graphicsDriver->getModernModule();
		auto program = modernModule->createShaderProgram(sources);

		return program;
    }
    
    //xe::gfx::Mesh* createMesh() {
    //    xe::gfx::Mesh* mesh = this->getMeshManager()->generateBoxMesh (
    //        "box",
    //        graphicsDriver.get(), 
    //        &vertexFormat,
    //        xe::gfx::IndexFormat::Index32,
    //        {0.0f, 0.0f, 0.0f},
    //        {1.0f, 1.0f, 1.0f}
    //    );
    //
    //    for (int i=0; i<mesh->getSubsetCount(); i++) {
    //        mesh->getSubset(i)->setMaterial(material.get());
    //    }
    //
    //    return mesh;
    //}

    xe::gfx::MeshSubsetPtr createBoxSubset(const xe::gfx::Material *material) {
        xe::gfx::MeshSubsetGeneratorBox boxgen(graphicsDriver.get());
        xe::gfx::MeshSubsetPtr subset = boxgen.generate({&vertexFormat, xe::gfx::IndexFormat::Index32});

        subset->setMaterial(material);

        return subset;
    }

    xe::gfx::TexturePtr createTexture() {
        auto toolkit = this->getGraphicsManager()->getImageToolkit();
        auto image = toolkit->getImage("C:\\Users\\fapablaza\\Desktop\\Projects\\libexeng\\media\\puppy.jpg");
        auto texture = graphicsDriver->createTexture(image);
        
        return texture;
    }

    void initialize() {
        graphicsDriver = this->createGraphicsDriver();
        graphicsDriver->initialize();
        
        vertexFormat = createVertexFormat();
        materialFormat = createMaterialFormat();
        
		shader = createProgram();
        texture = createTexture();
        material = createMaterial();
        subset = createBoxSubset(material.get());
    }
    
    virtual int run(int argc, char **argv) override {
        
		this->initialize();

        inputManager = graphicsDriver->getInputManager();
        
        auto keyboardStatus = inputManager->getKeyboard()->getStatus();
        
        bool done = false;
        float angle = 0.0f;

        while(!done) {
            inputManager->poll();
            
            if (++angle > 360.0f) {
                angle -= 360.0f;
            }

            xe::Vector3f position(0.0f, 2.0f, -1.0f);
            xe::Vector3f look_point(0.0f, 0.0f, 0.0f);
            xe::Vector3f up_direction(0.0f, 1.0f, 0.0f);

            xe::Matrix4f proj = xe::perspective<float>(xe::rad(60.0f), 640.0f/480.0f, 0.1f, 1000.0f);
            xe::Matrix4f view = xe::lookat<float>(position, look_point, up_direction);
            xe::Matrix4f model = xe::rotatey<float>(xe::rad(angle));

            xe::Matrix4f mvp = proj * view * model;
                
            done = keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyEsc);
            
            graphicsDriver->beginFrame({0.0f, 0.0f, 1.0f, 1.0f}, xe::gfx::ClearFlags::ColorDepth);
            
            graphicsDriver->setMaterial(subset->getMaterial());
            graphicsDriver->getModernModule()->setProgramMatrix("mvp", mvp);
            graphicsDriver->setMeshSubset(subset.get());
            graphicsDriver->render(subset->getPrimitive(), subset->getVertexCount());
			
            graphicsDriver->endFrame();
        }
        
        return 0;
    }

private:
    xe::input2::IInputManager *inputManager = nullptr;
    
    xe::gfx::GraphicsDriverPtr graphicsDriver;
    xe::gfx::VertexFormat vertexFormat;
    xe::gfx::MaterialFormat materialFormat;
    xe::gfx::MeshSubsetPtr subset;
    xe::gfx::MaterialPtr material;
    xe::gfx::TexturePtr texture;

    xe::gfx::ShaderProgramPtr shader;
};

int main(int argc, char **argv) {
    return xe::Application::execute<TextureApplication>(argc, argv);
}
