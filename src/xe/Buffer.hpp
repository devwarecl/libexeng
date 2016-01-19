/**
 * @file Buffer.hpp
 * @brief Buffer class definition.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_BUFFER_HPP__
#define __EXENG_BUFFER_HPP__

#include <cstdint>
#include <memory>
#include <xe/Object.hpp>
#include <xe/Enum.hpp>
#include <xe/TFlags.hpp>

namespace xe {

	struct BufferLockMode : public Enum {
		enum Enum {
			Read = 1,
			Write = 2,
			ReadWrite = Read | Write
		};
	};

	/**
	 * @brief Class for manipulation of memory areas.
	 */
	class EXENGAPI Buffer : public Object {
	public:
		virtual ~Buffer() {}

		/**
		 * @brief Get the identifier of the buffer object.
		 */
		virtual int getHandle() const = 0;

		/**
		 * @brief Get the current size of the buffer.
		 */
		virtual int getSize() const = 0;

		/**
		 * @brief Get buffer data
		 */
		virtual void read(void* dst_data, const int read_size, const int dst_offset, const int src_offset) const;

		virtual void read(void* dst_data) const {
			this->read(dst_data, this->getSize(), 0, 0);
		}

		virtual void read(void* dst_data, const int read_size) const {
			this->read(dst_data, read_size, 0, 0);
		}

		/**
		 * @brief Set buffer data
		 */
		virtual void write(const void *src_data, const int write_size, const int src_offset, const int dst_offset);

		virtual void write(const void* src_data) {
			this->write(src_data, this->getSize(), 0, 0);
		}

		virtual void write(const void* src_data, const int write_size) {
			this->write(src_data, write_size, 0, 0);
		}

		virtual void* lock(BufferLockMode::Enum mode) = 0;

		virtual void unlock() = 0;

		virtual const void* lock() const;

		virtual void unlock() const = 0;

		virtual std::string toString() const override;
	};

	typedef std::unique_ptr<Buffer> BufferPtr;
	
	template<typename PointerType>
	class BufferLocker {
	public:
		explicit BufferLocker(Buffer *buffer, BufferLockMode::Enum mode) {
			this->buffer = buffer;
			this->pointer = reinterpret_cast<PointerType*>(this->buffer->lock(mode));
		}

		~BufferLocker() {
			this->buffer->unlock();
		}

		PointerType* getPointer() {
			return pointer;
		}

	private:
		Buffer *buffer = nullptr;
		PointerType *pointer = nullptr;
	};

	template<typename PointerType>
	class BufferLockerConst {
	public:
		explicit BufferLockerConst(const Buffer *buffer) {
			this->buffer = buffer;
			this->pointer = reinterpret_cast<const PointerType*>(this->buffer->lock());
		}

		~BufferLockerConst() {
			this->buffer->unlock();
		}

		const PointerType* getPointer() const  {
			return this->pointer;
		}

	private:
		const Buffer *buffer = nullptr;
		const PointerType *pointer = nullptr;
	};
}

#endif // __EXENG_BUFFER_HPP__
