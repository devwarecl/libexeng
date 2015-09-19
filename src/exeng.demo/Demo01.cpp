
#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <exeng/Exeng.hpp>
#include <exeng/graphics/VertexWrapper.hpp>
#include <exeng/graphics/ShaderLibrary.hpp>
#include <exeng/graphics/MeshSubset.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/scenegraph/AssetsLibrary.hpp>
#include <exeng/scenegraph/GeometryLibrary.hpp>
#include <exeng/framework/GraphicsApplication.hpp>
#include <exeng/graphics/TextureManager.hpp>

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
		// transform *= rotatez<float>(rad(angle));

		this->getSceneNode()->setTransform(transform);
	}

private:
	float angle = 0.0f;
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

	virtual BufferPtr getAssetsXmlData() override {
		return std::make_unique<StaticBuffer>((void*)assets_xml_data, assets_xml_size);
	}

	virtual GraphicsDriverPtr createGraphicsDriver() override {
		auto pluginManager = this->getPluginManager();

		pluginManager->setPluginPath(this->getPluginPath());
        pluginManager->loadPlugin("exeng.graphics.gl3");
		
        GraphicsDriverPtr graphicsDriver = this->getGraphicsManager()->createDriver();
        graphicsDriver->addEventHandler(this);
        graphicsDriver->initialize();
	
		return graphicsDriver;
	}

	virtual AssetLibraryPtr createAssetLibrary() override {
		AssetLibraryPtr assetLibrary = std::make_unique<AssetLibrary>();
		assetLibrary->addAsset("Vertex.glsl",  std::make_unique<StaticBuffer>((void*)vertex_glsl_data, vertex_glsl_size));
		assetLibrary->addAsset("Fragment.glsl",  std::make_unique<StaticBuffer>((void*)fragment_glsl_data, fragment_glsl_size));

		return assetLibrary;
	}

	virtual SceneRendererPtr createSceneRenderer(GraphicsDriver *graphicsDriver) override {
        RasterizerRenderWrapperPtr 
        renderWrapper = std::make_unique<RasterizerRenderWrapper>(graphicsDriver);
        renderWrapper->setTransformName("WorldTransform");

        SceneRendererPtr 
        sceneRenderer = std::make_unique<GenericSceneRenderer>(std::move(renderWrapper));
        sceneRenderer->setScene(this->getScene());

		return sceneRenderer;
	}

    virtual bool onInitialize() override {
		this->camera = this->getScene()->getCamera(0);
		this->animator.reset(new SpatialAnimator(this->getScene()->getRootNode()->findNode("boxNode")));

		return true;
    }
    
    virtual ApplicationStatus::Enum getApplicationStatus() const override {
        return this->status;
    }
    
	/*
    virtual void pollEvents() override {
        this->getGraphicsDriver()->pollEvents();
    }
	*/
    
    virtual void update(float seconds) override {
		this->animator->update((float)seconds);
    }
    
    /*
	virtual void render() override {
		// this->getGraphicsDriver()->beginFrame({0.0f, 0.0f, 1.0f, 1.0f}, ClearFlags::ColorDepth);
		this->getSceneRenderer()->render(this->getScene()->getCamera(0));
		// this->getGraphicsDriver()->endFrame();
	}
    */
	
    virtual void handleEvent(const EventData &data) override {
        const InputEventData &inputData = data.cast<InputEventData>();
        
        if (inputData.check(ButtonStatus::Press, ButtonCode::KeyEsc)) {
            this->status = ApplicationStatus::Terminated;
        }
    }

	//const Vertex *vertices = (const Vertex*)subset->getBuffer(0)->getPointer();
	//for (int vertexIndex=0; vertexIndex<subset->getVertexCount(); ++vertexIndex) {
	//	std::cout << vertices[vertexIndex].coord << "; ";
	//	std::cout << vertices[vertexIndex].normal << "; ";
	//	std::cout << vertices[vertexIndex].texCoord;
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;
	
private:
	SceneNodeAnimatorPtr animator;
	// Texture *checkerTexture;

	Camera *camera = nullptr;
	ShaderProgram *program = nullptr;
	Material *material = nullptr;
    ApplicationStatus::Enum status = ApplicationStatus::Running;

	float angle = 0.0f;
};

int main(int argc, char **argv) {
    return Application::execute<Demo01>(argc, argv);
}
