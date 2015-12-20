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

#ifndef __EXENG_GRAPHICS_GRAPHICSMANAGER_HPP__
#define __EXENG_GRAPHICS_GRAPHICSMANAGER_HPP__

#include <list>
#include <vector>

#include <xe/Object.hpp>
#include <xe/Version.hpp>
#include <xe/gfx/GraphicsDriver.hpp>

namespace xe {   
    class EXENGAPI Root;
}

namespace xe { namespace gfx {
    
    /**
     * @brief Shader programming language description.
     */
    struct ShaderLanguage 
    {
        enum Type {
            GLSL,
            HLSL,
            CG
        };
        
        Type type;
        Version version;
        
        ShaderLanguage();
        ShaderLanguage(ShaderLanguage::Type type, const Version &version);
    };
    
    
    /**
     * @brief Type of GraphicsDriver
     */
    struct DriverType : public Enum 
    {
        enum Enum {
            Software,
            Hardware
        };
    };
    
    /**
     * @brief Basic information about a specific graphics driver.
     */
    struct GraphicsDriverInfo 
    {
        std::string name = "";
        Version version = {0, 0, 0, 0};
        DriverType::Enum type = DriverType::Software;
        std::vector<ShaderLanguage> shadingLanguages;
        
        bool operator== (const GraphicsDriverInfo &other) const;
        bool operator!= (const GraphicsDriverInfo &other) const;
        bool operator< (const GraphicsDriverInfo &other) const;
    };
    
    /**
     * @brief Instancia un tipo unico de controlador grafico
     */        
    class EXENGAPI IGraphicsDriverFactory {
    public:
        virtual ~IGraphicsDriverFactory() {}
        virtual GraphicsDriverInfo getDriverInfo() const = 0;
        virtual std::unique_ptr<GraphicsDriver> create() = 0;
    };
    
    /**
     * @brief Clase "manager" del subsistema de graficos.
     */
    class EXENGAPI GraphicsManager {
        friend class xe::Root;

    public:
        GraphicsManager();
        ~GraphicsManager();

        /**
         * @brief Add a new known GraphicsDriverFactory.
         */
        void addDriverFactory(IGraphicsDriverFactory* factory);

        /**
         * @brief Remove a existing GraphicsDriverFactory
         */
        void removeDriverFactory(IGraphicsDriverFactory* factory);
        
        /**
         * @brief Create the best available graphics driver, from the current 
         * registered ones.
         */
        std::unique_ptr<GraphicsDriver> createDriver();
        
        /**
         * @brief Create the graphics driver corresponding with the
         * supplied driver desc.
         */
        std::unique_ptr<GraphicsDriver> createDriver(const GraphicsDriverInfo &info);

		/**
		 * @brief Get available device descriptions.
		 */
		std::vector<GraphicsDriverInfo> getAvailableDrivers() const;
		
    private:
        struct Private;
        Private *impl = nullptr;
    };
}}


namespace xe { namespace gfx {

    inline bool GraphicsDriverInfo::operator== (const GraphicsDriverInfo &other) const 
    {
        if (this->name != other.name) {
            return false;
        }
            
        if (this->version != other.version) {
            return false;
        }
            
        return true;
    }
        
    inline bool GraphicsDriverInfo::operator!= (const GraphicsDriverInfo &other) const 
    {
        return !(*this == other);
    }
        
    inline bool GraphicsDriverInfo::operator< (const GraphicsDriverInfo &other) const 
    {
        return this->name < other.name && this->version < other.version;
    }
}}

namespace xe { namespace gfx {
    
    inline ShaderLanguage::ShaderLanguage() {}
    
    inline ShaderLanguage::ShaderLanguage(ShaderLanguage::Type type, const Version &version)
    {
        this->type = type;
        this->version = version;
    }
}}
        
#endif  //__EXENG_GRAPHICS_GRAPHICSMANAGER_HPP__
