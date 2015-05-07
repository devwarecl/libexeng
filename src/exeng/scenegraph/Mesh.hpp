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
        explicit Mesh(exeng::graphics::MeshSubsetPtr subset);
        explicit Mesh(std::vector<exeng::graphics::MeshSubsetPtr> subsets);
        
        virtual ~Mesh();
        
        /**
         * @brief Computes and returns the corresponding bounding box of the mesh.
         */
        virtual Boxf getBox() const override;
        
        /**
         * @brief Checks if the specified ray intersects with the Mesh.
         */
        virtual bool hit(const Ray &ray, IntersectInfo *intersectInfo) override;
        
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
        
        virtual TypeInfo getTypeInfo() const override;

    private:
        struct Private;
        Private *impl = nullptr;
    };

	typedef std::unique_ptr<Mesh> MeshPtr;
}}

#endif  //__EXENG_SCENEGRAPH_MESH_HPP__
