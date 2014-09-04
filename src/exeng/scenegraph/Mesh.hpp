/**
 * @file Mesh.hpp
 * @brief Mesh class definition.
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
#include <exeng/scenegraph/MeshPart.hpp>

namespace exeng { namespace scenegraph {
    /**
     * @brief Holds the geometric information about a object, composed of different MeshParts.
     * 
     * The MeshParts ARE owned by the Mesh object, and they cannot be shared.
     */
    class EXENGAPI Mesh : public Geometry {
    public:
        Mesh();

        explicit Mesh(int meshPartCount);
        
        virtual ~Mesh();
        
        void allocate(int partCount);

        /**
         * @brief Computes and returns the corresponding bounding box of the mesh.
         */
        virtual exeng::Boxf getBox() const;
        
        /**
         * @brief Checks if the specified ray intersects with the Mesh.
         */
        virtual bool hit( const exeng::scenegraph::Ray &ray, exeng::scenegraph::IntersectInfo *intersectInfo);
        
        /**
         * @brief Get the numbers of MeshParts on the Mesh.
         */
        int getPartCount() const;
        
        /**
         * @brief Get the part at the corresponding index.
         */
        MeshPart* getPart(int index);
        
        /**
         * @brief Get the part at the corresponding index.
         */
        const MeshPart* getPart(int index) const;
        
    private:
        struct Private;
        Private *impl;
    };
}}

#endif  //__EXENG_SCENEGRAPH_MESH_HPP__
