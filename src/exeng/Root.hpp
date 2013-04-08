
#ifndef __EXENG_ROOT_HPP__
#define __EXENG_ROOT_HPP__

#include "Config.hpp"

namespace exeng {
	namespace system {
		class EXENGAPI PluginManager;
	}

    /**
     * @brief La clase raiz del motor multimedia. Contiene referencias a 
	 * los distintos subsistemas del engine.
     */
	class EXENGAPI Root {
	public:

		/**
         * @brief Instancia el objeto raiz
		 */
		Root();
        
		/**
         * @brief 
		 */
		~Root();

        /**
         * @brief Devuelve el manejador de plugins actual
         * @return 
         */
		exeng::system::PluginManager& getPluginManagerRef();

	private:
		struct Private;
		Private *impl;
	};
}

#endif	//__EXENG_ROOT_HPP__
