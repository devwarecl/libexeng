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

#include "Mesh.hpp"

#include <cassert>
#include <map>
#include <boost/checked_delete.hpp>
#include <exeng/Vector.hpp>
#include <exeng/graphics/VertexArray.hpp>

using namespace xe::sg;

namespace xe { namespace gfx {
    typedef std::vector<std::unique_ptr<MeshSubset>> MeshSubsetVector;

    /**
     * @brief 
     */
    class VertexArrayAdapter {
    public:
        VertexArrayAdapter(Buffer *vertexBuffer_) : vertexBuffer(vertexBuffer_) {}
        ~VertexArrayAdapter() {}
        
        template<typename FieldType>
        FieldType& getField();
        
    private:
        Buffer *vertexBuffer = nullptr;
        void *data = nullptr;
    };
    
    /**
     * @brief Computes the normal vector, in clockwise order, to the
     * triangle conformed by the points P1, P2, P3.
     */
    inline Vector3f computeNormal(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3) {
		return normalize(cross(p2 - p1, p3 - p1));
    }
    
    /**
     * @brief Convert a triangle primitive type to a zero based index.
     */
    inline int trianglePrimitiveToIndex(Primitive::Enum primitive) {
        assert(Primitive::isTriangle(primitive));
        
        switch (primitive) {
            case Primitive::TriangleList:   return 0;
            case Primitive::TriangleStrip : return 1;
            case Primitive::TriangleFan:    return 2;
            
            default: assert(false);
        }
    }
    
    /**
     * @brief Check if the specified ray intersects with the triangle defined by the points p1, p2, p3 and the normal n.
     */
    inline bool intersectWithTriangle(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3, const Vector3f &n, 
                                      const Ray &ray, 
                                      IntersectInfo *intersectInfo=nullptr) 
	{
        IntersectInfo info;
       
        if (Plane(p1, n).intersect(ray, &info) == false) {
            if (intersectInfo != nullptr) {
                intersectInfo->intersect = false;
            }
            
            return false;
        }
        
        // Check triangle collision
        Vector3f r0 = ray.getPointAt(info.distance);
        Vector3f p = ray.getPoint(), q=r0;
        Vector3f a = p1, b=p2, c=p3;
        
        Vector3f pq = (q - p);
        Vector3f pa = (a - p);
        Vector3f pb = (b - p);
        Vector3f pc = (c - p);
        
        float u = dot(pq, pc, pb);
        float v = dot(pq, pa, pc);
        float w = dot(pq, pb, pa);
        
        // Check collision exists
        if ((u > 0.0f && v > 0.0f && w > 0.0f) == true || (u < 0.0f && v < 0.0f && w < 0.0f) == true) {
            if (intersectInfo != nullptr) {
                intersectInfo->intersect = true;
                intersectInfo->distance = info.distance;
                intersectInfo->material = nullptr;
                intersectInfo->normal = n;
            }
            
            return true;
        } else {
            //! TODO: Check with a epsilon
            return false;
        }
    }
    
    inline int getTriangleCount(int vertexCount, Primitive::Enum trianglePrimitive) {
        assert(Primitive::isTriangle(trianglePrimitive));
        
        switch (trianglePrimitive) {
            case Primitive::TriangleStrip:
            case Primitive::TriangleFan:
                return vertexCount - 2;
                
            case Primitive::TriangleList:
                return vertexCount / 3;
                
            default: 
                assert(false);
                return 0;
        }
    }
    
    inline int getVertexIndex_TriangleList(int triangleIndex, int pointIndex) {
        assert(pointIndex >= 0);
        assert(pointIndex <= 3);
        
        return triangleIndex*3 + pointIndex;
    }
    
    inline int getVertexIndex_TriangleStrip(int triangleIndex, int pointIndex) {
        assert(pointIndex >= 0);
        assert(pointIndex <= 3);
        
        if (triangleIndex%2 == 0) {
            return triangleIndex*3 + pointIndex;
        } else {
            // TODO: Correct this approach
            switch (pointIndex) {
                case 0: return triangleIndex;
                case 1: return triangleIndex + 2;
                case 2: return triangleIndex + 1;
                default: assert(false); return 0;
            }
        }
    }
    
    inline int getVertexIndex_TriangleFan(int triangleIndex, int pointIndex) {
        assert(pointIndex >= 0);
        assert(pointIndex <= 3);
        
        if (pointIndex == 0) {
            return 0;
        } else {
            switch (pointIndex) {
                case 1: return triangleIndex + 2;
                case 2: return triangleIndex + 1;
                default: assert(false);
            }
        }
        
        return triangleIndex*3 + pointIndex;
    }

    /**
     * @brief Detect intersection between a Ray and a MeshPart.
     */
    inline bool meshSubsetIntersect(MeshSubset *subset, const Ray &ray, IntersectInfo *intersectInfo=nullptr) {
        if (Primitive::isTriangle(subset->getPrimitive()) == false) {
            return false;
        }
        
        Primitive::Enum type = subset->getPrimitive();
        Buffer *vertexBuffer = subset->getBuffer(0);
        
        VertexFormat vertexFormat = subset->getVertexFormat();
        const void* vertexData = vertexBuffer->getPointer();
        
        int vertexOffset = vertexFormat.getAttribOffset(VertexAttrib::Position);
        int vertexStride = vertexFormat.getSize();
        
        // TODO: Handle properly the vertex format
        IntersectInfo info;
        
        int triangleCount = getTriangleCount(vertexBuffer->getSize() / vertexFormat.getSize(), subset->getPrimitive());
        
        for (int triangleIndex=0; triangleIndex<triangleCount; triangleIndex++) {
            IntersectInfo localInfo;
            
            // Get the triangle points, based on the triangle type and the vertex format
            int i1, i2, i3;
            
            switch (type) {
                case Primitive::TriangleList:
                    i1 = getVertexIndex_TriangleList(triangleIndex, 0);
                    i2 = getVertexIndex_TriangleList(triangleIndex, 1);
                    i3 = getVertexIndex_TriangleList(triangleIndex, 2);
                    break;
                    
                case Primitive::TriangleStrip:
                    i1 = getVertexIndex_TriangleStrip(triangleIndex, 0);
                    i2 = getVertexIndex_TriangleStrip(triangleIndex, 1);
                    i3 = getVertexIndex_TriangleStrip(triangleIndex, 2);
                    break;
                    
                case Primitive::TriangleFan:
                    i1 = getVertexIndex_TriangleFan(triangleIndex, 0);
                    i2 = getVertexIndex_TriangleFan(triangleIndex, 1);
                    i3 = getVertexIndex_TriangleFan(triangleIndex, 2);
                    break;
                    
                default: assert(false);
            }
            
            // TODO: Get the normal vector from the mesh data, if exists.
            const Vector3f &p1 = *reinterpret_cast<const Vector3f*>(static_cast<const float*>(vertexData) + i1*vertexStride + vertexOffset);
            const Vector3f &p2 = *reinterpret_cast<const Vector3f*>(static_cast<const float*>(vertexData) + i2*vertexStride + vertexOffset);
            const Vector3f &p3 = *reinterpret_cast<const Vector3f*>(static_cast<const float*>(vertexData) + i3*vertexStride + vertexOffset);
            
            Vector3f n = computeNormal(p1, p2, p3);
            
            if (intersectWithTriangle(p1, p2, p3, n, ray, &localInfo) && localInfo.distance >= 0.0f ) {
                localInfo.material = subset->getMaterial();
                if (localInfo.distance > info.distance) {
                    info = localInfo;
                }
            }
        }
        
        if (intersectInfo) {
            *intersectInfo = info;
        }
        
        return info.intersect;
    }
}}

/*
 * Mesh implementation
 */
namespace xe { namespace gfx {
    struct Mesh::Private {
        MeshSubsetVector    subsets;    //! Vector of MeshPart pointers
        Boxf                box;        //! Mesh collision box.
    };
    
    Mesh::Mesh(std::unique_ptr<xe::gfx::MeshSubset> subset) : impl(new Mesh::Private()) {
        this->impl->subsets.push_back(std::move(subset));
    }

    Mesh::Mesh(std::vector<std::unique_ptr<xe::gfx::MeshSubset>> subsets) : impl(new Mesh::Private()) {
        this->impl->subsets = std::move(subsets);
    }
    
    Mesh::~Mesh() {
        boost::checked_delete(this->impl);
    }
    
    Boxf Mesh::getBox() const {
        assert(this->impl != nullptr);
        
        /*
        MeshParVector &parts = this->impl->parts;
        Boxf box = parts[0].getBox();
    
        for(MeshPart &part : parts) {
            box.expand(part. );
        }
        
        return box;
        */
        
        return Boxf();
    }
    
    bool Mesh::hit(const Ray &ray, IntersectInfo *intersectInfo) {
        assert(this->impl != nullptr);
        
		IntersectInfo info = {}, bestInfo = {};
        
        for (auto &subset : this->impl->subsets) {
            if (meshSubsetIntersect(subset.get(), ray, &info) && info.distance >= 0.0f ) {
                if (info.distance > bestInfo.distance) {
                    bestInfo = info;
                }
            }
        }
        
        if (intersectInfo) {
            *intersectInfo = bestInfo;
        }
        
        return bestInfo.intersect;
    }
    
    int Mesh::getSubsetCount() const {
        assert(this->impl != nullptr);
        return static_cast<int>(this->impl->subsets.size());
    }
    
    MeshSubset* Mesh::getSubset(int index) {
		assert(this->impl != nullptr);
        return this->impl->subsets[index].get();
    }
    
    const MeshSubset* Mesh::getSubset(int index) const {
		assert(this->impl != nullptr);
        return this->impl->subsets[index].get();
    }

    TypeInfo Mesh::getTypeInfo() const {
		assert(this->impl != nullptr);
        return TypeId<Mesh>();
    }
}}
