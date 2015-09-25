
#include "RayTracerApp2.hpp"

#include <cstdio>
#include <memory>
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

			// This function was originally written by David Grayson for
			// https://github.com/DavidEGrayson/ahrs-visualizer

			::png_byte header[8];
			
			FILE *fp = std::fopen(uri.c_str(), "rb");
			if (fp == nullptr) {
				throw std::runtime_error("Can't open the PNG file.");
			}

			// read the header
			std::fread(header, 1, 8, fp);

			if (::png_sig_cmp(header, 0, 8)) {
				throw std::runtime_error("Not a PNG file.");
			}

			::png_structp png_ptr = ::png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (!png_ptr) {
				std::fclose(fp);
				throw std::runtime_error("Not a PNG file.");
			}

			// create png info struct
			::png_infop info_ptr = ::png_create_info_struct(png_ptr);
			if (!info_ptr) {
				::png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
				std::fclose(fp);
				throw std::runtime_error("error: png_create_info_struct returned 0.");
			}

			// create png info struct
			::png_infop end_info = ::png_create_info_struct(png_ptr);
			if (!end_info) {
				::png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
				std::fclose(fp);
				throw std::runtime_error("error: png_create_info_struct returned 0.");
			}

			// the code in this if statement gets called if libpng encounters an error
			if (setjmp(png_jmpbuf(png_ptr))) {
				::png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
				std::fclose(fp);
				throw std::runtime_error("error from libpng.");
			}

			// init png reading
			::png_init_io(png_ptr, fp);

			// let libpng know you already read the first 8 bytes
			::png_set_sig_bytes(png_ptr, 8);

			// read all the info up to the image data
			::png_read_info(png_ptr, info_ptr);

			// variables to pass to get info
			int bit_depth = 0, color_type = 0;
			::png_uint_32 width = 0, height = 0;

			// get info about png
			::png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

			//printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);

			if (bit_depth != 8) {
				// fprintf(stderr, "%s: Unsupported bit depth %d.  Must be 8.\n", file_name, bit_depth);
				throw std::runtime_error("Unsupported bit depth.  Must be 8.");
			}

			// TODO: handle pixel format
			ColorFormat format;

			if (color_type == PNG_COLOR_TYPE_RGB) {
				format = ColorFormat (
					24,
					{ColorComponent::Red, 8},
					{ColorComponent::Green, 8},
					{ColorComponent::Blue, 8}
				);

			} else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA) {
				format = ColorFormat (
					32,
					{ColorComponent::Red, 8},
					{ColorComponent::Green, 8},
					{ColorComponent::Blue, 8},
					{ColorComponent::Alpha, 8}
				);
			} else {
				// fprintf(stderr, "%s: Unknown libpng color type %d.\n", file_name, color_type);
				throw std::runtime_error("Unknown libpng color type.");
			}

			// Update the png info struct.
			::png_read_update_info(png_ptr, info_ptr);

			// Row size in bytes.
			int rowbytes = ::png_get_rowbytes(png_ptr, info_ptr);

			// glTexImage2d requires rows to be 4-byte aligned
			rowbytes += 3 - ((rowbytes-1) % 4);

			// Allocate the image_data as a big block, to be given to opengl
			::png_byte *image_data = (::png_byte *)std::malloc(rowbytes * height * sizeof(::png_byte) + 15);
			if (image_data == NULL) {
				fprintf(stderr, "error: could not allocate memory for PNG image data\n");
				::png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
				std::fclose(fp);
				return 0;
			}

			// row_pointers is for pointing to image_data for reading the png with libpng
			::png_byte **row_pointers = (::png_byte **)malloc(height * sizeof(::png_byte *));
			if (row_pointers == NULL) {
				fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
				::png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
				std::free(image_data);
				fclose(fp);
				return 0;
			}

			// set the individual row_pointers to point at the correct offsets of image_data
			for (unsigned int i=0; i<height; i++) {
				row_pointers[height - 1 - i] = image_data + i * rowbytes;
			}

			// read the png into image_data through row_pointers
			::png_read_image(png_ptr, row_pointers);

			// Generate the OpenGL texture object
			auto texture = driver->createTexture(Vector2i(width, height), format);

			texture->lock();
			// std::memcpy(texture->lock(), image_data, texture->getSize().)
			texture->unlock();

			/*
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE, image_data);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			*/

			// clean up
			::png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			std::free(image_data);
			std::free(row_pointers);
			std::fclose(fp);

			return nullptr;
		}
	};
}}

namespace exeng { namespace raytracer {
    using namespace exeng::graphics;
    using namespace exeng::scenegraph;
    using namespace exeng::input;
    using namespace exeng::framework;
    using namespace exeng::raytracer::renderers;

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

    RayTracerApp2::RayTracerApp2() {
		this->buttonPressHandler = std::make_unique<ButtonPressHandler>();
		this->moveAction = std::make_unique<MoveAction>(this->buttonPressHandler.get());
	}

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
		graphicsDriver->addEventHandler(this->buttonPressHandler.get());
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

		auto rotation = identity<float, 4>();

		rotation *= rotatey<float>(rad(this->rotationAngle));
		rotation *= rotatez<float>(rad(this->rotationAngle));
		rotation *= rotatex<float>(rad(this->rotationAngle));

        node->setTransform(rotation);
	}

	void RayTracerApp2::updateCamera(float seconds) {
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
		if (this->moveAction->isMovingRight()) {
			rotation = -angle;
		} 

		if (this->moveAction->isMovingLeft()) {
			rotation = angle;
		} 

		// Update position
		if (this->moveAction->isMovingForward()) {
			movement = distance;
		} 

		if (this->moveAction->isMovingBackward()) {
			movement = -distance;
		} 

		// Compute final camera orientation
		cameraDirection = transform(rotatey(rad(rotation)), cameraDirection);
		cameraDisplace = cameraDirection * movement;

		cameraPosition += cameraDisplace;
		cameraLookAt = cameraPosition + cameraDirection;

		camera->setOrientation(cameraPosition, cameraLookAt);
	}

    void RayTracerApp2::update(float seconds) {
        SceneNode *boxNode = this->getScene()->getRootNode()->findNode("boxNode");
		this->updateNodeRotation(seconds, boxNode);
		this->updateCamera(seconds);
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
