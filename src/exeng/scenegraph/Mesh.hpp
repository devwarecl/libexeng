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

#ifndef __EXENG_SCENEGRAPH_MESH_HPP__
#define __EXENG_SCENEGRAPH_MESH_HPP__

#include <exeng/scenegraph/Geometry.hpp>

namespace exeng { namespace scenegraph {
    
class EXENGAPI MeshPart;

/**
 * @brief Holds the geometric information about a object composed of primitives.
 */
class EXENGAPI Mesh : public Geometry {
public:
    explicit Mesh(int meshPartCount);
    
    virtual ~Mesh();
    
    /**
     * @brief Computes and returns the corresponding bounding box of the mesh.
     */
    virtual exeng::math::Boxf getBox() const;
    
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

}}

#endif  //__EXENG_SCENEGRAPH_MESH_HPP__
