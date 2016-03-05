
#include <xe/Application.hpp>
#include <xe/gfx/Algorithm.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/ImageManager.hpp>
#include <xe/gfx/Vertex.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/MeshManager.hpp>
#include <xe/gfx/MeshSubsetGeneratorBox.hpp>

class SimpleMeshApplication : public xe::Application {
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
        
        material->getLayer(0)->setTexture(texture.get());
		material->setAttribute("ambient", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("diffuse", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("specular", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("emission", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("shininess", 1.0f);

        return material;
    }
    
    xe::gfx::MaterialPtr createMaterial2() {
        auto material = std::make_unique<xe::gfx::Material>(&materialFormat);
        
        material->getLayer(0)->setTexture(texture2.get());
		material->setAttribute("ambient", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("diffuse", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("specular", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("emission", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("shininess", 1.0f);

        return material;
    }

    xe::gfx::MaterialPtr createMaterial3() {
        auto material = std::make_unique<xe::gfx::Material>(&materialFormat);
        
        material->getLayer(0)->setTexture(texture3.get());
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
    
    xe::gfx::MeshSubsetPtr createBoxMesh() {
        xe::gfx::MeshSubsetGeneratorBox boxgen(graphicsDriver.get());

        return boxgen.generate({&vertexFormat});
    }

    xe::gfx::MeshPtr createMesh() {
        auto subset1 = createBoxMesh();
        xe::gfx::transform(subset1.get(), xe::scale<float, 4>({2.0f, 0.5f, 2.0f}));
        xe::gfx::transform(subset1.get(), xe::translate<float>({0.0f, -0.25f, 0.0f}));
        subset1->setMaterial(material.get());

        auto subset2 = createBoxMesh();
        xe::gfx::transform(subset2.get(), xe::scale<float, 4>({0.5f, 1.5f, 0.5f}));
        xe::gfx::transform(subset2.get(), xe::translate<float>({0.0f, 0.25f, 0.0f}));
        subset2->setMaterial(material2.get());

        auto subset3 = createBoxMesh();
        xe::gfx::transform(subset3.get(), xe::translate<float>({1.0f, 0.25f, 0.0f}));
        subset3->setMaterial(material3.get());
        
        std::vector<xe::gfx::MeshSubsetPtr> subsets;
        subsets.push_back(std::move(subset1));
        subsets.push_back(std::move(subset2));
        subsets.push_back(std::move(subset3));

        return std::make_unique<xe::gfx::Mesh>(std::move(subsets));
    }

    xe::gfx::TexturePtr createTexture() {
        auto toolkit = this->getGraphicsManager()->getImageToolkit();
        auto image = toolkit->getImage("C:\\Users\\fapablaza\\Desktop\\Projects\\libexeng\\media\\puppy.jpg");
        auto texture = graphicsDriver->createTexture(image);
        
        return texture;
    }

    xe::gfx::TexturePtr createTexture2() {
        auto toolkit = this->getGraphicsManager()->getImageToolkit();
        auto image = toolkit->getImage("C:\\Users\\fapablaza\\Desktop\\Projects\\libexeng\\media\\metal126.jpg");
        auto texture = graphicsDriver->createTexture(image);
        
        return texture;
    }

    xe::gfx::TexturePtr createTexture3() {
        auto toolkit = this->getGraphicsManager()->getImageToolkit();
        auto image = toolkit->getImage("C:\\Users\\fapablaza\\Desktop\\Projects\\libexeng\\media\\tiles_ctf05b.jpg");
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
        texture2 = createTexture2();
        texture3 = createTexture3();
        material = createMaterial();
        material2 = createMaterial2();
        material3 = createMaterial3();
        mesh = createMesh();
    }
    
    virtual int run(int argc, char **argv) override {
        
		this->initialize();

        inputManager = graphicsDriver->getInputManager();
        
        auto keyboardStatus = inputManager->getKeyboard()->getStatus();
        
        bool done = false;
        float angle = 0.0f;

        while (!done) {
            inputManager->poll();
            
            done = keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyEsc);

            if (++angle > 360.0f) {
                angle -= 360.0f;
            }

            xe::Vector3f position(0.0f, 1.0f, -2.0f);
            xe::Vector3f look_point(0.0f, 0.0f, 0.0f);
            xe::Vector3f up_direction(0.0f, 1.0f, 0.0f);

            xe::Matrix4f proj = xe::perspective<float>(xe::rad(60.0f), 640.0f/480.0f, 0.1f, 1000.0f);
            xe::Matrix4f view = xe::lookat<float>(position, look_point, up_direction);
            xe::Matrix4f model = xe::rotatey<float>(xe::rad(angle));

            xe::Matrix4f mvp = proj * view * model;
            
            graphicsDriver->beginFrame({0.0f, 0.0f, 1.0f, 1.0f}, xe::gfx::ClearFlags::ColorDepth);
            
            this->renderMesh(mesh.get(), "mvp", mvp);
			
            graphicsDriver->endFrame();
        }
        
        return 0;
    }
    
    void renderMesh(const xe::gfx::Mesh *mesh, const std::string &param, const xe::Matrix4f &mvp) {
        for (int i=0; i<mesh->getSubsetCount(); i++) {
            const xe::gfx::MeshSubset *subset = mesh->getSubset(i);

            graphicsDriver->setMaterial(subset->getMaterial());
            graphicsDriver->getModernModule()->setProgramGlobal(param, mvp);
            graphicsDriver->setMeshSubset(subset);
            graphicsDriver->render(subset->getPrimitive(), subset->getVertexCount());
        }
    }

private:
    xe::input2::IInputManager *inputManager = nullptr;
    
    xe::gfx::GraphicsDriverPtr graphicsDriver;
    xe::gfx::VertexFormat vertexFormat;
    xe::gfx::MaterialFormat materialFormat;
    xe::gfx::MeshPtr mesh = nullptr;
    xe::gfx::MaterialPtr material;
    xe::gfx::MaterialPtr material2;
    xe::gfx::MaterialPtr material3;
    xe::gfx::TexturePtr texture;
    xe::gfx::TexturePtr texture2;
    xe::gfx::TexturePtr texture3;

    xe::gfx::ShaderProgramPtr shader;
};

int main(int argc, char **argv) {
    return xe::Application::execute<SimpleMeshApplication>(argc, argv);
}
