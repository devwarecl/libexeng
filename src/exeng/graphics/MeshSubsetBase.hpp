
#ifndef __EXENG_GRAPHICS_MESHSUBSETBASE_HPP__
#define __EXENG_GRAPHICS_MESHSUBSETBASE_HPP__

#include <exeng/graphics/MeshSubset.hpp>
#include <memory>
#include <vector>

namespace exeng { namespace graphics {
    class MeshSubsetBase : public MeshSubset {
    public:
		MeshSubsetBase() {}
        virtual VertexFormat getVertexFormat() const override;
        virtual IndexFormat::Enum getIndexFormat() const override;

        virtual int getBufferCount() const override;
        virtual Buffer* getBuffer(const int index) override;
        virtual const Buffer* getBuffer(const int index) const override;

        virtual Buffer* getIndexBuffer() override;
        virtual const Buffer* getIndexBuffer() const override;

        virtual Primitive::Enum getPrimitive() const override;
        virtual void setPrimitive(Primitive::Enum primitiveType) override;

        virtual const Material* getMaterial() const override;
        virtual void setMaterial(const Material *material) override;

    protected:
        std::vector<BufferPtr> buffers;
        BufferPtr indexBuffer;
        VertexFormat vertexFormat;
        IndexFormat::Enum indexFormat = IndexFormat::Unknown;
        Primitive::Enum primitiveType = Primitive::TriangleList;
        const Material *material = nullptr;
    };

    inline int MeshSubsetBase::getBufferCount() const {
        return this->buffers.size();
    }

    inline Buffer* MeshSubsetBase::getBuffer(const int index) {
        return this->buffers[index].get();
    }

    inline const Buffer* MeshSubsetBase::getBuffer(const int index) const {
        return this->buffers[index].get();
    }

    inline Buffer* MeshSubsetBase::getIndexBuffer() {
        return this->indexBuffer.get();
    }

    inline const Buffer* MeshSubsetBase::getIndexBuffer() const {
        return this->indexBuffer.get();
    }

    inline VertexFormat MeshSubsetBase::getVertexFormat() const {
        return this->vertexFormat;
    }

    inline IndexFormat::Enum MeshSubsetBase::getIndexFormat() const {
        return this->indexFormat;
    }

    inline Primitive::Enum MeshSubsetBase::getPrimitive() const {
        return this->primitiveType;
    }

    inline void MeshSubsetBase::setPrimitive(Primitive::Enum primitiveType) {
        this->primitiveType = primitiveType;
    }

    inline const Material* MeshSubsetBase::getMaterial() const {
        return this->material;
    }

    inline void MeshSubsetBase::setMaterial(const Material *material) {
        this->material = material;
    }
}}

#endif
