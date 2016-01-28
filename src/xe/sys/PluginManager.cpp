/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "PluginManager.hpp"

#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/sort.hpp>

#include <xe/Core.hpp>
#include <xe/Exception.hpp>
#include <xe/sys/Library.hpp>
#include <xe/sys/Plugin.hpp>
#include <xe/sys/PluginLibrary.hpp>

namespace xe { namespace sys {
    namespace fs = boost::filesystem;
    
    /**
     * @brief Private attributes of the plugin manager.
     */
    typedef std::map<std::string, std::unique_ptr<Plugin>> PluginMap;
	typedef std::vector<Plugin*> PluginArray;

    struct PluginManager::Private {
        Core* core = nullptr;
        PluginMap plugins;
		PluginArray pluginArray;
        fs::path pluginPath;

		void loadPluginFile(const fs::path &file) {
			std::string key = file.filename().stem().string();

			if (key.substr(0, 3) == "lib") {
				key = key.substr(3, key.size() - 3);
			}

			this->loadPluginFile(file, key);
		}

		void loadPluginFile(const fs::path &file, const std::string &key) {
			// check if the library is loaded previously
			PluginMap &plugins = this->plugins;
        
			if (plugins.find(key) == plugins.end()) {
				LibraryPtr library = std::make_unique<Library>(file.string());
				PluginPtr pluginLibrary = std::make_unique<PluginLibrary>(std::move(library));

				pluginArray.push_back(pluginLibrary.get());

				plugins[key] = std::move(pluginLibrary);
				plugins[key]->initialize(this->core);
			}
		}
		

    };
    
	std::string plugin_filename(const std::string &pluginName) {
#if defined(EXENG_WINDOWS)
		return pluginName + std::string(".dll");
#elif defined(EXENG_UNIX)
		return std::string("lib") + pluginName + std::string(".so");
#else
#error Unsupported platform.
#endif        
	}

	bool is_plugin(const fs::path &file) {
		const std::string xe_module = plugin_filename("xe");
		const std::string ext = boost::algorithm::to_lower_copy(file.extension().string());
		const std::string file_name = file.filename().string();

		const bool is_library	= ext == ".so" || ext == ".dll";
		const bool is_plugin	= file_name.find("xe.") != std::string::npos;
		const bool is_xe_module	= file_name == xe_module;

		return is_library && is_plugin && !is_xe_module;
	}

	std::list<fs::path> list_files(const fs::path &directory) {
		std::list<fs::path> files;

		if (fs::is_directory(directory)) {
			auto range = boost::make_iterator_range(fs::directory_iterator(directory), {});

			for (auto path_it : range) {
				files.push_back(path_it.path());
			}
		}

		return files;
	}

    PluginManager::PluginManager(Core* core) {
		assert(core);

        this->impl = new PluginManager::Private();
        this->impl->core = core;
        
        this->impl->pluginPath = fs::current_path();
    }

    PluginManager::~PluginManager() {
        delete this->impl;
        this->impl = nullptr;
    }
    
    Core* PluginManager::getCore() {
        assert(this->impl != nullptr);
        
        return this->impl->core;
    }
        
    const Core* PluginManager::getCore() const {
        assert(this->impl != nullptr);
        
        return this->impl->core;
    }
    
    void PluginManager::loadPlugin(const std::string &name) {
        assert(this->impl != nullptr);
        
		fs::path file = this->impl->pluginPath / plugin_filename(name);
		std::string key = name;
		
		this->impl->loadPluginFile(file, key);
    }
    
    void PluginManager::unloadPlugin(const std::string &name) {
        assert(this->impl != nullptr);
        
        auto &plugins = this->impl->plugins;
		auto &pluginArray = this->impl->pluginArray;
        auto it = plugins.find(name);
            
        if (it != plugins.end()) {
            it->second->terminate();
			
			auto pluginArrayIterator = std::find(pluginArray.begin(), pluginArray.end(), it->second.get());
			pluginArray.erase(pluginArrayIterator);

            plugins.erase(name);
        }
    }
    
    void PluginManager::setPluginPath(const std::string &path) {
        assert(this->impl != nullptr);
        
        fs::path pluginPath(path);
        
        if (pluginPath.is_relative()) {
            pluginPath = fs::absolute(pluginPath);
        }
        
        pluginPath = pluginPath.normalize().parent_path();
        
        if (!fs::is_directory(pluginPath) || !fs::exists(pluginPath)) {
			EXENG_THROW_EXCEPTION("The directory '" + pluginPath.string() + "' is not valid.");
        }
        
        this->impl->pluginPath = pluginPath;
    }
    
    std::string PluginManager::getPluginPath() const {
        assert(this->impl != nullptr);
        
        return this->impl->pluginPath.string();
    }
    
    void PluginManager::loadPlugins() {
		namespace ba = boost::adaptors;

		const std::string path_separator = ";";
		const std::string xe_module = plugin_filename("xe");
		const std::string env_path = std::getenv("PATH") + path_separator + fs::current_path().string();

		// get the directories from the string
		std::list<std::string> paths;
		boost::algorithm::split(paths, env_path, boost::is_any_of(path_separator));

		// get all files from those directories
		std::list<fs::path> files;
		for (const std::string &path : paths) {
			std::list<fs::path> listed_files = list_files(fs::path(path));

			listed_files.sort();

			files.merge(listed_files);
		}

		// filter only plugin files
		auto plugins = files | ba::filtered(is_plugin);

		// finally, try to load the remaining plugins
		for (const fs::path &plugin : plugins) {
			try {
				this->impl->loadPluginFile(plugin);

			} catch (const std::exception &exp) {
				std::cout << exp.what() << std::endl;
			}
		}
    }

	int PluginManager::getPluginCount() const {
		return this->impl->pluginArray.size();
	}

	const Plugin* PluginManager::getPlugin(const int index) const {
		assert(index >= 0);
		assert(index < this->getPluginCount());

		return this->impl->pluginArray[index];
	}
}}
