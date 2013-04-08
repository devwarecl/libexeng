
#include "Mesh.hpp"
#include <vector>
#include <cassert>

namespace exeng {
    namespace scenegraph {
        using exeng::math::Boxf;
        using exeng::scenegraph::Ray;
        using exeng::scenegraph::IntersectInfo;
        
        typedef std::vector<MeshPart*> MeshPartVector;
        typedef MeshPartVector::iterator MeshPartVectorIt;
        
        struct Mesh::Private {
            MeshPartVector  meshParts;
            Boxf            box;
        };
        
        
        Mesh::Mesh(int meshPartCount) {
            this->impl = new Mesh::Private();
        }
        
        
        Mesh::~Mesh() {
            delete this->impl;
        }
        
        
        Boxf Mesh::getBoundingBox() const {
            assert(this->impl != nullptr);
            return Boxf();
        }
        
        
        bool Mesh::hit(const Ray &ray, IntersectInfo *intersectInfo) {
            assert(this->impl != nullptr);
            return false;
        }
        
        
        int Mesh::getMeshPartCount() const {
            assert(this->impl != nullptr);
            return this->impl->meshParts.size();
        }
    }
}
