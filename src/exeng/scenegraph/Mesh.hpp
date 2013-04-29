
#ifndef __EXENG_SCENEGRAPH_MESH_HPP__
#define __EXENG_SCENEGRAPH_MESH_HPP__

#include "Geometry.hpp"

namespace exeng {
    namespace scenegraph {
        class EXENGAPI MeshPart;
        
        /**
         *  @brief Almacena la informacion geometrica de un objeto compuesto por primitivas
         */
        class EXENGAPI Mesh : public Geometry {
        public:
            
            explicit Mesh(int meshPartCount);
            
            virtual ~Mesh();
            
            /**
             * @brief Calcula la caja de colision actual para el objeto actual.
             * 
             * Esta implementacion asume que todos los mesh parts no son punteros nulos, ni vacios.
             */
            virtual exeng::math::Boxf getBoundingBox() const;
            
            virtual bool hit( const exeng::scenegraph::Ray &ray, exeng::scenegraph::IntersectInfo *intersectInfo);
            
            
            /**
             * @brief Devuelve la cantidad total de MeshSubset's contenidos en la malla.
             */
            int getPartCount() const;
            
            
            /**
             * @brief Devuelve el meshsubset contenido en el indice indicado
             */
            MeshPart* getPart(int index);
            
            
            /**
             * @brief Devuelve el meshsubset contenido en el indice indicado
             */
            const MeshPart* getPart(int index) const;
            
            /**
             * @brief Establece la parte de la malla indicada.
             */
            void setPart(int index, MeshPart *part);
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif  //__EXENG_SCENEGRAPH_MESH_HPP__
