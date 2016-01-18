
#ifndef __EXENG_GRAPHICS_MESHSUBSETBASE_HPP__
#define __EXENG_GRAPHICS_MESHSUBSETBASE_HPP__

#include <xe/gfx/MeshSubset.hpp>
#include <memory>
#include <vector>

namespace xe { namespace gfx {

	template<typename BufferImpl>
    class MeshSubsetBase : public MeshSubset {
    public:
		MeshSubsetBase() {}
        virtual VertexFormat getFormat() const override;
        virtual IndexFormat::Enum getIndexFormat() const override;

        virtual int getBufferCount() const override;
        virtual BufferImpl* getBuffer(const int index) override;
        virtual const BufferImpl* getBuffer(const int index) const override;

        virtual BufferImpl* getIndexBuffer() override;
        virtual const BufferImpl* getIndexBuffer() const override;

        virtual Primitive::Enum getPrimitive() const override;
        virtual void setPrimitive(Primitive::Enum primitiveType) override;

        virtual const Material* getMaterial() const override;
        virtual void setMaterial(const Material *material) override;

    protected:
		typedef std::unique_ptr<BufferImpl> BufferImplPtr;

        std::vector<BufferImplPtr> buffers;
        BufferImplPtr indexBuffer;
        VertexFormat vertexFormat;
        IndexFormat::Enum indexFormat = IndexFormat::Unknown;
        Primitive::Enum primitiveType = Primitive::TriangleList;
        const Material *material = nullptr;
    };

	template<typename BufferImpl>
    inline int MeshSubsetBase<BufferImpl>::getBufferCount() const {
		assert(this);

        return this->buffers.size();
    }

	template<typename BufferImpl>
    inline BufferImpl* MeshSubsetBase<BufferImpl>::getBuffer(const int index) {
		assert(this);

        return this->buffers[index].get();
    }

	template<typename BufferImpl>
    inline const BufferImpl* MeshSubsetBase<BufferImpl>::getBuffer(const int index) const {
		assert(this);

        return this->buffers[index].get();
    }

	template<typename BufferImpl>
    inline BufferImpl* MeshSubsetBase<BufferImpl>::getIndexBuffer() {
		assert(this);

        return this->indexBuffer.get();
    }

	template<typename BufferImpl>
    inline const BufferImpl* MeshSubsetBase<BufferImpl>::getIndexBuffer() const {
		assert(this);

        return this->indexBuffer.get();
    }

	template<typename BufferImpl>
    inline VertexFormat MeshSubsetBase<BufferImpl>::getFormat() const {
		assert(this);

        return this->vertexFormat;
    }

	template<typename BufferImpl>
    inline IndexFormat::Enum MeshSubsetBase<BufferImpl>::getIndexFormat() const {
		assert(this);

        return this->indexFormat;
    }

	template<typename BufferImpl>
    inline Primitive::Enum MeshSubsetBase<BufferImpl>::getPrimitive() const {
		assert(this);

        return this->primitiveType;
    }

	template<typename BufferImpl>
    inline void MeshSubsetBase<BufferImpl>::setPrimitive(Primitive::Enum primitiveType) {
		assert(this);

        this->primitiveType = primitiveType;
    }

	template<typename BufferImpl>
    inline const Material* MeshSubsetBase<BufferImpl>::getMaterial() const {
		assert(this);

        return this->material;
    }

	template<typename BufferImpl>
    inline void MeshSubsetBase<BufferImpl>::setMaterial(const Material *material) {
		assert(this);

        this->material = material;
    }
}}

#endif
