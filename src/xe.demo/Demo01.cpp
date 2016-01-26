
#include <memory>
#include <xe/fw/Application.hpp>
#include <xe/sys/Plugin.hpp>
#include <xe/sys/PluginManager.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe.main/Main.hpp>

namespace demo {
	class DemoApplication : public xe::fw::Application {
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
				throw std::runtime_error("No available graphics drivers.");
			}

			// select the first graphics driver
			auto graphicsDriver = this->getGraphicsManager()->createDriver(driverInfos[0]);

			this->graphicsDriver = std::move(graphicsDriver);
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

		bool done = false;
	};
}

namespace xe { namespace main {
	int main(int argc, char** argv) {
		return xe::fw::Application::execute<demo::DemoApplication>(argc, argv);
	}
}}
