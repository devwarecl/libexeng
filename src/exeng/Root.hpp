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

#ifndef __EXENG_ROOT_HPP__
#define __EXENG_ROOT_HPP__

#include "Config.hpp"

namespace exeng {

	namespace system {
		class EXENGAPI PluginManager;
	}

    /**
     * @brief The root class of the multimedia engine. 
     *
     * Permits the creation of various objects of several modules.
     */
	class EXENGAPI Root {
	public:
		Root();
        
		~Root();

        /**
         * @brief Get the current plugin manager.
         */
		exeng::system::PluginManager& getPluginManagerRef();

	private:
		struct Private;
		Private *impl;
	};
}

#endif	//__EXENG_ROOT_HPP__
