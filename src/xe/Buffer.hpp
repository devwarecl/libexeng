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
#include <cassert>
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

    template<int Size>
    struct StackCachePolicy {
	    explicit StackCachePolicy(int size) {
		    static_assert(Size > 0);
		    assert(Size >= size);
		    assert(size > 0);
	    }

	    std::uint8_t cache[Size];
    };

    struct HeapCachePolicy {
	    explicit HeapCachePolicy(int size) {
		    assert(size > 0);
		    cache = (std::uint8_t *) std::malloc(size);
	    }

	    ~HeapCachePolicy() {
		    std::free(cache);
	    }

	    std::uint8_t *cache = nullptr;
    };

    template<typename BufferCache, typename Type>
    class BufferWrapper {
    public:
	    BufferWrapper(BufferCache &cache_, const int size_) : cache(cache_), size(size_) {
            assert(size > 0);
            assert(sizeof(Type) % size == 0);

		    data = cache.lock();
	    }
        
	    ~BufferWrapper() {
		    cache.unlock();
	    }

        const Type& operator[](const int index) const {
            assert(index > 0);
            assert(index < this->getCount());

            return data[index];
        }

        Type& operator[](const int index) {
            assert(index > 0);
            assert(index < this->getCount());

            return data[index];
        }

        const int getCount() const {
            return sizeof(Type)/size;
        }

    private:
	    BufferCache &cache;
	    Type *data = nullptr;
        const int size;
    };

    template<typename CachePolicy>
    class BufferCache : public CachePolicy {
    public:
        typedef BufferCache<CachePolicy> BufferCacheType;

    public:
	    explicit BufferCache(Buffer* buffer_) : CachePolicy(buffer_->getSize()) {
		    assert(cache);

		    buffer = std::move(buffer_);
		    buffer->read(cache);
	    }
	
	    ~BufferCache() {}

	    void write(const void *source, const int size = 0, const int offset = 0, const int source_offset = 0) {
		    buffer->write(source, size, offset, source_offset);
	    }

	    void read(void* destination, const int size = 0, const int offset = 0, const int destination_offset = 0) const {
		    buffer->read(destination, size, offset, destination_offset);
	    }
	    
        template<typename Type>
	    BufferWrapper<BufferCacheType, Type> wrap() {
		    return BufferLocker<BufferCacheType, Type>> (*this);
	    }

        template<typename Type>
	    const BufferWrapper<const BufferCacheType, Type > wrap() const {
		    return BufferWrapper<const BufferCacheType, Type>> (*this);
	    }

	    void* lock() {
		    return cache;
	    }

	    void unlock() {
		    buffer->write(cache);
	    }

	    const void* lock() const {
		    return cache;
	    }

	    void unlock() const {}

    private:
	    Buffer* buffer = nullptr;
    };
}

#endif
