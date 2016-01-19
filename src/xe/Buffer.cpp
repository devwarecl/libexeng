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

#include <xe/Buffer.hpp>
#include <xe/Exception.hpp>

namespace xe {

	void Buffer::read(void* dst_data, const int read_size, const int dst_offset, const int src_offset) const {
		BufferLockerConst<void> locker(this);

#if defined (EXENG_DEBUG)
		if (src_offset + read_size > this->getSize()) {
			EXENG_THROW_EXCEPTION("Buffer overrun.");
		}
#endif
		const void *src_data = locker.getPointer();

		std::memcpy(
			static_cast<char*>(dst_data) + dst_offset,
			static_cast<const char*>(src_data) + src_offset,
			read_size
		);
	}

	void Buffer::write(const void *src_data, const int write_size, const int src_offset, const int dst_offset) {
		BufferLocker<void> locker(this, xe::BufferLockMode::Write);

#if defined (EXENG_DEBUG)
		if (src_offset + write_size > this->getSize()) {
			EXENG_THROW_EXCEPTION("Buffer overrun.");
		}
#endif
		void *dst_data = locker.getPointer();

#if defined(EXENG_DEBUG)
		if (dst_data == nullptr) {
			EXENG_THROW_EXCEPTION("Direct-access pointer to the buffer is a nullptr (forgot to override Buffer::getPointer?)");
		}
#endif
		std::memcpy(
			static_cast<char*>(dst_data) + dst_offset,
			static_cast<const char*>(src_data) + src_offset,
			write_size
		);
	}

	std::string Buffer::toString() const {
		BufferLockerConst<void> locker(this);

		std::string dataStr;

		dataStr.resize(this->getSize());
		std::memcpy(const_cast<char*>(dataStr.c_str()), locker.getPointer(), this->getSize());

		return dataStr;
	}
}
