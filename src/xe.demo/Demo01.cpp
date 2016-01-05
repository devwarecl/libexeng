
#include <memory>
#include <xe/fw/Application.hpp>
#include <xe/sys/Plugin.hpp>
#include <xe/sys/PluginManager.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/input/IEventHandler.hpp>
#include <xe.main/Main.hpp>

namespace demo {
	class DemoApplication : public xe::fw::Application, public xe::input::IEventHandler {
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

			// this->graphicsDriver->addEventHandler(this);
		}

        virtual int run(int argc, char **argv) override {
			// initialize the graphics driver with default settings
			this->graphicsDriver->initialize();

			auto keyboardStatus = this->graphicsDriver->getInputManager()->getKeyboard()->getStatus();

			while (!done) {
				xe::Vector4f color(0.2f, 0.2f, 0.8f, 1.0f);

				this->graphicsDriver->getInputManager()->poll();
			
				done = keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyEsc);

				this->graphicsDriver->beginFrame(color, xe::gfx::ClearFlags::ColorDepth);

				this->graphicsDriver->endFrame();
			}

			this->graphicsDriver->terminate();

			return 0;
		}

		virtual void handleEvent(const xe::input::EventData &eventData) override {
			/*
			if (eventData.eventType == xe::TypeId<xe::gfx::InputEventData>()) {
				auto inputEventData = eventData.cast<xe::gfx::InputEventData>();
				this->done = inputEventData.check(xe::gfx::ButtonStatus::Press, xe::gfx::ButtonCode::KeyEsc);

			} else if (eventData.eventType == xe::TypeId<xe::gfx::CloseEventData>()) {
				this->done = true;
			}
			*/
		}

		// virtual void handleInputEvent(const xe::gfx::InputEventData &eventData) {
		// 	}

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
