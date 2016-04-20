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

#pragma once

#ifndef __xe_buffer__
#define __xe_buffer__

#include <memory>
#include <cstdint>
#include <xe/Object.hpp>

namespace xe {

	/**
	 * @brief Memory area abstraction
	 */
	class EXENGAPI Buffer : public Object {
	public:
		typedef std::unique_ptr<Buffer> Ptr;

	public:
		virtual ~Buffer() {}

		/**
		 * @brief Get the size of the buffer, in bytes.
		 */
		virtual std::size_t getSize() const = 0;

		/**
		 * @brief Read the buffer data into a user-defined memory region.
		 */
		virtual void read(void* destination, const int size = 0, const int offset = 0, const int destination_offset = 0) const = 0;

		/**
		 * @brief Write a user-defined memory region to the buffer
		 */
		virtual void write(const void *source, const int size = 0, const int offset = 0, const int source_offset = 0) = 0;

		/**
		 * @brief Get a hex-dump of the buffer.
		 */
		virtual std::string toString() const override;
	};
}

#endif
