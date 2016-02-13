/**
 * @file Application.cpp
 * @brief Implementation of the Application class.
 */

/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "Application.hpp"

#include <xe/sys/Plugin.hpp>
#include <xe/sys/PluginManager.hpp>
#include <xe/util/MessageBox.hpp>

namespace xe {
	using xe::util::MessageBox;
	using xe::util::MessageBoxIcon;

	Application::Application() {
		// load available plugins
		xe::sys::PluginManager *pluginManager = this->getPluginManager();

		pluginManager->loadPlugins();

		std::cout << "Available plugins: " << std::endl;
		for (int i=0; i<pluginManager->getPluginCount(); i++) {
			const xe::sys::Plugin *plugin = pluginManager->getPlugin(i);

			std::cout << "\tName: " << plugin->getName() << std::endl;
			std::cout << "\tDesc: " << plugin->getDescription() << std::endl;
			std::cout << "\tVersion: " << plugin->getVersion() << std::endl;
			std::cout << std::endl;
		}

		if (pluginManager->getPluginCount() == 0) {
			std::cout << "No plugins were loaded!" << std::endl;
		}

		std::cout << std::endl;
	}

	Application::~Application() {}

    int Application::execute(Application &app, int argc, char** argv) {
        int exitCode = 0;
        
        try {
            exitCode = app.run(argc, argv);

        } catch (std::exception &exp) {
			MessageBox::show("Caught unhandled exception", exp.what(), MessageBoxIcon::Error);
			exitCode = 1;
        }
        
        return exitCode;
    }
    
	/*
    int Application::execute(Application &app, int argc, char** argv) {
        return app.run(argc, argv);
    }
	*/
}
