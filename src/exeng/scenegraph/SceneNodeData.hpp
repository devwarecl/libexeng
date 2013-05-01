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

#include "../Object.hpp"

namespace exeng
{
    namespace scenegraph
    {
    
        /**
         * @brief Clase base para la informacion que se desee colgar de un nodo de escena.
         * La duracion de este objeto es independiente del nodo de escena que lo contiene
         */
    
        class EXENGAPI SceneNodeData : public Object
        {
        public:
            /**
             * @brief Documentacion pendiente
             */
            virtual ~SceneNodeData();
        };
    }
}


#endif // __EXENG_SCENEGRAPH_SCENENODEDATA_HPP__
