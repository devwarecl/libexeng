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


#ifndef __EXENG_SCENEGRAPH_SCENENODEDATA_HPP__
#define __EXENG_SCENEGRAPH_SCENENODEDATA_HPP__

#include <xe/Object.hpp>

namespace xe { namespace sg {

/**
 * @brief Base class for display data in the scene graph. Can be any multi-media element.
 * The lifetime of this object is independent of the containing scenegraph.
 */
class EXENGAPI SceneNodeData : public Object {
public:
    virtual ~SceneNodeData();
};
        
}}


#endif // __EXENG_SCENEGRAPH_SCENENODEDATA_HPP__
