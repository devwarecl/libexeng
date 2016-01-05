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

		/**
		 * @brief Get a pointer to a read-only location
		 */
		virtual const void* getPointer() const = 0;

		virtual void* getPointer() {
			return nullptr;
		}

		virtual std::string toString() const override {
			std::string dataStr;

			dataStr.resize(this->getSize());
			std::memcpy( const_cast<char*>(dataStr.c_str()), this->getPointer(), this->getSize());

			return dataStr;
		}
	};

	typedef std::unique_ptr<Buffer> BufferPtr;
}

#endif // __EXENG_BUFFER_HPP__
