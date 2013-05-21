/**
 * @file IMeshLoader.hpp
 * @brief IMeshLoader interface definition. 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_SCENEGRAPH_IMESHLOADER_HPP__
#define __EXENG_SCENEGRAPH_IMESHLOADER_HPP__

#include <exeng/Config.hpp>

namespace exeng {
    namespace scenegraph {
        class EXENGAPI Mesh;    
        
        /**
         * @brief Mesh loader interface.
         */
        class EXENGAPI IMeshLoader{
        public:
            virtual ~IMeshLoader();
            
            /**
             * @brief Check if the specified filename extension is supported by the current loader.
             * @param filename Raw string to the filename to check. 
             */
            virtual bool isSupported(const char* extension) = 0;
            
            /**
             * @brief Load the mesh contained in the specified file.
             */
            virtual Mesh* loadMesh(const char* filename) = 0;
        };
    }
}
        

#endif // __EXENG_SCENEGRAPH_IMESHLOADER_HPP__
