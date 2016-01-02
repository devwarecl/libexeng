
#include <memory>
#include <xe/fw/Application.hpp>
#include <xe/sys/PluginManager.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe.main/Main.hpp>

namespace demo {
	class DemoApplication : public xe::fw::Application {
	public:
		DemoApplication() {
			// load all plugins
			this->getPluginManager()->loadPlugins();

			// display all available drivers
			auto driverInfos = this->getGraphicsManager()->getAvailableDrivers();

			if (driverInfos.size() > 0) {
				std::cout << "Available graphic drivers:" << std::endl;
				for (const auto &driverInfo : driverInfos) {
					std::cout << driverInfo.name << std::endl;
				}

			} else {
				throw std::runtime_error("No available graphics drivers.");
			}

			// select the first one
			auto graphicsDriver = this->getGraphicsManager()->createDriver(driverInfos[0]);

			this->graphicsDriver = std::move(graphicsDriver);
		}

        virtual int run(int argc, char **argv) override {
			// initialize the graphics driver with default settings
			graphicsDriver->initialize();

			graphicsDriver->terminate();

			return 0;
		}

	private:
		xe::gfx::GraphicsDriverPtr graphicsDriver;
	};
}

namespace xe { namespace main {
	int main(int argc, char** argv) {
		return xe::fw::Application::execute<demo::DemoApplication>(argc, argv);
	}
}}
