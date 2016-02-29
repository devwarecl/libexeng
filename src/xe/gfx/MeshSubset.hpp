
#ifndef __EXENG_GRAPHICS_MESHSUBSET_HPP__
#define __EXENG_GRAPHICS_MESHSUBSET_HPP__

#include <vector>
#include <memory>

#include <xe/Object.hpp>
#include <xe/Buffer.hpp>
#include <xe/HeapBuffer.hpp>
#include <xe/Forward.hpp>
#include <xe/gfx/Primitive.hpp>
#include <xe/gfx/VertexFormat.hpp>
#include <xe/gfx/IndexFormat.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/Primitive.hpp>

namespace xe { namespace gfx {

	struct MeshSubsetFormat {
		VertexFormat vertexFormat;
		IndexFormat::Enum indexFormat = IndexFormat::Unknown;
	};

	struct EXENGAPI MeshSubsetData {
		MeshSubsetData() {}

		virtual int getBufferCount() const = 0;
		virtual Buffer* getBuffer(const int index) = 0;
		virtual const Buffer* getBuffer(const int index) const = 0;
		
		virtual Buffer* getIndexBuffer() = 0;
		virtual const Buffer* getIndexBuffer() const = 0;
	};

	typedef std::unique_ptr<MeshSubsetData> MeshSubsetDataPtr;

	template<typename BufferImpl>
	struct MeshSubsetDataImpl : public MeshSubsetData {
		MeshSubsetDataImpl() {}

		explicit MeshSubsetDataImpl(const MeshSubsetData &other) {
            // initialize the local buffer array from other one
			buffers.reserve(other.getBufferCount());

			for (int i=0; i<other.getBufferCount(); i++) {
				const Buffer *buffer = other.getBuffer(i);

                xe::BufferLocker<void> locker(buffer);
                
				buffers.push_back(BufferImpl(locker.getPointer(), buffer->getSize()));
			}

            // initialize the index buffer
			const Buffer *buffer = other.getIndexBuffer();
            
            xe::BufferLocker<void> locker(buffer);
            
			ibuffer = BufferImpl(locker.getPointer(), buffer->getSize());
		}

		~MeshSubsetDataImpl() {}

		virtual int getBufferCount() const override {
			return buffers.size();
		}

		virtual Buffer* getBuffer(const int index) override {
			return &buffers[index];
		}

		virtual const Buffer* getBuffer(const int index) const override {
			return &buffers[index];
		}

		virtual Buffer* getIndexBuffer() override {
			return &ibuffer;
		}

		virtual const Buffer* getIndexBuffer() const override {
			return &ibuffer;
		}

	public:
		std::vector<BufferImpl> buffers;
		BufferImpl ibuffer;
	};

	typedef MeshSubsetDataImpl<HeapBuffer> MeshSubsetDataHeap;

	/**
     * @brief 
     */
    class MeshSubset2 : public Object {
    public:
		MeshSubset2() {}

		virtual ~MeshSubset2() {}

		void setGPUData(MeshSubsetDataPtr gpu_data) {
			this->gpu_data = std::move(gpu_data);
		}

		MeshSubsetData* getGPUData() {
			return gpu_data.get();
		}

		const MeshSubsetData* getGPUData() const {
			return gpu_data.get();
		}

        MeshSubsetFormat getFormat() const {
			return format;
		}
		
		MeshSubsetDataImpl<HeapBuffer>* getData() {
			return &data;
		}

		const MeshSubsetDataImpl<HeapBuffer>* getData() const {
			return &data;
		}

        Primitive::Enum getPrimitive() const {
			return primitive;
		}

        void setPrimitive(Primitive::Enum primitiveType) {
			primitive = primitiveType;
		}

		Material* getMaterial() {
			return material;
		}

        const Material* getMaterial() const {
			return material;
		}

        void setMaterial(Material *material) {
			this->material = material;
		}

	protected:
		MeshSubsetFormat format;
		Primitive::Enum primitive = Primitive::TriangleList;
		MeshSubsetDataImpl<HeapBuffer> data;
		Material *material = nullptr;
		MeshSubsetDataPtr gpu_data;
    };
	
	/**
     * @brief MeshSubset
     **/
    class EXENGAPI MeshSubset : public Object {
    public:
        virtual ~MeshSubset();

        virtual const VertexFormat* getFormat() const = 0;
        virtual IndexFormat::Enum getIndexFormat() const = 0;

        virtual int getBufferCount() const = 0;
        virtual Buffer* getBuffer(const int index) = 0;
        virtual const Buffer* getBuffer(const int index) const = 0;

        virtual Buffer* getIndexBuffer() = 0;
        virtual const Buffer* getIndexBuffer() const = 0;

        virtual Primitive::Enum getPrimitive() const = 0;
        virtual void setPrimitive(Primitive::Enum primitiveType) = 0;

        virtual const Material* getMaterial() const = 0;
        virtual void setMaterial(const Material *material) = 0;
        
        int getSize() const {
			int size = 0;
        
			for (int i=0; i<this->getBufferCount(); ++i) {
				size += this->getBuffer(i)->getSize();
			}
        
			return size;
		}

		int getVertexCount() const {
			return this->getSize() / this->getFormat()->getSize();
		}

		int getIndexCount() const {
			const int indexSize = IndexFormat::getSize(this->getIndexFormat());
			const int indexCount = this->getIndexBuffer()->getSize() / indexSize;

			return indexCount;
		}

        std::unique_ptr<MeshSubset> clone() const {
            return std::unique_ptr<MeshSubset>(this->cloneImpl());
        }

    protected:
        virtual MeshSubset* cloneImpl() const override = 0;
    };
    
	typedef std::unique_ptr<MeshSubset> MeshSubsetPtr;
}}

#endif  // __EXENG_GRAPHICS_MESHSUBSET_HPP__
