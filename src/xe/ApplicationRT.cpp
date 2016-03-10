
#include "ApplicationRT.hpp"

#include <xe/Timer.hpp>

namespace xe {

	int ApplicationRT::run(int argc, char **argv) {
		std::uint32_t last_time = xe::Timer::getTime();

		this->initialize(argc, argv);

		while (true) {
			float seconds = (xe::Timer::getTime() - last_time) * 0.0001f;

			last_time = xe::Timer::getTime();

			this->doEvents();
			this->update(seconds);
			this->render();
		}

		this->terminate();
	}
}

//
//#include "GraphicsApplication.hpp"
//
//#include <boost/lexical_cast.hpp>
//#include <boost/algorithm/string.hpp>
//#include <libxml/parser.h>
//#include <libxml/tree.h>
//#include <xe/Exception.hpp>
//#include <xe/HeapBuffer.hpp>
//#include <xe/gfx/TextureManager.hpp>
//#include <xe/gfx/MeshSubsetGenerator.hpp>
//#include <xe/gfx/Mesh.hpp>
//#include <xe/gfx/MeshManager.hpp>
//#include <xe/sg/SceneRendererGeneric.hpp>
/*
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/ShaderLibrary.hpp>
#include <xe/gfx/MaterialLibrary.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/sg/Scene.hpp>
#include <xe/sg/AssetsLibrary.hpp>
#include <xe/sg/GeometryLibrary.hpp>
#include <xe/sg/SceneRenderer.hpp>
*/


//
//#include "xmlpp/Document.hpp"
//
//namespace xe { namespace fw {
//
//	using namespace xe::gfx;
//	using namespace xe::sg;
//
//	class AssetsLoader {
//	public:
//		AssetsLoader() {}
//
//		void setAssetLibrary(AssetLibrary *assetLibrary) {
//			this->assetLibrary = assetLibrary;
//		}
//
//		void setGraphicsDriver(GraphicsDriver *driver) {
//			this->driver = driver;
//		}
//
//		void setMaterialLibrary(MaterialLibrary *materialLibrary) {
//			this->materialLibrary = materialLibrary;
//		}
//
//		void setGeometryLibrary(GeometryLibrary *geometryLibrary) {
//			this->geometryLibrary = geometryLibrary; 
//		}
//
//		void setShaderLibrary(ShaderLibrary *shaderLibrary) {
//			this->shaderLibrary = shaderLibrary;
//		}
//
//		void setScene(Scene *scene) {
//			this->scene = scene;
//		}
//
//		void setTextureManager(TextureManager *textureManager) {
//			this->textureManager = textureManager;
//		}
//
//		void loadAssets(Buffer* assetsXmlBuffer) {
//			if (!assetsXmlBuffer) {
//				return;
//			}
//
//			const char* assetsXmlData = (const char*)assetsXmlBuffer->getPointer();
//			const int assetsXmlSize = assetsXmlBuffer->getSize();
//
//			xmlDoc *document = ::xmlReadMemory(assetsXmlData, assetsXmlSize, "", nullptr, 0);
//			if (!document) {
//				EXENG_THROW_EXCEPTION("Can't read memory for XML parsing.");
//			}
//
//			xmlpp::NodeRef node = ::xmlDocGetRootElement(document);
//
//			if (node.getName() == "assets") {
//				this->parseAssets(node);
//			} else {
//				EXENG_THROW_EXCEPTION("'assets' root node doesn't exists.");
//			}
//
//			::xmlFreeDoc(document);
//			::xmlCleanupParser();
//		}
//
//	private:
//		void parseShaderLibrary(const xmlpp::NodeRef &node) {
//			for (xmlpp::NodeRef child : node.getChilds()) {
//				std::string name = child.getName();
//
//				if (name == "shader") {
//					std::string shaderName = child.getAttribute("name");
//					std::string shaderType = child.getAttribute("type");
//					std::string shaderFile = child.getAttribute("file");
//
//					Shader *shader = this->shaderLibrary->createShader(shaderName, getShaderType(shaderType));
//					std::string shaderSource = this->assetLibrary->getAsset(shaderFile)->toString();
//					shader->setSourceCode(shaderSource);
//					shader->compile();
//
//				} else if (name == "program") {
//					std::string programName = child.getAttribute("name");
//
//					ShaderProgram *program = this->shaderLibrary->createProgram(programName);
//
//					for (xmlpp::NodeRef moduleNode : child.getChilds("module")) {
//						std::string shaderName = moduleNode.getAttribute("ref-name");
//
//						Shader *shader = this->shaderLibrary->getShader(shaderName);
//						program->addShader(shader);
//					}
//					program->link();
//				} else {
//					EXENG_THROW_EXCEPTION("Tag '" + name + "' not known.");
//				}
//			}
//		}
//
//		MaterialFormat parseMaterialFormat(const xmlpp::NodeRef &node) {
//			std::vector<MaterialAttrib> attribs;
//
//			for (const xmlpp::NodeRef &child : node.getChilds("attribute")) {
//				MaterialAttrib attrib;
//				attrib.name = child.getAttribute("name");
//				attrib.dimension = getDimension(child.getAttribute("type"));
//				attrib.dataType = getDataType(child.getAttribute("type"));
//
//				attribs.push_back(attrib);
//			}
//
//			return MaterialFormat(attribs);
//		}
//
//		template<typename Type>
//		void fillMaterialAttribute(Material *material, const int attribIndex, const std::string &content) {
//			Vector4f values = parseVector<Type, 4>(content);
//			material->setAttribute(attribIndex, values.data, 4*sizeof(Type));
//		}
//
//		template<typename Type, int Size>
//		Vector<Type, Size> parseVector(const std::string &content) {
//			std::vector<std::string> splitted;
//			boost::split(splitted, content, boost::is_any_of(" "));
//
//			Vector<Type, Size> values(Type(0)) ;
//			for (int i=0; i<static_cast<int>(splitted.size()); ++i) {
//				values[i] = boost::lexical_cast<Type>(splitted[i]);
//			}
//
//			return values;
//		}
//
//
//
//		void parseMaterialAttribute(const xmlpp::NodeRef &node, Material *material) {
//			const std::string attribName = node.getAttribute("ref-name");
//			const std::string content = node.getContent();
//			const int attribIndex = material->getFormat()->getAttribIndex(attribName);
//
//			DataType::Enum dataType = material->getFormat()->getAttrib(attribIndex)->dataType;
//
//			if (dataType == DataType::Int32) {
//				fillMaterialAttribute<int>(material, attribIndex, content);
//			} else if (dataType == DataType::Float32) {
//				fillMaterialAttribute<float>(material, attribIndex, content);
//			} else {
//				EXENG_THROW_EXCEPTION("parseMaterialAttribute: Unsupported material datatype");
//			}
//		}
//
//		/*
//		<material>
//			<material-layers>
//                <material-layer>
//                    <texture source="generator">
//                        <texture-generator type="checkerboard" size="256 256" table-size="8 8"/>
//                    </texture>
//                </material-layer>
//            </material-layers>
//		</material>
//		*/
//
//		void parseMaterialLayers(const xmlpp::NodeRef &node, Material *material) {
//			int layerIndex = 0;
//
//			for (const xmlpp::NodeRef &child : node.getChilds("material-layer")) {
//				Texture *texture = nullptr;
//
//				std::string childName = child.getName();
//				xmlpp::NodeRefList textureNodes = child.getChilds("texture");
//
//				if (textureNodes.size() > 1) {
//					EXENG_THROW_EXCEPTION("Only one 'texture' tag is supported per layer");
//				} else if (textureNodes.size() == 1) {
//					xmlpp::NodeRef textureNode = *textureNodes.begin();
//
//					std::string textureName = textureNode.getAttribute("name");
//					std::string textureSource = textureNode.getAttribute("source");
//					
//					if (textureSource == "generator") {
//						xmlpp::NodeRef generatorNode = textureNode.getChild("texture-generator");
//						std::string generatorType = generatorNode.getAttribute("type");
//						
//						if (generatorType == "checkerboard") {
//							Vector2i size = parseVector<int, 2>(generatorNode.getAttribute("size"));
//							Vector2i grid = parseVector<int, 2>(generatorNode.getAttribute("grid"));
//
//							texture = this->textureManager->generateCheckerboard(textureName, size, grid);
//						} else {
//							EXENG_THROW_EXCEPTION("Unknown texture generator '" + generatorType + "'.");
//						}
//					} else {
//						EXENG_THROW_EXCEPTION("Unknown texture source '" + textureSource + "'.");
//					}
//				}
//
//				material->getLayer(layerIndex)->setTexture(texture);
//				++layerIndex;
//			}
//		}
//
//		void parseMaterial(const xmlpp::NodeRef &node) {
//			std::string name = node.getAttribute("name");
//
//			Material *material = this->materialLibrary->createMaterial(name, nullptr);
//
//			for (const xmlpp::NodeRef &child : node.getChilds()) {
//				std::string attributeName = child.getName();
//
//				if (attributeName == "attribute") {
//					this->parseMaterialAttribute(child, material);
//
//				} else if (attributeName == "program") {
//					std::string programName = child.getAttribute("ref-name");
//					ShaderProgram *program = this->shaderLibrary->getProgram(programName);
//					material->setShaderProgram(program);
//
//				} else if (attributeName == "material-layers") {
//					parseMaterialLayers(child, material);
//				}
//			}
//		}
//
//		void parseMaterialLibrary(const xmlpp::NodeRef &node) {
//			for (const xmlpp::NodeRef &child : node.getChilds()) {
//				std::string name = child.getName();
//
//				if (name == "material-format") {
//					MaterialFormat materialFormat = this->parseMaterialFormat(child);
//					// this->materialLibrary->initialize(materialFormat);
//				} else if (name == "material") {
//					this->parseMaterial(child);
//				}
//			}
//		}
//
//		MeshSubsetPtr parseGeometryMeshSubset(const xmlpp::NodeRef &node, const VertexFormat &format) {
//			MeshSubsetPtr meshSubset;
//
//			for (const xmlpp::NodeRef &child : node.getChilds()) {
//				std::string name = child.getName();
//
//				if (name == "mesh-subset-generator") {
//					std::string type = child.getAttribute("type");
//
//					std::unique_ptr<MeshSubsetGenerator> generator;
//
//					if (type == "box") {
//						Vector3f center = parseVector<float, 3>(child.getAttribute("center"));
//						Vector3f size = parseVector<float, 3>(child.getAttribute("size"));
//
//						// generator = std::make_unique<BoxGenerator<StandardVertex>>(center, size);
//					}
//
//					if (!generator) {
//						EXENG_THROW_EXCEPTION("Generator '" + type + "' not known.");
//					}
//
//					HeapBufferPtr vbuffer /*= generator->generateVertexBuffer()*/;
//					HeapBufferPtr ibuffer /*= generator->generateIndexBuffer()*/;
//
//					BufferPtr vertexBuffer  = this->driver->createVertexBuffer(vbuffer.get());
//					BufferPtr indexBuffer  = this->driver->createIndexBuffer(ibuffer.get());
//					Primitive::Enum primitive = Primitive::TriangleList;
//
//					meshSubset = this->driver->createMeshSubset(std::move(vertexBuffer), std::move(indexBuffer), format);
//					meshSubset->setPrimitive(primitive);
//
//				} else if (name == "material") {
//					std::string materialName = child.getAttribute("ref-name");
//					Material *material = this->materialLibrary->getMaterial(materialName);
//
//					meshSubset->setMaterial(material);
//				}
//			}
//
//			return meshSubset;
//		}
//
//		MeshPtr parseGeometryMesh(const xmlpp::NodeRef &node, const VertexFormat &format) {
//			std::string source = node.getAttribute("source");
//			MeshPtr mesh;
//
//			if (source == "generator") {
//				std::vector<MeshSubsetPtr> subsets;
//
//				for (xmlpp::NodeRef child : node.getChilds("mesh-subset")) {
//					MeshSubsetPtr meshSubset = this->parseGeometryMeshSubset(child, format);
//					subsets.push_back(std::move(meshSubset));
//				}
//
//				mesh = std::make_unique<Mesh>(std::move(subsets));
//			} else {
//				EXENG_THROW_EXCEPTION("parseGeometryMesh: Not supported source '" +  source + "'.");
//			}
//		
//			return mesh;
//		}
//	
//		void parseGeometryLibrary(const xmlpp::NodeRef &node) {
//			VertexFormat format;
//
//			for (xmlpp::NodeRef child : node.getChilds()) {
//				if (child.getName() == "vertex-format") {
//					int fieldIndex = 0;
//
//					for (xmlpp::NodeRef attributeNode : child.getChilds("attribute")) {
//						std::string attributeType = attributeNode.getAttribute("type");
//						std::string use = attributeNode.getAttribute("use");
//						std::string name = attributeNode.getAttribute("name");
//
//						VertexField &field = format.fields[fieldIndex];
//						field.dataType = AssetsLoader::getDataType(attributeType);
//						field.count = AssetsLoader::getDimension(attributeType);
//						field.attribute = AssetsLoader::getVertexAttrib(use);
//
//						fieldIndex++;
//					}
//				} else if (child.getName() == "geometry") {
//
//					if (child.getAttribute("type") == "mesh") {
//						GeometryPtr geometry /*= this->parseGeometryMesh(child.getChild("mesh"), format)*/;
//						this->geometryLibrary->addGeometry(child.getAttribute("name"), std::move(geometry));
//					}
//				}
//			}
//		}
//
//		void parseSceneNode(xmlpp::NodeRef &node, SceneNode *sceneNode) {
//			// parse scene node
//			Matrix4f transform = zero<float, 4, 4>();
//
//			// transformation
//			for (xmlpp::NodeRef transformNode : node.getChild("transformation").getChilds()) {
//				std::string name = transformNode.getName();
//
//				if (name == "identity") {
//					transform = identity<float, 4>();
//				} else if (name == "translate") {
//					Vector3f position = parseVector<float, 3>(transformNode.getContent());
//					transform *= translate<float>(position);
//				} else if (name == "rotate") {
//					Vector3f axis = parseVector<float, 3>(transformNode.getAttribute("axis"));
//					float angle = boost::lexical_cast<float>(transformNode.getContent());
//					transform *= rotate<float>(angle, axis);
//				} else if (name == "scale") {
//					Vector3f scaling = parseVector<float, 3>(transformNode.getContent());
//					transform *= scale<float, 4>(scaling);
//				}
//			}
//
//			sceneNode->setTransform(transform);
//
//			// geometries
//			for (xmlpp::NodeRef dataNode : node.getChilds("data")) {
//				if (dataNode.getAttribute("type") ==  "geometry") {
//					std::string geometryName = dataNode.getAttribute("ref-name");
//					Geometry *geometry = this->geometryLibrary->getGeometry(geometryName);
//
//					// sceneNode->setData(geometry);
//				}
//			}
//
//			// parse scene node childs
//			for (xmlpp::NodeRef child : node.getChilds("node")) {
//				SceneNode *childNode = sceneNode->addChild(child.getAttribute("name"));
//				this->parseSceneNode(child, childNode);
//			}
//		}
//
//		void parseScene(xmlpp::NodeRef &node) {
//			for (xmlpp::NodeRef child : node.getChilds()) {
//				std::string name = child.getName();
//
//				if (name == "background") {
//					Vector4f color = parseVector<float, 4>(child.getChild("color").getContent());
//					this->scene->setBackColor(color);
//				} else if (name == "camera-collection") {
//
//					for (xmlpp::NodeRef cameraNode : child.getChilds("camera")) {
//						// TODO: Use the camera name.
//						std::string cameraName = cameraNode.getAttribute("name");
//
//						// view
//						xmlpp::NodeRef viewNode = cameraNode.getChild("view").getChild("look-at");
//
//						Vector3f position = parseVector<float, 3>(viewNode.getAttribute("position"));
//						Vector3f lookAt = parseVector<float, 3>(viewNode.getAttribute("look-at"));
//						Vector3f up = parseVector<float, 3>(viewNode.getAttribute("up"));
//
//						Camera *camera = this->scene->createCamera();
//						camera->setPosition(position);
//						camera->setLookAt(lookAt);
//						camera->setUp(up);
//
//						// projection
//						// TODO: add projection to the camera node
//						xmlpp::NodeRef perspectiveNode = cameraNode.getChild("projection").getChild("perspective");
//
//						float fov = boost::lexical_cast<float>(perspectiveNode.getAttribute("fov"));
//						float aspect = boost::lexical_cast<float>(perspectiveNode.getAttribute("aspect"));
//						float zNear = boost::lexical_cast<float>(perspectiveNode.getAttribute("z-near"));
//						float zFar = boost::lexical_cast<float>(perspectiveNode.getAttribute("z-far"));
//
//						// viewport
//						xmlpp::NodeRef viewportNode = cameraNode.getChild("viewport");
//						Vector2f viewportPosition = parseVector<float, 2>(viewportNode.getAttribute("position"));
//						Vector2f viewportSize = parseVector<float, 2>(viewportNode.getAttribute("size"));
//						camera->setViewport(Rectf(viewportPosition, viewportPosition + viewportSize));
//					}
//				} else if (name == "node") {
//					SceneNode *sceneNode = this->scene->getRootNode();
//					this->parseSceneNode(child, sceneNode);
//				} else {
//					EXENG_THROW_EXCEPTION("Invalid '" + name + "' node");
//				}
//			}
//		}
//	
//		void parseAssets(const xmlpp::NodeRef &node) {
//			for (xmlpp::NodeRef child : node.getChilds()) {
//				if (child.getName() == "shader-library") {
//					this->parseShaderLibrary(child);
//				} else if (child.getName() == "material-library") {
//					this->parseMaterialLibrary(child);
//				} else if (child.getName() == "geometry-library") {
//					this->parseGeometryLibrary(child);
//				} else if (child.getName() == "scene") {
//					this->parseScene(child);
//				}
//			}
//		}
//
//	private:
//		static int getDimension(const std::string &type) {
//			if (type == "float") {
//				return 1;
//			} else if (type == "Vector2f") {
//				return 2;
//			} else if (type == "Vector3f") {
//				return 3;
//			} else if (type == "Vector4f") {
//				return 4;
//			} else if (type == "int") {
//				return 1;
//			} else if (type == "Vector2i") {
//				return 2;
//			} else if (type == "Vector3i") {
//				return 3;
//			} else if (type == "Vector4i") {
//				return 4;
//			} else {
//				EXENG_THROW_EXCEPTION("Unknown type: " + type);
//			}
//		}
//
//		static ShaderType::Enum getShaderType(const std::string &shaderType) {
//			if (shaderType == "vertex") {
//				return ShaderType::Vertex;
//			} else if (shaderType == "fragment") {
//				return ShaderType::Fragment;
//			} else {
//				EXENG_THROW_EXCEPTION("Unknown '" + shaderType + "' shader type.");
//			}
//		}
//
//		static DataType::Enum getDataType(const std::string &type) {
//			if (type == "float") {
//				return DataType::Float32;
//			} else if (type == "Vector2f") {
//				return DataType::Float32;
//			} else if (type == "Vector3f") {
//				return DataType::Float32;
//			} else if (type == "Vector4f") {
//				return DataType::Float32;
//			} else if (type == "int") {
//				return DataType::Int32;
//			} else if (type == "Vector2i") {
//				return DataType::Int32;
//			} else if (type == "Vector3i") {
//				return DataType::Int32;
//			} else if (type == "Vector4i") {
//				return DataType::Int32;
//			} else {
//				EXENG_THROW_EXCEPTION("Unknown '" + type + "' data type.");
//			}
//		}
//
//		static VertexAttrib::Enum getVertexAttrib(const std::string &attributeUse) {
//			if (attributeUse == "position") {
//				return VertexAttrib::Position;
//			} else if (attributeUse == "normal") {
//				return VertexAttrib::Normal;
//			} else if (attributeUse == "texture-coordinate") {
//				return VertexAttrib::TexCoord;
//			} else {
//				EXENG_THROW_EXCEPTION("Unknown '" + attributeUse + "' vertex attribute.");
//			}
//		}
//
//	private:
//		AssetLibrary *assetLibrary = nullptr;
//		GraphicsDriver *driver = nullptr;
//		MaterialLibrary *materialLibrary = nullptr;
//		GeometryLibrary *geometryLibrary = nullptr;
//		ShaderLibrary *shaderLibrary = nullptr;
//		Scene *scene = nullptr;
//		TextureManager *textureManager = nullptr;
//	};
//
//	typedef std::unique_ptr<AssetsLoader> AssetsLoaderPtr;
//
//	struct GraphicsApplication::Private {
//		int exitCode = 0;
//		ApplicationStatus::Enum applicationStatus = ApplicationStatus::Terminated;
//
//		GraphicsDriverPtr graphicsDriver;
//		ShaderLibraryPtr shaderLibrary;
//		GeometryLibraryPtr geometryLibrary;
//		MaterialLibraryPtr materialLibrary;
//		AssetLibraryPtr assetLibrary;
//		ScenePtr scene;
//		SceneRendererPtr sceneRenderer;
//	};
//	
//	GraphicsApplication::GraphicsApplication() {
//		this->impl = new GraphicsApplication::Private();
//	}
//
//	GraphicsApplication::~GraphicsApplication() {
//		this->terminate();
//		delete this->impl;
//	}
//
//	void GraphicsApplication::initialize(int argc, char **argv) {
//		// core classes initialization
//		GraphicsDriverPtr graphicsDriver = this->createGraphicsDriver();
//		AssetLibraryPtr assetLibrary = this->createAssetLibrary();
//		ShaderLibraryPtr shaderLibrary = std::make_unique<ShaderLibrary>(graphicsDriver.get());
//		MaterialLibraryPtr materialLibrary/* = std::make_unique<MaterialLibrary>()*/;
//		GeometryLibraryPtr geometryLibrary = std::make_unique<GeometryLibrary>();
//		ScenePtr scene = std::make_unique<Scene>();
//
//		// this->getMeshManager()->setGraphicsDriver(graphicsDriver.get());
//		this->getTextureManager()->setGraphicsDriver(graphicsDriver.get());
//
//		// loads scene, objects and materials
//		BufferPtr assetXmlData = this->getAssetsXmlData();
//
//		AssetsLoaderPtr loader = std::make_unique<AssetsLoader>();
//		loader->setAssetLibrary(assetLibrary.get());
//		loader->setGraphicsDriver(graphicsDriver.get());
//		loader->setMaterialLibrary(materialLibrary.get());
//		loader->setGeometryLibrary(geometryLibrary.get());
//		loader->setShaderLibrary(shaderLibrary.get());
//		loader->setScene(scene.get());
//		loader->setTextureManager(this->getTextureManager());
//		loader->loadAssets(assetXmlData.get());
//
//        // save the core objects
//		this->impl->graphicsDriver = std::move(graphicsDriver);
//		this->impl->shaderLibrary = std::move(shaderLibrary);
//		this->impl->geometryLibrary = std::move(geometryLibrary);
//		this->impl->materialLibrary = std::move(materialLibrary);
//		this->impl->assetLibrary = std::move(assetLibrary);
//		this->impl->scene = std::move(scene);
//		
//		// create the scene renderer
//		SceneRendererPtr sceneRenderer = this->createSceneRenderer(this->getGraphicsDriver());
//		sceneRenderer->setScene(this->getScene());
//
//        this->impl->sceneRenderer = std::move(sceneRenderer);
//
//		// let the application do after-initialization routines
//		if (this->onInitialize()) {
//            this->setApplicationStatus(ApplicationStatus::Running);
//        }
//	}
//
//	void GraphicsApplication::terminate() {
//
//	}
//	
//	void GraphicsApplication::pollEvents() {
//        this->getGraphicsDriver()->pollEvents();
//    }
//    
//    void GraphicsApplication::update(float seconds) {
//    }
//    
//	void GraphicsApplication::render() {
//		// this->getSceneRenderer()->render(this->getScene()->getCamera(0));
//	}
//
//    int GraphicsApplication::run(int argc, char **argv) {
//        uint32_t lastTime = Timer::getTime();
//        uint32_t frameTime = 0;
//        
//        this->initialize(argc, argv);
//        
//        while (this->getApplicationStatus() == ApplicationStatus::Running) {
//            frameTime = Timer::getTime() - lastTime;
//            lastTime = Timer::getTime();
//            
//            this->pollEvents();
//            this->update(frameTime / 1000.0f);
//            this->render();
//        }
//        
//        return this->getExitCode();
//    }
//
//	void GraphicsApplication::setExitCode(int code) {
//		this->impl->exitCode = code;
//	}
//
//    int GraphicsApplication::getExitCode() const {
//		return this->impl->exitCode;
//	}
//
//	void GraphicsApplication::setApplicationStatus(ApplicationStatus::Enum status) {
//		this->impl->applicationStatus = status;
//	}
//
//	ApplicationStatus::Enum GraphicsApplication::getApplicationStatus() const {
//		return this->impl->applicationStatus;
//	}
//
//	GraphicsDriver* GraphicsApplication::getGraphicsDriver() {
//		return this->impl->graphicsDriver.get();
//	}
//
//	ShaderLibrary* GraphicsApplication::getShaderLibrary() {
//		return this->impl->shaderLibrary.get();
//	}
//
//	GeometryLibrary* GraphicsApplication::getGeometryLibrary() {
//		return this->impl->geometryLibrary.get();
//	}
//
//	MaterialLibrary* GraphicsApplication::getMaterialLibrary() {
//		return this->impl->materialLibrary.get();
//	}
//
//	AssetLibrary* GraphicsApplication::getAssetLibrary() {
//		return this->impl->assetLibrary.get();
//	}
//
//	Scene* GraphicsApplication::getScene() {
//		return this->impl->scene.get();
//	}
//	
//	ISceneRenderer* GraphicsApplication::getSceneRenderer() {
//		return this->impl->sceneRenderer.get();
//	}
//
//	const GraphicsDriver* GraphicsApplication::getGraphicsDriver() const {
//		return this->impl->graphicsDriver.get();
//	}
//
//	const ShaderLibrary* GraphicsApplication::getShaderLibrary() const {
//		return this->impl->shaderLibrary.get();
//	}
//
//	const GeometryLibrary* GraphicsApplication::getGeometryLibrary() const {
//		return this->impl->geometryLibrary.get();
//	}
//
//	const MaterialLibrary* GraphicsApplication::getMaterialLibrary() const {
//		return this->impl->materialLibrary.get();
//	}
//
//	const AssetLibrary* GraphicsApplication::getAssetLibrary() const {
//		return this->impl->assetLibrary.get();
//	}
//
//	const Scene* GraphicsApplication::getScene() const {
//		return this->impl->scene.get();
//	}
//
//	const ISceneRenderer* GraphicsApplication::getSceneRenderer() const {
//		return this->impl->sceneRenderer.get();
//	}
//
//    void GraphicsApplication::renderMesh(const Mesh* mesh) {
//        for (int i=0; i<mesh->getSubsetCount(); ++i) {
//            const MeshSubset* subset = mesh->getSubset(i);
//
//            this->getGraphicsDriver()->setMeshSubset(subset);
//            this->getGraphicsDriver()->render(subset->getPrimitive(), 4);
//        }
//    }
//}}
