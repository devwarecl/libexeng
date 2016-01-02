
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
			// load available plugins

			this->getPluginManager()->loadPlugins();

			std::cout << "Loaded plugins: " << std::endl;

			for (int i=0; i<this->getPluginManager()->getPluginCount(); i++) {
				const xe::sys::Plugin *plugin = this->getPluginManager()->getPlugin(i);

				std::cout << "\tName: " << plugin->getName() << std::endl;
				std::cout << "\tDesc: " << plugin->getDescription() << std::endl;
				std::cout << "\tVersion: " << plugin->getVersion() << std::endl;
				std::cout << std::endl;
			}

			std::cout << std::endl;

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
