/**
 * @file Buffer.hpp
 * @brief Define the Buffer abstract class.
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
     * @brief Abstract interface to a huge memory block.
     */
    class EXENGAPI Buffer : public Object {
    public:
        enum Enum {
            Empty = 0x00000001,
            Local = 0x00000002,
            __Force32 = 0xFFFFFFFF
        };

        typedef TFlags<Enum> Flags;
        
    public:
        virtual ~Buffer();

        /**
         * @brief 
         */
        virtual Buffer::Flags getFlags() const = 0;

        /**
         * @brief 
         */
        virtual void allocate(const std::uint32_t size) = 0;

        /**
         * @brief 
         */
        virtual void release() = 0;

        /**
         * @brief Get a pointer to the data. 
         * 
         * This data exist on the address space of the local process. If the buffer points to 
         * another address space (different from the local address space), it return a pointer 
         * to the address space of a local cache of the data instead.
         */
        virtual void* getDataPtr() = 0;

        /**
         * @brief 
         */
        virtual const void* getDataPtr() const = 0;

        /**
         * @brief Copy the local memory to the remote one.
         */
        virtual void write() = 0;

        /**
         * @brief Copy the remote memory to the local one.
         */
        virtual void read() = 0;

        /**
         * @brief Get the native handle of the buffer. If its a local buffer, return the value Buffer::getDataPtr
         */
        virtual std::uint64_t getHandle() const = 0;

        /**
         * @brief Gets the size of the buffer, in bytes.
         */
        virtual std::uint32_t getSize() const = 0;
        
        /**
         * @brief Copy and allocate the buffer internal data.
         */
        virtual void setData(const void* dataSrc, const std::uint32_t size) = 0;

        /**
         * @brief Copy the data of the buffer to the specified memory location.
         */
        virtual void getData(void* dataDst, const std::uint32_t size, const std::uint32_t offset) const = 0;
    };

	typedef std::unique_ptr<Buffer> BufferPtr;
}

#endif // __EXENG_BUFFER_HPP__
