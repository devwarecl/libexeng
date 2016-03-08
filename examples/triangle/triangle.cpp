
#include <xe/Application.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/Vertex.hpp>

class TriangleApplication : public xe::Application {
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
        
		material->setAttribute("ambient", xe::Vector4f(1.0f, 1.0f, 0.0f, 1.0f));
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

uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emissive;
uniform float shininess;

uniform sampler2D tex_sampler;

void main() {
	color = /*texture(tex_sampler, uv) * */ambient;
})";
		std::list<xe::gfx::ShaderSource> sources = {
			{xe::gfx::ShaderType::Vertex, vshader_src},
			{xe::gfx::ShaderType::Fragment, pshader_src}
		};

		auto modernModule = graphicsDriver->getModernModule();
		auto program = modernModule->createShaderProgram(sources);

		return program;
    }
    
    xe::gfx::MeshSubsetPtr createSubset() {

		// vertex data
		xe::gfx::StandardVertex v1, v2, v3, v4, v5, v6;
		v1.coord = { -1.5f, -1.5f, 0.0f };	v1.normal = { 0.0f, 0.0f, -1.0f }; v1.texCoord = { 0.0f, 1.0f };
		v2.coord = {  0.0f,  1.5f, 0.0f };	v2.normal = { 0.0f, 0.0f, -1.0f }; v2.texCoord = { 0.0f, 0.0f };
		v3.coord = {  1.5f, -1.5f, 0.0f };	v3.normal = { 0.0f, 0.0f, -1.0f }; v3.texCoord = { 1.0f, 1.0f };
		v4.coord = { -1.5f, -1.5f, 0.0f };	v4.normal = { 0.0f, 0.0f,  1.0f }; v4.texCoord = { 0.0f, 1.0f };
		v5.coord = {  0.0f,  1.5f, 0.0f };	v5.normal = { 0.0f, 0.0f,  1.0f }; v5.texCoord = { 0.0f, 0.0f };
		v6.coord = {  1.5f, -1.5f, 0.0f };	v6.normal = { 0.0f, 0.0f,  1.0f }; v6.texCoord = { 1.0f, 1.0f };
		
		std::vector<xe::gfx::StandardVertex> vertices = {v1, v2, v3, v4, v5, v6};

		// index data
		std::vector<int> indices = {0, 1, 2, 4, 3, 5};

		// create vertex and index buffers
		auto vbuffer = graphicsDriver->createVertexBuffer(vertices);
		auto ibuffer = graphicsDriver->createIndexBuffer(indices);

		// create the triangle meshsubset
		auto subset = graphicsDriver->createMeshSubset (
            std::move(vbuffer),  &vertexFormat, 
            std::move(ibuffer),  xe::gfx::IndexFormat::Index32
        );

        return subset;
    }
    
    void initialize() {
        graphicsDriver = this->createGraphicsDriver();
        graphicsDriver->initialize();
        
        vertexFormat = createVertexFormat();
        materialFormat = createMaterialFormat();
        
        subset = createSubset();
		shader = createProgram();
        material = createMaterial();
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
			graphicsDriver->getModernModule()->setShaderProgram(shader.get());
			graphicsDriver->getModernModule()->setProgramMatrix("mvp", mvp);
			graphicsDriver->setMaterial(material.get());
			graphicsDriver->setMeshSubset(subset.get());
			graphicsDriver->render(xe::gfx::Primitive::TriangleList, 6);
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
    
    xe::gfx::ShaderProgramPtr shader;
};

int main(int argc, char **argv) {
    return xe::Application::execute<TriangleApplication>(argc, argv);
}
