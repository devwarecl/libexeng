
#include "GL3MeshSubset.hpp"

namespace exeng { namespace graphics { namespace gl3 {
    GL3MeshSubset::GL3MeshSubset(std::vector<std::unique_ptr<Buffer>> vertexBuffers , const VertexFormat &format) : MeshSubsetBase(std::move(vertexBuffers), format) {
#if defined(EXENG_DEBUG)
        if (this->buffers.size() == 0) {
            throw std::runtime_error("GL3MeshSubset::GL3MeshSubset -> The vertex buffer vector must contain at least one element.");
        }
#endif
        // TODO: Implement the state change associated to the mesh subset here, and not in the 
        // GL3GraphicsDriver::setMeshSubset method call.
        ::glGenVertexArrays(1, &this->vertexArrayId);
    }

    GL3MeshSubset::~GL3MeshSubset() {
        if (this->vertexArrayId) {
            ::glDeleteVertexArrays(1, &this->vertexArrayId);
            this->vertexArrayId = 0;
        }
    }

    TypeInfo GL3MeshSubset::getTypeInfo() const {
        return TypeId<GL3MeshSubset>();
    }
}}}
