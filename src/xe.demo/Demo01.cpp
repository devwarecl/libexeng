
/*
#include <memory>

#include <xe/Application.hpp>
#include <xe/sys/Plugin.hpp>
#include <xe/sys/PluginManager.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/Vertex.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/TextureManager.hpp>
#include <xe.main/Main.hpp>

namespace xe {
	class DemoApplication : public xe::Application {
	public:
		DemoApplication() {
			// display all available graphics drivers
			auto driverInfos = this->getGraphicsManager()->getAvailableDrivers();

			if (driverInfos.size() > 0) {
				std::cout << "Available graphic drivers:" << std::endl;
				for (const auto &driverInfo : driverInfos) {
					std::cout << driverInfo.name << std::endl;
				}

			} else {
				std::cout << "No available graphics drivers!" << std::endl;
				throw std::runtime_error("");
			}

			// select the first graphics driver
			auto graphicsDriver = this->getGraphicsManager()->createDriver(driverInfos[0]);

			this->graphicsDriver = std::move(graphicsDriver);
		}

		void initGeometry() {
			xe::gfx::Texture *texture = this->getGraphicsManager()->getTextureManager()->getTexture("assets/test.png");

			xe::gfx::Material *material = nullptr;
			
			xe::gfx::StandardVertex v1, v2, v3, v4;

			v1.coord = {-1.0f, 1.0f, 0.0f};	v1.normal = { 0.0f, 0.0f, 0.0f}; v1.texCoord = {0.0f, 1.0f};
			v2.coord = { 1.0f, 1.0f, 0.0f};	v2.normal = { 0.0f, 0.0f, 0.0f}; v2.texCoord = {1.0f, 1.0f};
			v3.coord = {-1.0f, 0.0f, 0.0f};	v3.normal = { 0.0f, 0.0f, 0.0f}; v3.texCoord = {0.0f, 0.0f};
			v4.coord = { 1.0f, 0.0f, 0.0f};	v4.normal = { 0.0f, 0.0f, 0.0f}; v4.texCoord = {0.0f, 0.0f};

			std::vector<xe::gfx::StandardVertex> vertices = {v1, v2, v3, v4};

			auto vbuffer = this->graphicsDriver->createVertexBuffer(vertices);

            format = xe::gfx::StandardVertex::getFormat();

			auto meshSubset = this->graphicsDriver->createMeshSubset(std::move(vbuffer), &format);
			auto mesh = std::make_unique<xe::gfx::Mesh>(std::move(meshSubset));
		}

        virtual int run(int argc, char **argv) override {
			// initialize the graphics driver with default settings
			this->graphicsDriver->initialize();

			auto keyboardStatus = this->graphicsDriver->getInputManager()->getKeyboard()->getStatus();

			while (!done) {
				this->graphicsDriver->getInputManager()->poll();
			
				done = keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyEsc);

				this->graphicsDriver->beginFrame({0.2f, 0.2f, 0.8f, 1.0f}, xe::gfx::ClearFlags::ColorDepth);

				this->graphicsDriver->endFrame();
			}

			this->graphicsDriver->terminate();

			return 0;
		}

	private:
		xe::gfx::GraphicsDriverPtr graphicsDriver;
        xe::gfx::VertexFormat format;

		bool done = false;
	};
}

namespace xe { 
	int main(int argc, char** argv) {
		return xe::Application::execute<xe::DemoApplication>(argc, argv);
	}
}
*/
