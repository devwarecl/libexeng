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

#ifndef __EXENG_HEAPBUFFER_HPP__
#define __EXENG_HEAPBUFFER_HPP__

#include <memory>
#include <exeng/Buffer.hpp>

namespace exeng {

	/**
	 * @brief Implementation of the buffer class, for heap memory.
	 */
	class EXENGAPI HeapBuffer : public Buffer {
	public:
		/* HeapBuffer class specific methods */
		explicit HeapBuffer(const int size);

		virtual ~HeapBuffer();

		void* getPointer() {
			return this->data;
		}

		virtual const void* getPointer() const override {
			return this->data;
		}
		
		/* Buffer class overrided methods*/
		virtual int getSize() const override {
			return this->size;
		}

		virtual int getHandle() const override {
			return reinterpret_cast<int>(this);
		}

		virtual void getData(void* data, const int size, const int dataOffset, const int bufferOffset) const override;

		virtual void setData(const void *data, const int size, const int dataOffset, const int bufferOffset) override;

		/* Object class overrided methods*/

		/*
		virtual bool isClonable() const override {
			return true;
		}

		virtual HeapBuffer* clone() const override;
		*/

	private:
		void* data = nullptr;
		int size = 0;
	};

    /**
     * @brief Raw memory allocated in the heap.
     */
    class EXENGAPI HeapBuffer2 : public Buffer2 {
    public:
        HeapBuffer2();
        explicit HeapBuffer2(const std::uint32_t size);

        virtual ~HeapBuffer2();
        virtual Buffer2::Flags getFlags() const;
        virtual void allocate(const std::uint32_t size) override;
        virtual void release() override;
        virtual void* getDataPtr() override;
        virtual const void* getDataPtr() const override;
        virtual void write() override;
        virtual void read() override;
        virtual std::uint64_t getHandle() const override;
        virtual std::uint32_t getSize() const override;
        virtual void setData(const void* dataSrc, const std::uint32_t size) override;
        virtual void getData(void* dataDst, const std::uint32_t size, const std::uint32_t offset) const override;
        
    private:
        void* data = nullptr;
        std::uint32_t size = 0;
    };

	typedef std::unique_ptr<HeapBuffer> HeapBufferPtr;
}

#endif // __EXENG_HEAPBUFFER_HPP__
