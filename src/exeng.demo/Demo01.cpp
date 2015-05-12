
#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <exeng/Exeng.hpp>
#include <exeng/graphics/VertexWrapper.hpp>
#include <exeng/graphics/ShaderLibrary.hpp>
#include <exeng/graphics/MeshSubset.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/framework/GraphicsApplication.hpp>

#include "Fragment.glsl.hpp"
#include "Vertex.glsl.hpp"
#include "Assets.xml.hpp"

using namespace exeng;
using namespace exeng::framework;
using namespace exeng::graphics;
using namespace exeng::scenegraph;
using namespace exeng::input;

class SpatialAnimator : public SceneNodeAnimator {
public:
	SpatialAnimator() {}
	explicit SpatialAnimator(SceneNode *node) : SceneNodeAnimator(node) {}

	virtual void update(double seconds) override {
		this->angle += static_cast<float>(60.0 * seconds);

		auto transform = identity<float, 4>();
		transform *= rotatex<float>(rad(angle));
		transform *= rotatey<float>(rad(angle));
		transform *= rotatez<float>(rad(angle));

		this->getSceneNode()->setTransform(transform);
	}

private:
	float angle = 0.0f;
};

class AssetLibrary {
public:
	void addAsset(const std::string &fileId, void* data, const int dataSize) {
#if defined(EXENG_DEBUG)
		if (!data) {
			EXENG_THROW_EXCEPTION("Asset data must be a null pointer.");
		}

		if (dataSize <= 0) {
			EXENG_THROW_EXCEPTION("Invalid buffer size");
		}
#endif
		StaticBufferPtr assetData = std::make_unique<StaticBuffer>(data, dataSize);

		this->assets[fileId] = std::move(assetData);
	}

	void addAsset(const std::string &fileId, BufferPtr assetData) {
		this->assets[fileId] = std::move(assetData);
	}

	Buffer* getAsset(const std::string &file) {
		return this->assets[file].get();
	}

private:
	std::map<std::string, BufferPtr> assets;
};
typedef std::unique_ptr<AssetLibrary> AssetLibraryPtr;

class GeometryLibrary {
public:
	void initialize(const VertexFormat &format) {
		this->geometries = std::map<std::string, GeometryPtr>();
		this->format = format;
	}

	void addGeometry(const std::string &name, GeometryPtr geometry) {
		this->geometries[name] = std::move(geometry);
	}

	Geometry* getGeometry(const std::string &name) {
		return this->geometries[name].get();
	}

	VertexFormat getFormat() const {
		return this->format;
	}

private:
	std::map<std::string, GeometryPtr> geometries;
	VertexFormat format;
};
typedef std::unique_ptr<GeometryLibrary> GeometryLibraryPtr;

namespace xml {
	class Node;
	typedef std::list<Node> NodeList;

	class Node {
	public:
		Node(::xmlNode *node) {
			this->node = node;
		}

		std::string getName() const {
			return (const char*)(this->node->name);
		}

		std::string getAttribute(const std::string &attrName) const {
			return (const char*)(::xmlGetProp(this->node, (const xmlChar*) attrName.c_str()));
		}

		bool hasAttribute(const std::string &attrName) const {
			const void* raw = (::xmlGetProp(this->node, (const xmlChar*) attrName.c_str()));
			return raw != nullptr;
		}

		std::string getContent() const {
			return (const char*)::xmlNodeGetContent(this->node);
		}

		NodeList getChilds() const {
			NodeList childs;

			for (::xmlNode *child=this->node->children; child; child=child->next) {
				if (child->type != XML_ELEMENT_NODE) {
					continue;
				}

				childs.push_back(child);
			}

			return childs;
		}

		NodeList getChilds(const std::string &name) const {
			NodeList childs;

			for (::xmlNode *child=this->node->children; child; child=child->next) {
				if (child->type != XML_ELEMENT_NODE) {
					continue;
				}

				if ( ::xmlStrcmp(child->name, (const xmlChar*)name.c_str()) == 0) {
					childs.push_back(child);
				}
			}

			return childs;
		}

		Node getChild(const std::string &name) const {
			auto &childs = this->getChilds(name);

#if defined(EXENG_DEBUG)
			if (childs.size() == 0) {
				EXENG_THROW_EXCEPTION("No child with the name '" + name + "'");
			}
#endif
			return *childs.begin();
		}

	private:
		::xmlNode *node = nullptr;
	};
}

class AssetsLoader {
public:
	AssetsLoader(AssetLibrary *assetLibrary, GraphicsDriver *driver, MaterialLibrary *materialLibrary, GeometryLibrary *geometryLibrary, ShaderLibrary *shaderLibrary, Scene *scene) {
		this->assetLibrary = assetLibrary;
		this->driver = driver;
		this->materialLibrary = materialLibrary;
		this->geometryLibrary = geometryLibrary; 
		this->shaderLibrary = shaderLibrary;
		this->scene = scene;
	}

	void loadAssets() {
		const char* assetsXmlData = assets_xml_data;
		const int assetsXmlSize = assets_xml_size;

		xmlDoc *document = ::xmlReadMemory(assetsXmlData, assetsXmlSize, "", nullptr, 0);
		if (!document) {
			EXENG_THROW_EXCEPTION("Can't read memory for XML parsing.");
		}

		xml::Node node = ::xmlDocGetRootElement(document);

		if (node.getName() == "assets") {
			this->parseAssets(node);
		} else {
			EXENG_THROW_EXCEPTION("'assets' root node doesn't exists.");
		}

		::xmlFreeDoc(document);
		::xmlCleanupParser();
	}

private:
	void parseShaderLibrary(const xml::Node &node) {
		for (xml::Node child : node.getChilds()) {
			std::string name = child.getName();

			if (name == "shader") {
				std::string shaderName = child.getAttribute("name");
				std::string shaderType = child.getAttribute("type");
				std::string shaderFile = child.getAttribute("file");

				Shader *shader = this->shaderLibrary->createShader(shaderName, getShaderType(shaderType));
				std::string shaderSource = this->assetLibrary->getAsset(shaderFile)->toString();
				shader->setSourceCode(shaderSource);
				shader->compile();

			} else if (name == "program") {
				std::string programName = child.getAttribute("name");

				ShaderProgram *program = this->shaderLibrary->createProgram(programName);

				for (xml::Node moduleNode : child.getChilds("module")) {
					std::string shaderName = moduleNode.getAttribute("ref-name");

					Shader *shader = this->shaderLibrary->getShader(shaderName);
					program->addShader(shader);
				}
				program->link();
			} else {
				EXENG_THROW_EXCEPTION("Tag '" + name + "' not known.");
			}
		}
	}

	MaterialFormat parseMaterialFormat(const xml::Node &node) {
		std::vector<MaterialAttrib> attribs;

		for (const xml::Node &child : node.getChilds("attribute")) {
			MaterialAttrib attrib;
			attrib.name = child.getAttribute("name");
			attrib.dimension = getDimension(child.getAttribute("type"));
			attrib.dataType = getDataType(child.getAttribute("type"));

			attribs.push_back(attrib);
		}

		return MaterialFormat(attribs);
	}

	template<typename Type>
	void fillMaterialAttribute(Material *material, const int attribIndex, const std::string &content) {
		Vector4f values = parseVector<Type, 4>(content);
		material->setAttribute(attribIndex, values.data, 4*sizeof(Type));
	}

	template<typename Type, int Size>
	Vector<Type, Size> parseVector(const std::string &content) {
		std::vector<std::string> splitted;
		boost::split(splitted, content, boost::is_any_of(" "));

		Vector<Type, Size> values(Type(0)) ;
		for (int i=0; i<static_cast<int>(splitted.size()); ++i) {
			values[i] = boost::lexical_cast<Type>(splitted[i]);
		}

		return values;
	}

	void parseMaterialAttribute(const xml::Node &node, Material *material) {
		const std::string attribName = node.getAttribute("ref-name");
		const std::string content = node.getContent();
		const int attribIndex = material->getFormat()->getAttribIndex(attribName);

		DataType::Enum dataType = material->getFormat()->getAttrib(attribIndex)->dataType;

		if (dataType == DataType::Int32) {
			fillMaterialAttribute<int>(material, attribIndex, content);
		} else if (dataType == DataType::Float32) {
			fillMaterialAttribute<float>(material, attribIndex, content);
		} else {
			EXENG_THROW_EXCEPTION("parseMaterialAttribute: Unsupported material datatype");
		}
	}

	void parseMaterial(const xml::Node &node) {
		std::string name = node.getAttribute("name");

		Material *material = this->materialLibrary->createMaterial(name, nullptr);

		for (const xml::Node &child : node.getChilds()) {
			std::string attributeName = child.getName();

			if (attributeName == "attribute") {
				this->parseMaterialAttribute(child, material);
			} else if (attributeName == "program") {
				std::string programName = child.getAttribute("ref-name");
				ShaderProgram *program = this->shaderLibrary->getProgram(programName);
				material->setShaderProgram(program);
			}
		}
	}

	void parseMaterialLibrary(const xml::Node &node) {
		for (const xml::Node &child : node.getChilds()) {
			std::string name = child.getName();

			if (name == "material-format") {
				MaterialFormat materialFormat = this->parseMaterialFormat(child);
				this->materialLibrary->initialize(materialFormat);
			} else if (name == "material") {
				this->parseMaterial(child);
			}
		}
	}

	MeshSubsetPtr parseGeometryMeshSubset(const xml::Node &node, const VertexFormat &format) {
		MeshSubsetPtr meshSubset;

		for (const xml::Node &child : node.getChilds()) {
			std::string name = child.getName();

			if (name == "mesh-subset-generator") {
				std::string type = child.getAttribute("type");

				GeometryGeneratorPtr generator;

				if (type == "box") {
					Vector3f center = parseVector<float, 3>(child.getAttribute("center"));
					Vector3f size = parseVector<float, 3>(child.getAttribute("size"));

					generator.reset( new BoxGeometryGenerator(center, size));
				}

				if (!generator) {
					EXENG_THROW_EXCEPTION("Generator '" + type + "' not known.");
				}

				HeapBufferPtr vbuffer = generator->generateVertexBuffer(format);
				HeapBufferPtr ibuffer = generator->generateIndexBuffer();

				BufferPtr vertexBuffer  = this->driver->createVertexBuffer(vbuffer.get());
				BufferPtr indexBuffer  = this->driver->createIndexBuffer(ibuffer.get());
				Primitive::Enum primitive = Primitive::TriangleList;

				meshSubset = this->driver->createMeshSubset(std::move(vertexBuffer), std::move(indexBuffer), format);
				meshSubset->setPrimitive(primitive);

			} else if (name == "material") {
				std::string materialName = child.getAttribute("ref-name");
				Material *material = this->materialLibrary->getMaterial(materialName);

				meshSubset->setMaterial(material);
			}
		}

		return meshSubset;
	}

	MeshPtr parseGeometryMesh(const xml::Node &node, const VertexFormat &format) {
		std::string source = node.getAttribute("source");
		MeshPtr mesh;

		if (source == "generator") {
			std::vector<MeshSubsetPtr> subsets;

			for (xml::Node child : node.getChilds("mesh-subset")) {
				MeshSubsetPtr meshSubset = this->parseGeometryMeshSubset(child, format);
				subsets.push_back(std::move(meshSubset));
			}

			mesh = std::make_unique<Mesh>(std::move(subsets));
		} else {
			EXENG_THROW_EXCEPTION("parseGeometryMesh: Not supported source '" +  source + "'.");
		}
		
		return mesh;
	}
	
	void parseGeometryLibrary(const xml::Node &node) {
		VertexFormat format;

		for (xml::Node child : node.getChilds()) {
			if (child.getName() == "vertex-format") {
				int fieldIndex = 0;

				for (xml::Node attributeNode : child.getChilds("attribute")) {
					std::string attributeType = attributeNode.getAttribute("type");
					std::string use = attributeNode.getAttribute("use");
					std::string name = attributeNode.getAttribute("name");

					VertexField &field = format.fields[fieldIndex];
					field.dataType = AssetsLoader::getDataType(attributeType);
					field.count = AssetsLoader::getDimension(attributeType);
					field.attribute = AssetsLoader::getVertexAttrib(use);

					fieldIndex++;
				}
			} else if (child.getName() == "geometry") {

				if (child.getAttribute("type") == "mesh") {
					GeometryPtr geometry = this->parseGeometryMesh(child.getChild("mesh"), format);
					this->geometryLibrary->addGeometry(child.getAttribute("name"), std::move(geometry));
				}
			}
		}
	}

	void parseSceneNode(xml::Node &node, SceneNode *sceneNode) {
		// parse scene node
		Matrix4f transform = zero<float, 4, 4>();

		// transformation
		for (xml::Node transformNode : node.getChild("transformation").getChilds()) {
			std::string name = transformNode.getName();

			if (name == "identity") {
				transform = identity<float, 4>();
			} else if (name == "translate") {
				Vector3f position = parseVector<float, 3>(transformNode.getContent());
				transform *= translate<float>(position);
			} else if (name == "rotate") {
				Vector3f axis = parseVector<float, 3>(transformNode.getAttribute("axis"));
				float angle = boost::lexical_cast<float>(transformNode.getContent());
				transform *= rotate<float>(angle, axis);
			} else if (name == "scale") {
				Vector3f scaling = parseVector<float, 3>(transformNode.getContent());
				transform *= scale<float, 4>(scaling);
			}
		}

		sceneNode->setTransform(transform);

		// geometries
		for (xml::Node dataNode : node.getChilds("data")) {
			if (dataNode.getAttribute("type") ==  "geometry") {
				std::string geometryName = dataNode.getAttribute("ref-name");
				Geometry *geometry = this->geometryLibrary->getGeometry(geometryName);

				sceneNode->setData(geometry);
			}
		}

		// parse scene node childs
		for (xml::Node child : node.getChilds("node")) {
			SceneNode *childNode = sceneNode->addChild(child.getAttribute("name"));
			this->parseSceneNode(child, childNode);
		}
	}

	void parseScene(xml::Node &node) {
		for (xml::Node child : node.getChilds()) {
			std::string name = child.getName();

			if (name == "background") {
				Vector4f color = parseVector<float, 4>(child.getChild("color").getContent());
				this->scene->setBackColor(color);
			} else if (name == "camera-collection") {

				for (xml::Node cameraNode : child.getChilds("camera")) {
					// TODO: Use the camera name.
					std::string cameraName = cameraNode.getAttribute("name");

					// view
					xml::Node viewNode = cameraNode.getChild("view").getChild("look-at");

					Vector3f position = parseVector<float, 3>(viewNode.getAttribute("position"));
					Vector3f lookAt = parseVector<float, 3>(viewNode.getAttribute("look-at"));
					Vector3f up = parseVector<float, 3>(viewNode.getAttribute("up"));

					Camera *camera = this->scene->createCamera();
					camera->setPosition(position);
					camera->setLookAt(lookAt);
					camera->setUp(up);

					// projection
					// TODO: add projection to the camera node
					xml::Node perspectiveNode = cameraNode.getChild("projection").getChild("perspective");

					float fov = boost::lexical_cast<float>(perspectiveNode.getAttribute("fov"));
					float aspect = boost::lexical_cast<float>(perspectiveNode.getAttribute("aspect"));
					float zNear = boost::lexical_cast<float>(perspectiveNode.getAttribute("z-near"));
					float zFar = boost::lexical_cast<float>(perspectiveNode.getAttribute("z-far"));

					// viewport
					xml::Node viewportNode = cameraNode.getChild("viewport");
					Vector2f viewportPosition = parseVector<float, 2>(viewportNode.getAttribute("position"));
					Vector2f viewportSize = parseVector<float, 2>(viewportNode.getAttribute("size"));
					camera->setViewport(Rectf(viewportPosition, viewportPosition + viewportSize));
				}
			} else if (name == "node") {
				SceneNode *sceneNode = this->scene->getRootNode();
				this->parseSceneNode(child, sceneNode);
			} else {
				EXENG_THROW_EXCEPTION("Invalid '" + name + "' node");
			}
		}
	}
	
	void parseAssets(const xml::Node &node) {
		for (xml::Node child : node.getChilds()) {
			if (child.getName() == "shader-library") {
				this->parseShaderLibrary(child);
			} else if (child.getName() == "material-library") {
				this->parseMaterialLibrary(child);
			} else if (child.getName() == "geometry-library") {
				this->parseGeometryLibrary(child);
			} else if (child.getName() == "scene") {
				this->parseScene(child);
			}
		}
	}

private:
	static int getDimension(const std::string &type) {
		if (type == "float") {
			return 1;
		} else if (type == "Vector2f") {
			return 2;
		} else if (type == "Vector3f") {
			return 3;
		} else if (type == "Vector4f") {
			return 4;
		} else if (type == "int") {
			return 1;
		} else if (type == "Vector2i") {
			return 2;
		} else if (type == "Vector3i") {
			return 3;
		} else if (type == "Vector4i") {
			return 4;
		} else {
			EXENG_THROW_EXCEPTION("Unknown type: " + type);
		}
	}

	static ShaderType::Enum getShaderType(const std::string &shaderType) {
		if (shaderType == "vertex") {
			return ShaderType::Vertex;
		} else if (shaderType == "fragment") {
			return ShaderType::Fragment;
		} else {
			EXENG_THROW_EXCEPTION("Unknown '" + shaderType + "' shader type.");
		}
	}

	static DataType::Enum getDataType(const std::string &type) {
		if (type == "float") {
			return DataType::Float32;
		} else if (type == "Vector2f") {
			return DataType::Float32;
		} else if (type == "Vector3f") {
			return DataType::Float32;
		} else if (type == "Vector4f") {
			return DataType::Float32;
		} else if (type == "int") {
			return DataType::Int32;
		} else if (type == "Vector2i") {
			return DataType::Int32;
		} else if (type == "Vector3i") {
			return DataType::Int32;
		} else if (type == "Vector4i") {
			return DataType::Int32;
		} else {
			EXENG_THROW_EXCEPTION("Unknown '" + type + "' data type.");
		}
	}

	static VertexAttrib::Enum getVertexAttrib(const std::string &attributeUse) {
		if (attributeUse == "position") {
			return VertexAttrib::Position;
		} else if (attributeUse == "normal") {
			return VertexAttrib::Normal;
		} else if (attributeUse == "texture-coordinate") {
			return VertexAttrib::TexCoord;
		} else {
			EXENG_THROW_EXCEPTION("Unknown '" + attributeUse + "' vertex attribute.");
		}
	}

private:
	AssetLibrary *assetLibrary = nullptr;
	GraphicsDriver *driver = nullptr;
	MaterialLibrary *materialLibrary = nullptr;
	GeometryLibrary *geometryLibrary = nullptr;
	ShaderLibrary *shaderLibrary = nullptr;
	Scene *scene = nullptr;
};

class GraphicsNodeRenderer {
public:
	GraphicsNodeRenderer() {}
	~GraphicsNodeRenderer() {}

	void setGraphicsDriver(GraphicsDriver *driver) {
		this->driver = driver;
	}

	GraphicsDriver* getGraphicsDriver() {
		return this->driver;
	}

	const GraphicsDriver* getGraphicsDriver() const {
		return this->driver;
	}

	void setTransform(const Matrix4f &transform) {
		this->transform = transform;
	}

	void prepareCamera(const Camera *camera) {
		
	}

	void renderNodeData(const SceneNodeData *data) {
		TypeInfo info = data->getTypeInfo();

		if (info == TypeId<Mesh>()) {
			const Mesh *mesh = static_cast<const Mesh*>(data);

			for (int i=0; i<mesh->getSubsetCount(); ++i) {
				const MeshSubset *subset = mesh->getSubset(i);

				this->driver->setMaterial(subset->getMaterial());
				this->driver->setMeshSubset(subset);
				this->driver->getModernModule()->setProgramGlobal("WorldTransform", this->transform);
				this->driver->render(subset->getPrimitive(), subset->getVertexCount());
			}
		} else {
			EXENG_THROW_EXCEPTION("Unsupported Geometry type.");
		}

	}

private:
	GraphicsDriver* driver = nullptr;
	Matrix4f transform;
};

class Demo01 : public GraphicsApplication, public IEventHandler {
public:
	std::string getPluginPath() {
#if defined(EXENG_UNIX)
        return "../../plugins/libexeng.graphics.gl3/";
#else
#  if defined (EXENG_DEBUG)
		return "../../bin/Debug/";
#  else 
		return "../../bin/Release/";
#  endif
#endif
	}

    virtual void initialize(int argc, char **argv) override {
		this->getPluginManager()->setPluginPath(this->getPluginPath());
        this->getPluginManager()->loadPlugin("exeng.graphics.gl3");
		
        this->graphicsDriver = this->getGraphicsManager()->createDriver();
        this->graphicsDriver->addEventHandler(this);
        this->graphicsDriver->initialize();

		this->scene = std::make_unique<Scene>();

		this->getMeshManager()->setGraphicsDriver(this->graphicsDriver.get());
		
		this->assetLibrary = std::make_unique<AssetLibrary>();
		this->assetLibrary->addAsset("Vertex.glsl",  std::make_unique<StaticBuffer>((void*)vertex_glsl_data, vertex_glsl_size));
		this->assetLibrary->addAsset("Fragment.glsl",  std::make_unique<StaticBuffer>((void*)fragment_glsl_data, fragment_glsl_size));

		this->materialLibrary = std::make_unique<MaterialLibrary>();
		this->geometryLibrary = std::make_unique<GeometryLibrary>();
		this->shaderLibrary = std::make_unique<ShaderLibrary>(this->graphicsDriver.get());
		
		// loads scene, objects and materials
		AssetsLoader loader(this->assetLibrary.get(), this->graphicsDriver.get(), this->getMaterialLibrary(), this->getGeometryLibrary(), this->getShaderLibrary(), this->scene.get());
		loader.loadAssets();

		this->camera = this->scene->getCamera(0);

		// create scene renderer
		auto sceneRenderer = new GenericSceneRenderer<GraphicsNodeRenderer>();
		sceneRenderer->setScene(this->scene.get());
		sceneRenderer->setGraphicsDriver(this->graphicsDriver.get());

		this->sceneRenderer.reset(sceneRenderer);
    }
    
    virtual ApplicationStatus::Enum getApplicationStatus() const override {
        return this->status;
    }
    
    virtual void pollEvents() override {
        this->graphicsDriver->pollEvents();
    }
    
    virtual void update(float seconds) override {
		this->angle += (60.0f * seconds);
    }
    
	virtual void render() {
		this->graphicsDriver->beginFrame({0.0f, 0.0f, 1.0f, 1.0f}, ClearFlags::ColorDepth);
		this->sceneRenderer->render(this->camera);
		this->graphicsDriver->endFrame();
	}

    virtual void render2() {
		// Camera Data
		Vector3f position = camera->getPosition();
		Vector3f lookAt = camera->getLookAt();
		Vector3f up = camera->getUp();
		DisplayMode mode = this->graphicsDriver->getDisplayMode();
		float aspect = static_cast<float>(mode.size.width) / static_cast<float>(mode.size.height);

		Matrix4f projMatrix = perspective<float>( rad(60.0f), aspect, 0.1f, 1000.0f);
		Matrix4f viewMatrix = lookat<float>(position, lookAt, up);
		Matrix4f modelMatrix = identity<float, 4>();
		modelMatrix *= rotatex<float>(rad(this->angle));
		modelMatrix *= rotatey<float>(rad(this->angle));
		modelMatrix *= rotatez<float>(rad(this->angle));
		// modelMatrix *= scale<float, 4>({5.0f, 5.0f, 5.0f});

		Matrix4f mvpMatrix = projMatrix * viewMatrix * modelMatrix;

		// Matrix4f cameraTransform = lookat<float>(position, lookAt, up);
		// Matrix4f cameraTransform = identity<float, 4>();

		this->graphicsDriver->beginFrame({0.0f, 0.0f, 1.0f, 1.0f}, ClearFlags::ColorDepth);

		Rectf viewport({0.0f, 0.0f}, Vector2f{(float)mode.size.width, (float)mode.size.height});
		
		this->graphicsDriver->setViewport(viewport);

		// Mesh Data
		Mesh *mesh = static_cast<Mesh*>(this->geometryLibrary->getGeometry("box"));

		for (int i=0; i<mesh->getSubsetCount(); i++) {
			MeshSubset *subset = mesh->getSubset(i);

			//const Vertex *vertices = (const Vertex*)subset->getBuffer(0)->getPointer();
			//for (int vertexIndex=0; vertexIndex<subset->getVertexCount(); ++vertexIndex) {
			//	std::cout << vertices[vertexIndex].coord << "; ";
			//	std::cout << vertices[vertexIndex].normal << "; ";
			//	std::cout << vertices[vertexIndex].texCoord;
			//	std::cout << std::endl;
			//}
			//std::cout << std::endl;

			this->graphicsDriver->setMaterial(subset->getMaterial());
			this->graphicsDriver->getModernModule()->setProgramGlobal("WorldTransform", mvpMatrix);
			this->graphicsDriver->setMeshSubset(subset);
			this->graphicsDriver->render(subset->getPrimitive(), subset->getVertexCount());
		}

		this->graphicsDriver->endFrame();

		/*
		this->graphicsDriver->beginFrame({0.0f, 0.0f, 1.0f, 1.0f}, ClearFlags::ColorDepth);
		this->sceneRenderer->render(this->camera);
		this->graphicsDriver->endFrame();
		*/
    }
    
    virtual void handleEvent(const EventData &data) override {
        const InputEventData &inputData = data.cast<InputEventData>();
        
        if (inputData.check(ButtonStatus::Press, ButtonCode::KeyEsc)) {
            this->status = ApplicationStatus::Terminated;
        }
    }

	MaterialLibrary* getMaterialLibrary() {
		return this->materialLibrary.get();
	}

	const MaterialLibrary* getMaterialLibrary() const {
		return this->materialLibrary.get();
	}

	GeometryLibrary* getGeometryLibrary() {
		return this->geometryLibrary.get();
	}

	const GeometryLibrary* getGeometryLibrary() const {
		return this->geometryLibrary.get();
	}

	ShaderLibrary* getShaderLibrary() {
		return this->shaderLibrary.get();
	}

	const ShaderLibrary* getShaderLibrary() const {
		return this->shaderLibrary.get();
	}

private:
    GraphicsDriverPtr graphicsDriver;
	SceneNodeAnimatorPtr animator;
	ShaderLibraryPtr shaderLibrary;
	GeometryLibraryPtr geometryLibrary;
	MaterialLibraryPtr materialLibrary;
	AssetLibraryPtr assetLibrary;
	ScenePtr scene;
	SceneRendererPtr sceneRenderer;

	Camera *camera = nullptr;
	ShaderProgram *program = nullptr;
	Material *material = nullptr;
    ApplicationStatus::Enum status = ApplicationStatus::Running;

	float angle = 0.0f;
};

int main(int argc, char **argv) {
    return Application::execute<Demo01>(argc, argv);
}
