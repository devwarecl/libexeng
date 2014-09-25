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

#include <exeng/HeapBuffer.hpp>
#include <cstdlib>
#include <stdexcept>
#include <memory>

namespace exeng {
    HeapBuffer::HeapBuffer() {}

    HeapBuffer::HeapBuffer(const std::uint32_t size) {
        this->allocate(size);
    }

    Buffer::Flags HeapBuffer::getFlags() const {
        if (this->data) {
            return Buffer::Local;
        } else {
            return Buffer::Local | Buffer::Empty;
        }
    }

    void HeapBuffer::allocate(const std::uint32_t size) {
        this->release();

        this->data = std::malloc(size);
        this->size = size;
    }

    void HeapBuffer::release() {
        if (this->data) {
            std::free(this->data);

            this->data = nullptr;
            this->size = 0;
        }
    }

    HeapBuffer::~HeapBuffer() {
        this->release();
    }

    std::uint32_t HeapBuffer::getSize() const {
        return this->size;
    }

    void* HeapBuffer::getDataPtr() {
        return this->data;
    }

    const void* HeapBuffer::getDataPtr() const {
        return this->data;
    }

    void HeapBuffer::write() {}
    void HeapBuffer::read() {}

    std::uint64_t HeapBuffer::getHandle() const {
        return reinterpret_cast<std::uint64_t>(this->data);
    }

    void HeapBuffer::setData(const void* dataSrc, const std::uint32_t size) {
        this->allocate(size);
        std::memcpy(this->data, dataSrc, size);
    }

    void HeapBuffer::getData(void* dataDst, const std::uint32_t size, const std::uint32_t offset) const {
        std::memcpy(dataDst, reinterpret_cast<std::uint8_t*>(this->data) + offset, size );
    }
}
