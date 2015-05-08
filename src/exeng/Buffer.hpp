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
#include <exeng/Object.hpp>
#include <exeng/Enum.hpp>
#include <exeng/TFlags.hpp>

namespace exeng {
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
		virtual void getData(void* data, const int dataSize, const int dataOffset, const int bufferOffset) const = 0;

		virtual void getData(void* data) const {
			this->getData(data, this->getSize(), 0, 0);
		}

		/**
		 * @brief Set buffer data
		 */
		virtual void setData(const void *data, const int dataSize, const int dataOffset, const int bufferOffset) = 0;

		virtual void setData(const void* data) {
			this->setData(data, this->getSize(), 0, 0);
		}

		/**
		 * @brief Get a pointer to a read-only location
		 */
		virtual const void* getPointer() const = 0;

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
