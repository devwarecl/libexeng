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
         *  @brief Contiene informacion sobre las capacidades que posee un controlador de graficos
         */
        class EXENGAPI GraphicsDriverInfo : public Object {
        public:
            GraphicsDriverInfo();

            virtual ~GraphicsDriverInfo();

            /**
             * @brief Devuelve el nombre del driver
             */
            std::string getName() const;
 
            /**
             * @brief Devuelve true si la implementacion del driver grafico es 
             * una implementacion de hardware
             */
            bool isHardwareAccelerated() const;
            
            virtual std::string toString() const;

        private:
            struct Private;
            Private* impl;

        private:
            GraphicsDriverInfo& operator= (const GraphicsDriverInfo& other);
            GraphicsDriverInfo (const GraphicsDriverInfo&);
        };


        /**
         *  @brief Instancia un tipo unico de controlador grafico
         */        
        class EXENGAPI IGraphicsDriverFactory {
        public:
            virtual ~IGraphicsDriverFactory() {}
            virtual GraphicsDriverInfo& getDriverInfo() const = 0;
            virtual GraphicsDriver* create() = 0;
        };
        
        
        /**
         * @brief Clase "manager" del subsistema de graficos.
         */
        class EXENGAPI GraphicsManager {
            friend class exeng::Root;

        public:
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
             * @brief Crea el mejor controlador grafico disponible, para la 
             */
            GraphicsDriver* createDriver();
            
            /**
             * @brief Devuelve la cantidad total de fabricas registradas en el administrador
             */
            int getDriverFactoryCount() const;

            /**
             * @brief Devuelve la informacion del driver que podria crear la fabrica indicada
             */
            GraphicsDriverInfo& getDriverInfo( int factoryIndex ) const;

        private:
            GraphicsManager();

            struct Private;
            Private *impl;
        };
    }
}

#endif  //__EXENG_GRAPHICS_GRAPHICSMANAGER_HPP__
