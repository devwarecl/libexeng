/**
 * @file Triangle.hpp
 * @brief Defines the Triangle structure
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_SCENEGRAPH_TRIANGLE_HPP__
#define __EXENG_SCENEGRAPH_TRIANGLE_HPP__

#include <xe/sg/Plane.hpp>
#include <xe/sg/Ray.hpp>
#include <xe/sg/IntersectInfo.hpp>

namespace xe { namespace sg {
    template<typename VectorType>
    struct Triangle {
        const VectorType &p1;
        const VectorType &p2;
        const VectorType &p3;
        
        Triangle(const VectorType &p1, const VectorType &p2, const VectorType &p3);
        
        VectorType getNormal() const;
        
        VectorType getNormalUnnormalized() const;
        
        bool hit(const Ray& ray, IntersectInfo *info=nullptr) const;
    };


	template<typename Vector>
    Triangle<Vector>::Triangle(const Vector &P1, const Vector &P2, const Vector &P3) : p1(P1), p2(P2), p3(P3) {
    }


    template<typename Vector>
    Vector Triangle<Vector>::getNormal() const {
        auto normal = this->getNormalUnnormalized();
        normal.normalize();
        return normal;
    }


    template<typename Vector>
    Vector Triangle<Vector>::getNormalUnnormalized() const {
        auto v1 = p2 - p1;
        auto v2 = p3 - p1;
        auto normal = v1.cross(v2);
        
        return normal;
    }


    template<typename Vector>
    bool Triangle<Vector>::hit(const Ray& ray, IntersectInfo *info=nullptr) const {
        
        // Generar un plano con los tres puntos
        auto plane = Plane();
        
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

}}


#endif  //__EXENG_SCENEGRAPH_TRIANGLE_HPP__
