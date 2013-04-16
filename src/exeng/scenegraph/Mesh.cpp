
#include "Mesh.hpp"
#include "MeshPart.hpp"

#include <cassert>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/checked_delete.hpp>
#include <map>

using exeng::math::Boxf;
using exeng::scenegraph::Ray;
using exeng::scenegraph::IntersectInfo;
using exeng::scenegraph::MeshPart;

typedef boost::ptr_vector<MeshPart> MeshPartVector;
typedef MeshPartVector::iterator MeshPartVectorIt;

namespace exeng {
    namespace scenegraph {
        
        inline bool isTrianglePrimitive(PrimitiveType primitive) {
            switch (primitive) {
                case PrimitiveType::TriangleFan:
                case PrimitiveType::TriangleList:
                case PrimitiveType::TriangleStrip:
                    return true;
                
                default:
                    return false;
            }
        }
        
        
        struct Mesh::Private {
            MeshPartVector  parts;
            Boxf            box;
        };
        
        
        Mesh::Mesh(int partCount) {
            
            // Hacer espacio para las partes
            this->impl = new Mesh::Private();
            this->impl->parts.reserve(partCount);
            this->impl->parts.resize(partCount);
            
            // Crear partes vacias
            for (int i=0; i<partCount; ++i) {
                this->impl->parts.push_back(new MeshPart());
            }
        }
        
        
        Mesh::~Mesh() {
            boost::checked_delete(this->impl);
        }
        
        
        Boxf Mesh::getBoundingBox() const {
            assert(this->impl != nullptr);
            return this->impl->box;
        }
        
        
        bool Mesh::hit(const Ray &ray, IntersectInfo *intersectInfo) {
            assert(this->impl != nullptr);
            
            for ( auto &meshPart : this->impl->parts) {
                if (isTrianglePrimitive(meshPart.getPrimitiveType()) == true)  {   
                    
                }
            }
            
            return false;
        }
        
        
        int Mesh::getPartCount() const {
            assert(this->impl != nullptr);
            return this->impl->parts.size();
        }
        
    
        MeshPart* Mesh::getPart(int index) {
            return &this->impl->parts[index];
        }
        
        
        const MeshPart* Mesh::getPart(int index) const {
            return &this->impl->parts[index];
        }
    }
}
