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

#include <exeng/Buffer.hpp>

namespace exeng {
    /**
     * @brief Raw memory allocated in the heap.
     */
    class EXENGAPI HeapBuffer : public Buffer {
    public:
        HeapBuffer();
        explicit HeapBuffer(const std::uint32_t size);

        virtual ~HeapBuffer();
        virtual Buffer::Flags getFlags() const;
        virtual void allocate(const std::uint32_t size) override;
        virtual void release() override;
        virtual void* getDataPtr() override;
        virtual const void* getDataPtr() const override;
        virtual void write() override;
        virtual void read() override;
        virtual std::uint64_t getHandle() const override;
        virtual std::uint32_t getSize() const override;
        virtual void setData(const void* dataSrc, const std::uint32_t size) override;
        virtual void getData(void* dataDst, const std::uint32_t size, const std::uint32_t offset) const override;
        
    private:
        void* data = nullptr;
        std::uint32_t size = 0;
    };
}

#endif // __EXENG_HEAPBUFFER_HPP__
