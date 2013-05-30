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

#include <vector>

#include <exeng/Object.hpp>
#include <exeng/Version.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>

namespace exeng {
    
    class EXENGAPI Root;

    namespace graphics {
        
        /**
         * @brief 
         */
        struct GraphicsDriverInfo {
            std::string name;
            Version version;
            bool hardware;
            bool supportsVertexShaders;
            bool supportsPixelShader;
            bool supportGeometryShaders;
            
            inline GraphicsDriverInfo() {
                this->name = "";
                this->version = Version(1, 0, 0, 0);
                this->hardware = false;
                this->supportsVertexShaders = false;
                this->supportsPixelShader = false;
                this->supportGeometryShaders = false;
            }
            
            
            inline bool operator== (const GraphicsDriverInfo &other) const {
                if (this->name != other.name) {
                    return false;
                }
                
                if (this->version != other.version) {
                    return false;
                }
                
                return true;
            }
            
            
            inline bool operator!= (const GraphicsDriverInfo &other) const {
                return !(*this == other);
            }
            
            
            inline bool operator< (const GraphicsDriverInfo &other) const {
                return this->name < other.name && this->version < other.version;
            }
        };
        
        /**
         * @brief Instancia un tipo unico de controlador grafico
         */        
        class EXENGAPI IGraphicsDriverFactory {
        public:
            virtual ~IGraphicsDriverFactory() {}
            virtual GraphicsDriverInfo getDriverInfo() const = 0;
            virtual GraphicsDriver* create() = 0;
        };
        
        /**
         * @brief Clase "manager" del subsistema de graficos.
         */
        class EXENGAPI GraphicsManager {
            friend class exeng::Root;

        public:
            GraphicsManager();
            
            ~GraphicsManager();

            /**
             * @brief 
             */
            void addDriverFactory(IGraphicsDriverFactory* factory);

            /**
             * @brief
             */
            void removeDriverFactory(IGraphicsDriverFactory* factory);
            
            /**
             * @brief Create the best available graphics driver, from the current 
             * registered ones.
             */
            GraphicsDriver* createDriver();
            
            /**
             * @brief Create the graphics driver corresponding with the
             * supplied driver desc.
             */
            GraphicsDriver* createDriver(const GraphicsDriverInfo &info);
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif  //__EXENG_GRAPHICS_GRAPHICSMANAGER_HPP__
