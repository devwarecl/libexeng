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

#include <memory>
#include <vector>
#include <exeng/graphics/MeshSubset.hpp>
#include <exeng/scenegraph/Geometry.hpp>

namespace exeng { namespace scenegraph {
    /**
     * @brief Holds the geometric information about a object, composed of different MeshParts.
     * 
     * The MeshParts ARE owned by the Mesh object, and they cannot be shared.
     */
    class EXENGAPI Mesh : public Geometry {
    public:
        explicit Mesh(std::unique_ptr<exeng::graphics::MeshSubset> subset);
        explicit Mesh(std::vector<std::unique_ptr<exeng::graphics::MeshSubset>> subsets);
        
        virtual ~Mesh();
        
        /**
         * @brief Computes and returns the corresponding bounding box of the mesh.
         */
        virtual Boxf getBox() const;
        
        /**
         * @brief Checks if the specified ray intersects with the Mesh.
         */
        virtual bool hit( const Ray &ray, IntersectInfo *intersectInfo);
        
        /**
         * @brief Get the numbers of MeshParts on the Mesh.
         */
        int getMeshSubsetCount() const;
        
        /**
         * @brief Get the part at the corresponding index.
         */
        exeng::graphics::MeshSubset* getMeshSubset(int index);
        
        /**
         * @brief Get the part at the corresponding index.
         */
        const exeng::graphics::MeshSubset* getMeshSubset(int index) const;
        
    private:
        struct Private;
        Private *impl = nullptr;
    };
}}

#endif  //__EXENG_SCENEGRAPH_MESH_HPP__
