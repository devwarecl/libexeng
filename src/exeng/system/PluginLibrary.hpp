/**
 * @file Plugin.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_SYSTEM_PLUGINLIBRARY_HPP__
#define __EXENG_SYSTEM_PLUGINLIBRARY_HPP__

#include <memory>
#include <stdexcept>
#include <exeng/system/Plugin.hpp>
#include <exeng/system/Library.hpp>

namespace exeng { namespace system {    
    /**
     * @brief Manage a plugin loaded from an external library
     */
    class PluginLibrary : public Plugin {
    public:
        PluginLibrary(std::unique_ptr<Library> library);
        virtual ~PluginLibrary();
        virtual std::string getName() const override;
        virtual std::string getDescription() const override;
        virtual Version getVersion() const override;
        virtual void initialize(Root *root) override;
        virtual void terminate() override;
        
    private:
        std::unique_ptr<Library> library;
        Plugin* plugin = nullptr;
    };
}}

#endif // __EXENG_SYSTEM_PLUGINLIBRARY_HPP__
