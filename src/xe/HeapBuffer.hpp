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
#include <xe/Buffer.hpp>

namespace xe {

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

		virtual void read(void* data, const int dataSize, const int dataOffset, const int bufferOffset) const override;

		virtual void write(const void* data, const int dataSize, const int dataOffset, const int bufferOffset) override;

		inline void read(void* data) const {
			this->read(data, this->getSize(), 0, 0);
		}

		inline void write(const void* data) {
			this->write(data, this->getSize(), 0, 0);
		}

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

	typedef std::unique_ptr<HeapBuffer> HeapBufferPtr;
}

#endif // __EXENG_HEAPBUFFER_HPP__
