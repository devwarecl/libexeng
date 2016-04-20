
#pragma once

#ifndef __xe_stackbuffer__
#define __xe_stackbuffer__

#include <cstring>
#include <xe/Buffer.hpp>

namespace xe {
	/**
	 * @brief Stack-memory based buffer
	 */
	template<std::size_t Size>
	class StackBuffer : public Buffer {
	public:
		static_assert(Size > 0);

	public:
        StackBuffer() {}

        virtual std::size_t getSize() const override {
            return Size;
        }
        
		virtual void read(void* destination, const int size = 0, const int offset = 0, const int destination_offset = 0) const override {
			assert(destination);
			assert(false);
		}

		virtual void write(const void *source, const int size = 0, const int offset = 0, const int source_offset = 0) override {
			assert(source);
			assert(false);
		}

	private:
		std::uint8_t data[Size];
	};
}

#endif	
