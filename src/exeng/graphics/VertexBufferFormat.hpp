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

#ifndef __EXENG_GRAPHICS_VERTEXFORMAT_HPP__
#define __EXENG_GRAPHICS_VERTEXFORMAT_HPP__

#include "../Config.hpp"

namespace exeng {
    namespace graphics {
        /**
         * @brief Describe the vertex format
         */
        class EXENGAPI VertexBufferFormat {
        public:
            /**
             * @brief
             */
            VertexBufferFormat();
            
            /**
             * @brief Return the total number of spatial coordinates per vertex (2, 3 or 4)
             */
            int getCoordCount() const;
            
            /**
             * @brief Return the number of color coordinates
             */
            int getColorCount() const;
            
            /**
             * @brief Return the total number of texture coordinates
             */
            int getTexCoordCount(int Unit) const;
            
            /**
             * @brief Get the total count of texture unit coordinates
             */
            int getTexUnitCount() const;
            
            /**
             * @brief This is true if the vertex format allow normals
             */
            bool getNormalStatus() const;
            
            /**
             * @brief
             */
            void setCoordCount( int Count );
            
            /**
             * @brief
             */
            void setColorCount( int Count );
            
            /**
             * @brief
             */
            void setTexCoordCount( int Unit, int Count );
            
            /**
             * @brief
             */
            void setNormalStatus(bool Value);
            
            /**
             * @brief
             */
            void setColorStatus(bool Value);
            
            /**
             * @brief
             */
            bool getColorStatus() const;
            
            /**
             * @brief Compute the size in bytes need for a single vertex in memory
             */
            int getStorageSize() const;
            
        private:
            int coordCount;
            bool colorStatus;
            int colorCount;
            bool normals;
            int texUnitCount;
            int texCoordCount[16];
        };
    }
}

#endif  //__EXENG_GRAPHICS_VERTEXFORMAT_HPP__
