
#include <list>
#include <xe/Core.hpp>
#include <xe/sys/Plugin.hpp>
#include <xe/sg/SceneLoader.hpp>
#include <xe/sg/SceneManager.hpp>

#include "xmlpp/Document.hpp"

namespace xml {
	struct Scene {
		struct ShaderLibrary {
			struct Shader {
				std::string name;
				std::string type;
				std::string file;
			};

			struct Progam {
				struct Module {
					std::string refname;
				};

				std::string name;
				std::vector<Module> modules;
			};

			std::string language;
			std::vector<Shader> shaders;
			std::vector<Progam> programs;
		};

		struct MaterialLibrary {
			struct Format {
				struct Attribute {
					std::string name;
					std::string type;
				};

				std::vector<Attribute> attributes;
			};

			struct Material {
				struct Layer {
					struct Texture {
						std::string name;
						std::string source;
						std::string file;
						std::string type;
						std::vector<int> size;
						std::vector<int> grid;
					} texture;
				};

				struct Attribute {
					std::string refname;
					std::vector<float> value;
				};

				std::string name;
				std::string program;
				std::vector<Layer> layers;
				std::vector<Attribute> attributes;
			};

			Format format;
			std::vector<Material> materials;
		};

		struct GeometryLibrary {
			struct VertexFormat {
				struct Attribute {
					std::string name;
					std::string type;
					std::string use;
				};

				std::vector<Attribute> attributes;
			};

			struct Geometry {
				struct Mesh {
					struct MeshSubset {
						std::string material;
						std::string generator;
						std::vector<float> size;
						std::vector<float> center;
					};

					std::string source;
					std::string filename;
					std::vector<MeshSubset> subsets;
				};

				std::string name;
				std::string type;
				Mesh mesh;
			};

			VertexFormat vertexFormat;
			std::vector<Geometry> geometries;
		};

		struct Background {
			std::vector<float> color;
		};

		struct Camera {
			struct View {
				std::string type;
				std::vector<float> position;
				std::vector<float> lookat;
				std::vector<float> up;
			};

			struct Projection {
				std::string type;
				float fov;
				float aspect;
				float znear;
				float zfar;
			};

			struct Viewport {
				std::vector<float> position;
				std::vector<float> size;
			};

			std::string name;
			View view;
			Projection projection;
			Viewport viewport;
		};

		struct Node {
			struct Transformation {
				std::string type;
				std::vector<float> value;
			};

			struct Data {
				std::string type;
				std::string refname;
			};

			std::string name;
			std::vector<Transformation> transformations;
			Data data;
			std::vector<Node> childs;
		};
		
		std::string name;
		ShaderLibrary shaderLibrary;
		MaterialLibrary materialLibrary;
		GeometryLibrary geometryLibrary;
		std::vector<Camera> cameras;
		Node node;
	};
}

namespace xe { namespace sg {

	xml::Scene::ShaderLibrary::Shader parseShader(const xmlpp::NodeRef &node) {
		xml::Scene::ShaderLibrary::Shader shader;

		shader.name = node.getAttribute("name");
		shader.type = node.getAttribute("type");
		shader.file = node.getAttribute("file");

		return shader;
	}

	xml::Scene::ShaderLibrary::Progam::Module parseModule(const xmlpp::NodeRef &node) {
		xml::Scene::ShaderLibrary::Progam::Module module;

		module.refname = node.getAttribute("refname");

		return module;
	}

	xml::Scene::ShaderLibrary::Progam parseProgram(const xmlpp::NodeRef &node) {
		xml::Scene::ShaderLibrary::Progam program;

		program.name = node.getAttribute("name");

		for (const xmlpp::NodeRef &child : node.getChilds("module")) {
			program.modules.push_back(parseModule(child));
		}

		return program;
	}

	xml::Scene::ShaderLibrary parseShaderLibrary(const xmlpp::NodeRef &node) {
		xml::Scene::ShaderLibrary shaderLibrary;

		shaderLibrary.language = node.getAttribute("language");

		for (const xmlpp::NodeRef &child : node.getChilds()) {
			std::string childName = child.getName();

			if (childName == "shader") {
				shaderLibrary.shaders.push_back(parseShader(child));

			} else if (childName == "program") {
				shaderLibrary.programs.push_back(parseProgram(child));
			}
		}

		return shaderLibrary;
	}

	xml::Scene::MaterialLibrary::Format::Attribute parseMaterialFormatAttribute(const xmlpp::NodeRef &node) {
		xml::Scene::MaterialLibrary::Format::Attribute attribute;

		attribute.name = node.getAttribute("name");
		attribute.type = node.getAttribute("type");

		return attribute;
	}

	xml::Scene::MaterialLibrary::Format parseMaterialFormat(const xmlpp::NodeRef &node) {
		xml::Scene::MaterialLibrary::Format format;

		for (const xmlpp::NodeRef &child : node.getChilds("attribute")) {
			format.attributes.push_back( parseMaterialFormatAttribute(child));
		}

		return format;
	}

	xml::Scene::MaterialLibrary::Material::Layer::Texture parseMaterialLayerTexture(const xmlpp::NodeRef &node) {
		xml::Scene::MaterialLibrary::Material::Layer::Texture texture;

		texture.name = node.getAttribute("name");
		texture.source = node.getAttribute("source");
		texture.type = node.getAttribute("type");
		texture.size = node.getAttribute<int>("size", " ");
		texture.grid = node.getAttribute<int>("grid", " ");

		return texture;
	}

	xml::Scene::MaterialLibrary::Material::Layer parseMaterialLayer(const xmlpp::NodeRef &node) {
		xml::Scene::MaterialLibrary::Material::Layer layer;

		layer.texture = parseMaterialLayerTexture(node.getChild("texture"));

		return layer;
	}

	xml::Scene::MaterialLibrary::Material::Attribute parseMaterialAttribute(const xmlpp::NodeRef &node) {
		xml::Scene::MaterialLibrary::Material::Attribute attribute;

		attribute.refname = node.getAttribute("refname");
		attribute.value = node.getAttribute<float>("value", " ");

		return attribute;
	}

	xml::Scene::MaterialLibrary::Material parseMaterial(const xmlpp::NodeRef &node) {
		xml::Scene::MaterialLibrary::Material material;

		material.name = node.getAttribute("name");
		material.program = node.getAttribute("program");

		for (const xmlpp::NodeRef &child : node.getChilds("layer")) {
			material.layers.push_back(parseMaterialLayer(child));
		}

		for (const xmlpp::NodeRef &child : node.getChilds("attribute")) {
			material.attributes.push_back(parseMaterialAttribute(child));
		}
		
		return material;
	}

	xml::Scene::MaterialLibrary parseMaterialLibrary(const xmlpp::NodeRef &node) {
		xml::Scene::MaterialLibrary materialLibrary;

		materialLibrary.format = parseMaterialFormat(node.getChild("format"));

		for (auto child : node.getChilds("material")) {
			materialLibrary.materials.push_back(parseMaterial(child));
		}

		return materialLibrary;
	}

	xml::Scene::GeometryLibrary::VertexFormat::Attribute parseVertexFormatAttribute(const xmlpp::NodeRef &node) {
		xml::Scene::GeometryLibrary::VertexFormat::Attribute attribute;

		attribute.name = node.getAttribute("name");
		attribute.type = node.getAttribute("type");
		attribute.use = node.getAttribute("use");

		return attribute;
	}

	xml::Scene::GeometryLibrary::VertexFormat parseVertexFormat(const xmlpp::NodeRef &node) {
		xml::Scene::GeometryLibrary::VertexFormat format;

		for (auto child : node.getChilds("attribute")) {
			format.attributes.push_back(parseVertexFormatAttribute(child));
		}

		return format;
	}

	xml::Scene::GeometryLibrary::Geometry::Mesh::MeshSubset parseMeshSubset(const xmlpp::NodeRef &node) {
		xml::Scene::GeometryLibrary::Geometry::Mesh::MeshSubset subset;

		subset.material = node.getAttribute("material");
		subset.generator = node.getAttribute("generator");
		subset.center = node.getAttribute<float>("center", " ");
		subset.size = node.getAttribute<float>("size", " ");

		return subset;
	}

	xml::Scene::GeometryLibrary::Geometry::Mesh parseMesh(const xmlpp::NodeRef &node) {
		xml::Scene::GeometryLibrary::Geometry::Mesh mesh;

		mesh.source = node.getAttribute("source");
		mesh.filename = node.getAttribute("filename");
		
		for (const xmlpp::NodeRef &child : node.getChilds("mesh-subset")) {
			mesh.subsets.push_back(parseMeshSubset(node));
		}

		return mesh;
	}

	xml::Scene::GeometryLibrary::Geometry parseGeometry(const xmlpp::NodeRef &node) {
		xml::Scene::GeometryLibrary::Geometry geometry;

		geometry.name = node.getAttribute("name");
		geometry.type = node.getAttribute("type");
		geometry.mesh = parseMesh(node.getChild("mesh"));

		return geometry;
	}

	xml::Scene::GeometryLibrary parseGeometryLibrary(const xmlpp::NodeRef &node) {
		xml::Scene::GeometryLibrary geometryLibrary;

		geometryLibrary.vertexFormat = parseVertexFormat(node.getChild("vertex-format"));

		for (auto child : node.getChilds("geometry")) {
			geometryLibrary.geometries.push_back(parseGeometry(child));
		}

		return geometryLibrary;
	}

	xml::Scene::Background parseBackground(const xmlpp::NodeRef &node) {
		xml::Scene::Background background;

		background.color = node.getAttribute<float>("color", " ");

		return background;
	}

	xml::Scene::Camera::View parseView(const xmlpp::NodeRef &node) {
		xml::Scene::Camera::View view;

		view.type = node.getAttribute("type");
		view.position = node.getAttribute<float>("position", " ");
		view.lookat = node.getAttribute<float>("lookat", " ");
		view.up = node.getAttribute<float>("up", " ");

		return view;
	}

	xml::Scene::Camera::Projection parseProjection(const xmlpp::NodeRef &node) {
		xml::Scene::Camera::Projection projection;

		projection.type = node.getAttribute("type");
		projection.fov = node.getAttribute<float>("fov");
		projection.aspect = node.getAttribute<float>("aspect");
		projection.znear = node.getAttribute<float>("znear");
		projection.zfar = node.getAttribute<float>("zfar");

		return projection;
	}

	xml::Scene::Camera::Viewport parseViewport(const xmlpp::NodeRef &node) {
		xml::Scene::Camera::Viewport viewport;

		viewport.position = node.getAttribute<float>("position", " ");
		viewport.size = node.getAttribute<float>("size", " ");

		return viewport;
	}

	xml::Scene::Camera parseCamera(const xmlpp::NodeRef &node) {
		xml::Scene::Camera camera;

		camera.name = node.getAttribute("name");
		camera.view = parseView(node.getChild("view"));
		camera.projection = parseProjection(node.getChild("projection"));
		camera.viewport = parseViewport(node.getChild("viewport"));

		return camera;
	}

	xml::Scene::Node::Transformation parseTransformation(const xmlpp::NodeRef &node) {
		xml::Scene::Node::Transformation transformation;

		transformation.type = node.getAttribute("type");
		transformation.value = node.getAttribute<float>("value", " ");

		return transformation;
	}

	xml::Scene::Node::Data parseNodeData(const xmlpp::NodeRef &node) {
		xml::Scene::Node::Data nodeData;

		nodeData.type = node.getAttribute("type");
		nodeData.refname = node.getAttribute("refname");

		return nodeData;
	}

	xml::Scene::Node parseNode(const xmlpp::NodeRef &node) {
		xml::Scene::Node node_;

		node_.name = node.getAttribute("name");
		node_.data = parseNodeData(node.getChild("data"));

		for (auto child : node.getChilds("transformation")) {
			node_.transformations.push_back(parseTransformation(child));
		}

		for (auto child : node.getChilds("node")) {
			node_.childs.push_back(parseNode(child));
		}

		return node_;
	}

	xml::Scene parseScene(const xmlpp::NodeRef &node) {
		xml::Scene scene;

		scene.name = node.getAttribute("name");
		scene.shaderLibrary = parseShaderLibrary(node.getChild("shader-library"));
		scene.materialLibrary = parseMaterialLibrary(node.getChild("material-library"));
		scene.geometryLibrary = parseGeometryLibrary(node.getChild("geometry-library"));

		for (auto child : node.getChilds("camera")) {
			scene.cameras.push_back( parseCamera(child) );
		}

		scene.node = parseNode(node.getChild("node"));

		return scene;
	}

	class SceneLoaderXML : public SceneLoader {
	public:
		SceneLoaderXML(Core *core) : SceneLoader(core) {}

		virtual ~SceneLoaderXML() {}

		virtual bool isSupported(const std::string &file) {
			return true;
		}

		virtual ScenePtr load(const std::string &file) {
			xmlpp::Document document = ::xmlReadFile(file.c_str(), nullptr, 0);
			xml::Scene xmlScene = parseScene(document.GetRootNode());
			xe::sg::ScenePtr scene = this->createScene(xmlScene);

			return scene;
		}

	private:
		xe::sg::ScenePtr createScene(const xml::Scene &xmlScene) {
			auto scene = std::make_unique<xe::sg::Scene>();

			return scene;
		}
	};

	class SceneLoaderXMLPlugin : public xe::sys::Plugin {
	public:
		virtual std::string getName() const override {
			return "SceneLoader XML Plugin";
		}

        virtual std::string getDescription() const override {
			return "Load a full scene from data stored on a XML file.";
		}

        virtual Version getVersion() const override {
			return Version(1, 0, 0, 0);
		}

        virtual void initialize(Core *core) override {
			this->core = core;

			sceneLoaderXML = std::make_unique<SceneLoaderXML>(core);
			core->getSceneManager()->addSceneLoader(sceneLoaderXML.get());
		}

        virtual void terminate() override {
			core->getSceneManager()->removeSceneLoader(sceneLoaderXML.get());
			this->sceneLoaderXML.reset();
		}

	private:
		Core *core = nullptr;
		std::unique_ptr<SceneLoaderXML> sceneLoaderXML;
	};
}}

#if defined (EXENG_WINDOWS)
#  if defined (EXENG_64)
#    pragma comment (linker, "/export:ExengGetPluginObject")
#    undef EXENG_EXPORT
#  endif
#endif 

EXENG_EXPORT_PLUGIN(xe::sg::SceneLoaderXMLPlugin);
