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

#ifndef __EXENG_HPP__
#define __EXENG_HPP__

#include "DetectEnv.hpp"
#include "Config.hpp"
#include "TFlags.hpp"
#include "Object.hpp"
#include "Version.hpp"
#include "Root.hpp"

#include "math/Common.hpp"
#include "math/TSize.hpp"
#include "math/TVector.hpp"
#include "math/TMatrix.hpp"
#include "math/TBoundary.hpp"

/**
 * @brief The common namespace for the engine.
 */
namespace exeng {
	/**
	 * @brief Classes for rendering raw 2D and 3D graphics.
	 */
    namespace graphics {}
    
    /**
	 * @brief Common mathematical namespace
	 */
    namespace math {}
    
    /**
	 * @brief Loading for plugins and dynamic linking libraries.
	 */
    namespace system {}
    
    /**
     * @brief Scenegraph module, for rendering 3D graphics.
     */
    namespace scenegraph {}
}

#endif  //__EXENG_HPP__
