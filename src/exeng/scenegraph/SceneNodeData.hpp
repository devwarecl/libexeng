/**
 * @brief Documentacion pendiente
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
