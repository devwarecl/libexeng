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

#ifndef __EXENG_GRAPHICS_MESH_HPP__
#define __EXENG_GRAPHICS_MESH_HPP__

#include <memory>
#include <vector>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/sg/Geometry.hpp>
#include <xe/sg/Plane.hpp>
#include <xe/sg/Box.hpp>
#include <xe/sg/IntersectInfo.hpp>

namespace xe { namespace gfx {
	
    /**
     * @brief Holds the geometric information about a object, composed of different MeshSubset.
     */
    class EXENGAPI Mesh : public xe::sg::Geometry {
    public:
        explicit Mesh(MeshSubsetPtr subset);
        explicit Mesh(std::vector<MeshSubsetPtr> subsets);
        
        virtual ~Mesh();
        
        /**
         * @brief Computes and returns the corresponding bounding box of the mesh.
         */
        virtual Boxf getBox() const override;
        
        /**
         * @brief Checks if the specified ray intersects with the Mesh.
         */
        virtual bool hit(const xe::sg::Ray &ray, xe::sg::IntersectInfo *intersectInfo) override;
        
        /**
         * @brief Get the numbers of MeshParts on the Mesh.
         */
        int getSubsetCount() const;
        
        /**
         * @brief Get the part at the corresponding index.
         */
        MeshSubset* getSubset(int index);
        
        /**
         * @brief Get the part at the corresponding index.
         */
        const MeshSubset* getSubset(int index) const;
        
        virtual TypeInfo getTypeInfo() const override;
		
		virtual void renderWith(xe::sg::Renderer *renderer) override;

    private:
        struct Private;
        Private *impl = nullptr;
    };

	typedef std::unique_ptr<Mesh> MeshPtr;
}}

#endif 
