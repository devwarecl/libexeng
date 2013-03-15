
#ifndef __EXENG_GRAPHICS_GRAPHICSMANAGER_HPP__
#define __EXENG_GRAPHICS_GRAPHICSMANAGER_HPP__

#include <vector>

#include "../Object.hpp"
#include "../Version.hpp"
#include "GraphicsDriver.hpp"

namespace exeng
{
	class EXENGAPI Root;

    namespace graphics
    {
		//! Contiene informacion sobre las capacidades que posee un controlador de graficos
		class EXENGAPI GraphicsDriverInfo : public Object
		{
		public:
			GraphicsDriverInfo();

			virtual ~GraphicsDriverInfo();

			//! Devuelve el nombre del driver
			std::string getName() const;

			//! Devuelve true si la implementacion del driver grafico es una implementacion de hardware
			bool isHardwareAccelerated() const;
			
			//! 
			virtual std::string toString() const;

		private:
			struct Private;
			Private* impl;

		private:
			GraphicsDriverInfo& operator= (const GraphicsDriverInfo& other);
			GraphicsDriverInfo (const GraphicsDriverInfo&);
		};


		//! Instantiates a unique type of graphics driver
		class EXENGAPI GraphicsDriverFactory
		{
		public:
			virtual ~GraphicsDriverFactory() {}
			virtual GraphicsDriverInfo& getDriverInfo() const = 0;
			virtual GraphicsDriver* create() = 0;
		};


		//! Clase "manager" del subsistema de graficos.
		class EXENGAPI GraphicsManager
		{
			friend class exeng::Root;

		public:
			~GraphicsManager();

			//!
			void addDriverFactory(GraphicsDriverFactory& factory);

			//!
			void removeDriverFactory(GraphicsDriverFactory& factory);

			//! Crea un controlador grafico 
			GraphicsDriver* createDriver(GraphicsDriverInfo& info);

			//! Devuelve la cantidad total de fabricas registradas en el administrador
			int getDriverFactoryCount() const;

			//! Devuelve la informacion del driver que podria crear la fabrica indicada
			GraphicsDriverInfo& getDriverInfo( int factoryIndex ) const;

		private:
			GraphicsManager();

			struct Private;
			Private *impl;
		};

    }
}

#endif  //__EXENG_GRAPHICS_GRAPHICSMANAGER_HPP__
