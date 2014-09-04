
#include <memory>
#include <exeng/graphics/MeshSubset.hpp>

namespace exeng { namespace graphics {

    struct MeshSubset::Private {
        std::vector<std::unique_ptr<VertexBuffer>> vertexBuffers;
        std::unique_ptr<IndexBuffer> indexBuffer;
    };

    MeshSubset::MeshSubset(const std::vector<VertexBuffer*> &vertexBuffers, IndexBuffer *indexBuffer) : impl(new MeshSubset::Private()) {
        for (VertexBuffer *vertexBuffer : vertexBuffers) {
            this->impl->vertexBuffers.push_back(std::unique_ptr<VertexBuffer>(vertexBuffer));
        }

        this->impl->indexBuffer = std::unique_ptr<IndexBuffer>(indexBuffer);
    }

    MeshSubset::~MeshSubset() {
        delete impl;
    }
}}
