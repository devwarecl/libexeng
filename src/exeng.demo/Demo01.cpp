
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

/*
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
*/

class ButtonPressHandler : public IEventHandler {
public:
	ButtonPressHandler () {
		for (int i=0; i<ButtonCode::Count; i++) {
			this->buttonStatus[i] = ButtonStatus::Release;
		}
	}

	const bool isPressed(ButtonCode::Enum code) const {
		return this->buttonStatus[code] == ButtonStatus::Press;
	}

private:
	virtual void handleEvent(const EventData &data) override {
        const InputEventData &inputData = data.cast<InputEventData>();
		this->handleInputEvent(inputData);
    }

	void handleInputEvent(const InputEventData &inputData) {
		this->buttonStatus[inputData.buttonCode] = inputData.buttonStatus;
	}

private:
	ButtonStatus::Enum buttonStatus[ButtonCode::Count];
};

class MoveAction {
public:
	explicit MoveAction(const ButtonPressHandler *buttonPressHandler) {
		this->buttonPressHandler = buttonPressHandler;
	}

	const bool isMovingForward() const {
		assert(this);
		assert(this->buttonPressHandler);

		return this->buttonPressHandler->isPressed(ButtonCode::KeyUp);
	}

	const bool isMovingBackward() const {
		assert(this);
		assert(this->buttonPressHandler);

		return this->buttonPressHandler->isPressed(ButtonCode::KeyDown);
	}

	const bool isMovingLeft() const {
		assert(this);
		assert(this->buttonPressHandler);

		return this->buttonPressHandler->isPressed(ButtonCode::KeyLeft);
	}

	const bool isMovingRight() const {
		assert(this);
		assert(this->buttonPressHandler);

		return this->buttonPressHandler->isPressed(ButtonCode::KeyRight);
	}

private:
	const ButtonPressHandler *buttonPressHandler = nullptr;
};

class Demo01 : public GraphicsApplication, public IEventHandler {
public:
	Demo01() : moveAction(&buttonPressHandler) {
	}

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
		graphicsDriver->addEventHandler(&this->buttonPressHandler);
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
		// this->animator.reset(new SpatialAnimator(this->getScene()->getRootNode()->findNode("boxNode")));

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
    
	void updateCamera(float seconds) {
		const float speed		= 2.0f;
		const float distance	= speed * seconds;
		const float angle		= 60.0f * seconds;

		Camera *camera = this->getScene()->getCamera(0);

		Vector3f cameraPosition = camera->getPosition();
		Vector3f cameraLookAt = camera->getLookAt();

		Vector3f cameraDirection = normalize(cameraLookAt - cameraPosition);
		Vector3f cameraDisplace;

		float rotation = 0.0f;
		float movement = 0.0f;

		// Update direction
		if (this->moveAction.isMovingRight()) {
			rotation = -angle;
		} 

		if (this->moveAction.isMovingLeft()) {
			rotation = angle;
		} 

		// Update position
		if (this->moveAction.isMovingForward()) {
			movement = distance;
		} 

		if (this->moveAction.isMovingBackward()) {
			movement = -distance;
		} 

		// Compute final camera orientation
		cameraDirection = transform(rotatey(rad(rotation)), cameraDirection);
		cameraDisplace = cameraDirection * movement;

		cameraPosition += cameraDisplace;
		cameraLookAt = cameraPosition + cameraDirection;

		camera->setOrientation(cameraPosition, cameraLookAt);
	}

    virtual void update(float seconds) override {
		this->updateCamera(seconds);
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

private:
	Camera *camera = nullptr;
	ShaderProgram *program = nullptr;
	Material *material = nullptr;
    ApplicationStatus::Enum status = ApplicationStatus::Running;

	ButtonPressHandler buttonPressHandler;
	MoveAction moveAction;

	float angle = 0.0f;
};

/*
int main(int argc, char **argv) {
    return Application::execute<Demo01>(argc, argv);
}
*/

namespace xg {
	/*
	#define MAKE_VERTEX_FORMAT_ATTRIB(index, attrib, dataType, size) (((dataType) | (attrib << 2) | (size << 6)) << (index*8))

	struct VertexFormatAttrib {
		std::uint8_t dataType:2;
		std::uint8_t attrib:4;
		std::uint8_t size:2;
	};
	
	typedef std::uint64_t VertexFormat;
	*/


}

int main(int argc, char **argv) {


	return 0;
}
