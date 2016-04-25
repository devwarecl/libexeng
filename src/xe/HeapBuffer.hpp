
#pragma once

#ifndef __xe_heapbuffer__
#define __xe_heapbuffer__

#include <memory>
#include <vector>
#include <xe/Buffer.hpp>

namespace xe {
	/**
	 * @brief Heap-memory based buffer
	 */
	class EXENGAPI HeapBuffer : public Buffer {
	public:
		HeapBuffer() {}

		explicit HeapBuffer(const int size) {
			alloc(size);
		}

		explicit HeapBuffer(const int size, const void* data) {
			alloc(size);
			write(data);
		}

		virtual ~HeapBuffer() {
			free();
		}

		void alloc(const int size);

		void free();

		virtual std::size_t getSize() const override {
			return size;
		}

		virtual void read(void* destination, const int size = 0, const int offset = 0, const int destination_offset = 0) const override;

		virtual void write(const void *source, const int size = 0, const int offset = 0, const int source_offset = 0) override;

	private:
		std::uint8_t* data = nullptr;
		std::size_t size = 0;
	};
}

#endif // __EXENG_HEAPBUFFER_HPP__
