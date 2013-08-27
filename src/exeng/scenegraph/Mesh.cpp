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

#include <exeng/math/TVector.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/scenegraph/MeshPart.hpp>
#include <exeng/scenegraph/Plane.hpp>
#include <exeng/graphics/VertexArray.hpp>

#include <cassert>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/checked_delete.hpp>
#include <map>

using namespace exeng;
using namespace exeng::math;
using namespace exeng::scenegraph;
using namespace exeng::graphics;

typedef boost::ptr_vector<MeshPart> MeshPartVector;
typedef MeshPartVector::iterator MeshPartVectorIt;

namespace exeng {
namespace scenegraph {

struct Triangle {
    Vector3f &p1;
    Vector3f &p2;
    Vector3f &p3;
    
    Triangle(Vector3f &P1, Vector3f &P2, Vector3f &P3) : p1(P1), p2(P2), p3(P3) {}
    
    Vector3f getNormal() const {
        Vector3f v1 = p2 - p1;
        Vector3f v2 = p3 - p1;
        Vector3f n = v1.cross(v2);
        
        n.normalize();
        
        return n;
    }
};


class TriangleArray {
public:
    TriangleArray (VertexBuffer *vertexBuffer) : 
        vertices(vertexBuffer) {
    }
    
    virtual ~TriangleArray()  { }
    
    /**
     * @brief Devuelve la cantidad de triangulos
     */
    virtual int size() const = 0;
    
    /**
     * @brief Devuelve el triangulo que se encuentre en el indice indicado.
     */
    virtual Triangle triangle(int index) = 0;
    
    
protected:
    VertexArray<Vertex> vertices;
};


class TriangleListArray : public TriangleArray {
public:
    TriangleListArray(VertexBuffer *vertexBuffer) : TriangleArray(vertexBuffer) {
    }
    
    virtual ~TriangleListArray() {}
    
    virtual int size() const {
        return this->vertices.size() / 3;
    }
    
    virtual Triangle triangle(int index) {
        if (index >= this->size()) {
            throw std::runtime_error("");
        }
        
        Vector3f &p1 = this->vertices[3*index + 0].coord;
        Vector3f &p2 = this->vertices[3*index + 1].coord;
        Vector3f &p3 = this->vertices[3*index + 2].coord;
        
        return Triangle(p1, p2, p3);
    }
};


class TriangleStripArray : public TriangleArray {
public:
    TriangleStripArray(VertexBuffer *vertexBuffer) : TriangleArray(vertexBuffer) {
    }
    
    virtual ~TriangleStripArray() {}
    
    virtual int size() const {
        return this->vertices.size() - 2;
    }
    
    virtual Triangle triangle(int index) {
        if (index >= this->size()) {
            throw std::runtime_error("");
        }
        
        if (index%2 == 0) {
            Vector3f &p1 = this->vertices[index + 0].coord;
            Vector3f &p2 = this->vertices[index + 1].coord;
            Vector3f &p3 = this->vertices[index + 2].coord;
            
            return Triangle(p1, p2, p3);
        } else {
            Vector3f &p1 = this->vertices[index + 0].coord;
            Vector3f &p2 = this->vertices[index + 2].coord;
            Vector3f &p3 = this->vertices[index + 0].coord;
            
            return Triangle(p1, p2, p3);
        }
    }
};


class TriangleFanArray : public TriangleArray {
public:
    TriangleFanArray(VertexBuffer *vertexBuffer) : TriangleArray(vertexBuffer) {
    }
    
    virtual ~TriangleFanArray() {}
    
    virtual int size() const {
        return this->vertices.size() - 2;
    }
    
    virtual Triangle triangle(int index) {
        if (index >= this->size()) {
            throw std::runtime_error("");
        }
        
        if (index%2 == 0) {
            Vector3f &p1 = this->vertices[0].coord;
            Vector3f &p2 = this->vertices[index + 1].coord;
            Vector3f &p3 = this->vertices[index + 2].coord;
            
            return Triangle(p1, p2, p3);
        } else {
            Vector3f &p1 = this->vertices[0].coord;
            Vector3f &p2 = this->vertices[index + 2].coord;
            Vector3f &p3 = this->vertices[index + 0].coord;
            
            return Triangle(p1, p2, p3);
        }
    }
};


/**
 * @brief Construye un arreglo de triangulos apropiado segun el tipo de primitiva
 */
inline TriangleArray* getTriangleArray(VertexBuffer *vb, IndexBuffer *ib, Primitive::Enum type) {
    TriangleArray* result = nullptr;
    
    switch(type) {
        case Primitive::Enum::TriangleList:   result = new TriangleListArray(vb); break;
        case Primitive::Enum::TriangleStrip:  result = new TriangleStripArray(vb);break;
        case Primitive::Enum::TriangleFan:    result = new TriangleFanArray(vb);  break;
        default: throw std::runtime_error("Unexpected primitive type"); break;
    }
    
    return result;
}


struct Mesh::Private {
    MeshPartVector  parts;  //! Las partes que componen a un modelo tridimensional
    Boxf box;               //! La caja colision general del modelo.
};


Mesh::Mesh(int partCount) {
    // Hacer espacio para las partes
    this->impl = new Mesh::Private();
    this->impl->parts.reserve(partCount);
    this->impl->parts.resize(partCount);
    
    // Crear partes vacias
    for (int i=0; i<partCount; ++i) {
        this->impl->parts.push_back(nullptr);
    }
}


Mesh::~Mesh() {
    boost::checked_delete(this->impl);
}


Boxf Mesh::getBox() const {
    assert(this->impl != nullptr);
    
    auto &parts = this->impl->parts;
    auto &box = this->impl->box;
    
    box = parts[0].getBox();

    for(auto &part : parts) {
        box.expand(part.getBox() );
    }
    
    return box;
}


/**
 * @brief Detecta si existe interseccion entre la parte y el rayo indicado.
 */
bool meshSubsetHit(MeshPart &meshPart, const Ray &ray, IntersectInfo *intersectInfo=nullptr) {
    
    if (Primitive::isTriangle(meshPart.getPrimitiveType()) == false) {
        return false;
    }
    
    std::unique_ptr<TriangleArray> triangleArray;
    Primitive::Enum type = meshPart.getPrimitiveType();
    VertexBuffer *vertexBuffer = meshPart.getVertexBuffer();
    IndexBuffer *indexBuffer = meshPart.getIndexBuffer();
    
    IntersectInfo lastInfo;
    IntersectInfo info;
    Plane plane;
    
    triangleArray.reset( getTriangleArray(vertexBuffer, indexBuffer, type) );
    
    for (int i=0; i<triangleArray->size(); ++i) {
        Triangle tri = triangleArray->triangle(i);
        
        // Generar un plano con los tres puntos
        plane.set(tri.p1, tri.p2, tri.p3);
        if (plane.intersect(ray, &info) == true) {
            
            // Si se intersecto con el punto, ver si el punto esta 
            // dentro de las coordenadas del triangulo        
            if (info.distance <= 0.0) {
                continue;
            }
            
            // Comprobar si el punto de interseccion pertenece al triangulo o no, usando 
            // coordenadas baricentricas
            Vector3f r0=ray.getPointAt(info.distance);
            Vector3f p=ray.getPoint(), q=r0;
            Vector3f a=tri.p1, b=tri.p2, c=tri.p3;
            
            Vector3f pq = (q - p);
            Vector3f pa = (a - p);
            Vector3f pb = (b - p);
            Vector3f pc = (c - p);
            
            float u, v, w;
            u = pq.triple(pc, pb);
            v = pq.triple(pa, pc);
            w = pq.triple(pb, pa);
            
            // Detectar si existe colision, sin importar como esten ordenados los triangulos
            bool isBackSide = (u > 0.0f && v > 0.0f && w > 0.0f);
            bool isFrontSide = (u < 0.0f && v < 0.0f && w < 0.0f);
            
            if (isBackSide == true || isFrontSide == true) {
                if (intersectInfo != nullptr){
                    intersectInfo->intersect = true;
                    intersectInfo->distance = info.distance;
                    intersectInfo->materialPtr = meshPart.getMaterial();
                    intersectInfo->normal = tri.getNormal();
                }
                
                return true;
            } else {
                //! TODO: Comprobar mediante un epsilon
                return false;
            }
        }
    }
    
    return false;
}


bool Mesh::hit(const Ray &ray, IntersectInfo *intersectInfo) {
    assert(this->impl != nullptr);
    
    IntersectInfo info, bestInfo;
    
    for (MeshPart &meshPart : this->impl->parts) {
        bool intersect = meshSubsetHit(meshPart, ray, &info);
        bool isFront =  info.distance >= 0.0;
        
        if ( intersect == true && isFront == true) {
            if (info.distance > bestInfo.distance) {
                bestInfo = info;
            }
        }
    }
    
    if (intersectInfo != nullptr) {
        *intersectInfo = bestInfo;
    }
    
    return bestInfo.intersect;
}


int Mesh::getPartCount() const {
    assert(this->impl != nullptr);
    return static_cast<int>(this->impl->parts.size());
}


MeshPart* Mesh::getPart(int index) {
    return &this->impl->parts[index];
}


const MeshPart* Mesh::getPart(int index) const {
    return &this->impl->parts[index];
}
}
}
