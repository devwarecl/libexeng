
#include "RayTracerApp2.hpp"

#include <memory>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include <png.h>

#include <exeng/StaticBuffer.hpp>
#include <exeng/system/PluginManager.hpp>
#include <exeng/graphics/GraphicsManager.hpp>
#include <exeng/graphics/TextureManager.hpp>
#include <exeng/scenegraph/MeshManager.hpp>
#include <exeng/scenegraph/GenericSceneRenderer.hpp>

#include "resources/Assets.xml.hpp"
#include "resources/VertexShader.glsl.hpp"
#include "resources/FragmentShader.glsl.hpp"
#include "resources/MultiHardwareTracer.cl.hpp"

#include "renderers/SoftwareRenderer.hpp"
#include "renderers/HardwareRenderer.hpp"

namespace exeng { namespace graphics {

	class TextureLoaderPng : public TextureLoader {
	public:
		TextureLoaderPng() {}
		TextureLoaderPng(GraphicsDriver *graphicsDriver) : TextureLoader(graphicsDriver) {}

		virtual bool tryLoad(const std::string &uri) override {
			assert(this);

			namespace fs = boost::filesystem;
			namespace ba = boost::algorithm;
			
			fs::path path(uri);

			if (!fs::is_regular_file(path)) {
				return false;
			}

			std::string ext = path.stem().string();

			return ext == "png";
		}

		virtual ResourcePtr load(const std::string &uri) override {
			assert(this);

			GraphicsDriver *driver = this->getGraphicsDriver();
			assert(driver);

			::png_byte header[8];

			std::fstream fileStream;

			fileStream.open(uri.c_str(), std::ios_base::binary|std::ios_base::in);
			if (!fileStream.is_open()) {
				throw std::runtime_error("PNG file can't be opened.");
			}

			fileStream.read(reinterpret_cast<char*>(header), 8);
			if (::png_sig_cmp(header, 0, 8)) {
				throw std::runtime_error("Not a PNG file.");
			}

			::png_structp pngStruct = ::png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
			if (!pngStruct) {
				throw std::runtime_error("");
			}

			::png_infop pngInfo = ::png_create_info_struct(pngStruct);
			if (!pngInfo) {
				::png_destroy_read_struct(&pngStruct, nullptr, nullptr);
				throw std::runtime_error("");
			}

			::png_infop pngEndInfo = ::png_create_info_struct(pngStruct);
			if (!pngEndInfo) {
				::png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);
				throw std::runtime_error("");
			}

			if (setjmp(png_jmpbuf(pngStruct))) {
				::png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);
				throw std::runtime_error("");
			}

			

		}
	};
}}

namespace exeng { namespace raytracer {
    using namespace exeng::graphics;
    using namespace exeng::scenegraph;
    using namespace exeng::input;
    using namespace exeng::framework;
    using namespace exeng::raytracer::renderers;

    RayTracerApp2::RayTracerApp2() {}
    RayTracerApp2::~RayTracerApp2() {}

    BufferPtr RayTracerApp2::getAssetsXmlData() {
        return std::make_unique<StaticBuffer>((void*)assets_xml_data, assets_xml_size);
    }

    std::string RayTracerApp2::getPluginPath() {
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

    GraphicsDriverPtr RayTracerApp2::createGraphicsDriver() {
        this->getPluginManager()->setPluginPath(this->getPluginPath());
        this->getPluginManager()->loadPlugin("exeng.graphics.gl3");
		
        GraphicsDriverPtr graphicsDriver = this->getGraphicsManager()->createDriver();
        graphicsDriver->addEventHandler(this);
        graphicsDriver->initialize();
	    
		return graphicsDriver;
    }

    AssetLibraryPtr RayTracerApp2::createAssetLibrary() {
        AssetLibraryPtr assetLibrary = std::make_unique<AssetLibrary>();
		assetLibrary->addAsset("Vertex.glsl", std::make_unique<StaticBuffer>((void*)vertexshader_glsl_data, vertexshader_glsl_size));
		assetLibrary->addAsset("Fragment.glsl", std::make_unique<StaticBuffer>((void*)fragmentshader_glsl_data, fragmentshader_glsl_size));
        assetLibrary->addAsset("MultiHardwareTracer.cl", std::make_unique<StaticBuffer>((void*)multihardwaretracer_cl_data, multihardwaretracer_cl_size));

		return assetLibrary;
    }

    SceneRendererPtr RayTracerApp2::createSceneRenderer(GraphicsDriver *graphicsDriver) {
        // Create the material for the rendering of the screen
        Size2i screenSize = graphicsDriver->getDisplayMode().size;
        Texture *renderTarget = this->getTextureManager()->create("renderTarget", screenSize, {0.2f, 0.2f, 0.8f, 1.0f});

        ShaderProgram *program = this->getShaderLibrary()->getProgram("shaderProgram");

        Material *screenMaterial = this->getMaterialLibrary()->createMaterial("screen", program);
        screenMaterial
            ->setAttribute(0, Vector4f(1.0f, 1.0f, 1.0f, 1.0f))
            ->setAttribute(1, Vector4f(0.0f, 0.0f, 0.0f, 1.0f))
            ->setAttribute(2, Vector4f(0.0f, 0.0f, 0.0f, 1.0f))
            ->setAttribute(3, 0.0f)
            ->getLayer(0)->setTexture(renderTarget);
        
        // Create the mesh for rendering
        Mesh *screenMesh = this->getMeshManager()->generateScreenMesh("screen");
        
        AssetLibrary *assets = this->getAssetLibrary();
        MaterialLibrary *materials = this->getMaterialLibrary();

        auto renderWrapper = std::make_unique<HardwareRenderer>(renderTarget, assets, materials);
        
        SceneRendererPtr sceneRenderer = std::make_unique<GenericSceneRenderer>(std::move(renderWrapper));
        sceneRenderer->setScene(this->getScene());

        return sceneRenderer;
    }

    bool RayTracerApp2::onInitialize() {
        this->screenMaterial = this->getMaterialLibrary()->getMaterial("screen");
        this->screenMesh = this->getMeshManager()->getMesh("screen");
        this->camera = this->getScene()->getCamera(0);

        return true;
    }

    void RayTracerApp2::handleEvent(const EventData &data) {
        const InputEventData &inputData = data.cast<InputEventData>();
        
        if (inputData.check(ButtonStatus::Press, ButtonCode::KeyEsc)) {
            this->setApplicationStatus(ApplicationStatus::Terminated);
        }
    }

	void RayTracerApp2::updateNodeRotation(float seconds, SceneNode *node) {
		assert(this);
		assert(node);

		const float rotationSpeed = 60.0f;
		const float rotationAngle = rotationSpeed * seconds;

		this->rotationAngle += rotationAngle;

        node->setTransform(rotatey<float>(rad(this->rotationAngle)));
	}

    void RayTracerApp2::update(float seconds) {
        SceneNode *boxNode = this->getScene()->getRootNode()->findNode("boxNode");
		this->updateNodeRotation(seconds, boxNode);
    }

    void RayTracerApp2::render() {
        this->getGraphicsDriver()->beginFrame({0.2f, 0.2f, 0.8f, 1.0f}, ClearFlags::ColorDepth);

        // render the scene using ray tracing
        this->getSceneRenderer()->render(this->camera);

        // render the render target texture
        this->getGraphicsDriver()->setMaterial(this->screenMaterial);
        this->getGraphicsDriver()->getModernModule()->setProgramGlobal("WorldTransform", identity<float, 4>());
        this->renderMesh(this->screenMesh);

        this->getGraphicsDriver()->endFrame();
    }
}}

namespace exeng { namespace main {
    int main(int argc, char **argv) {
        using namespace exeng;
        using namespace exeng::framework;
        using namespace exeng::raytracer;

        return Application::execute<RayTracerApp2>(argc, argv);
    }
}}
