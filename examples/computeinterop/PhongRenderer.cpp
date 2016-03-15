
#include "PhongRenderer.hpp"

#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/Vertex.hpp>
#include <xe/sg/Camera.hpp>
#include <xe/sg/Light.hpp>

extern std::string fshader_src;
extern std::string vshader_src;

PhongRenderer::PhongRenderer(xe::gfx::GraphicsDriver *graphicsDriver) {
	assert(graphicsDriver);

	this->graphicsDriver = graphicsDriver;
	this->programmableModule = graphicsDriver->getModernModule();

	// create vertex format
	vertexFormat = xe::gfx::StandardVertex::getFormat();

	// create material format
	std::vector<xe::gfx::MaterialAttrib> attribs = {
        {"ambient", xe::DataType::Float32, 4},
        {"diffuse", xe::DataType::Float32, 4},
        {"specular", xe::DataType::Float32, 4},
        {"emission", xe::DataType::Float32, 4},
        {"shininess", xe::DataType::Float32, 1}
    };
    
	std::vector<xe::gfx::MaterialLayerDesc> layerdescs = {
		{"texture0"}
	};

	materialFormat = xe::gfx::MaterialFormat(attribs, layerdescs);

	// create shader program
	std::list<xe::gfx::ShaderSource> sources = {
		{xe::gfx::ShaderType::Vertex, vshader_src},
		{xe::gfx::ShaderType::Fragment, fshader_src}
	};

	shaderProgram = graphicsDriver->getModernModule()->createShaderProgram(sources);

	graphicsDriver->getModernModule()->setShaderProgram(shaderProgram.get());
}

PhongRenderer::~PhongRenderer() {
	graphicsDriver->getModernModule()->setShaderProgram(nullptr);
}

void PhongRenderer::beginFrame(const xe::Vector4f &color) {
	graphicsDriver->beginFrame(color);
}

void PhongRenderer::endFrame() {
	graphicsDriver->endFrame();
}

void PhongRenderer::render(xe::sg::Light *light) {
	assert(light);

	programmableModule->setProgramParam("light_position", light->getPosition());
	programmableModule->setProgramParam("light_range", light->getRange());
}

void PhongRenderer::render(xe::sg::Camera *camera) {
	assert(camera);

	xe::Matrix4f proj = camera->computeProj();
	xe::Matrix4f view = camera->computeView();

	programmableModule->setProgramMatrix("proj", proj);
	programmableModule->setProgramMatrix("view", view);
}

void PhongRenderer::render(xe::sg::Geometry *geometry) {
	assert(!geometry);
}

void PhongRenderer::render(xe::gfx::Mesh *mesh) {
	assert(mesh);

	graphicsDriver->render(mesh);
}

void PhongRenderer::setModel(const xe::Matrix4f &transformation) {
	programmableModule->setProgramMatrix("model", transformation);
}

const xe::gfx::VertexFormat* PhongRenderer::getVertexFormat() const {
	return &vertexFormat;
}

const xe::gfx::MaterialFormat* PhongRenderer::getMaterialFormat() const {
	return &materialFormat;
}

std::string fshader_src = 
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

uniform sampler2D texture0;

void main() {
	vec4 light_direction = normalize(vec4(0.0f, -1.0f, 0.25f, 0.0f));
	float factor = dot(light_direction, vec4(n, 1.0f));	

	color = (texture(texture0, uv) * 0.5 + diffuse * 0.5) * factor;
}
)";


std::string vshader_src = R"(
#version 330
layout(location=0) in vec3 coord;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 tex_coord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 n;
out vec2 uv;

void main() {
	mat4 mvp = proj * view * model;

	gl_Position = mvp * vec4(coord, 1.0f);
	n = vec3(mvp * vec4(normal, 1.0f));
	uv = tex_coord;
}
)";
