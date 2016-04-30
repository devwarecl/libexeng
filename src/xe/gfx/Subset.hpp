
#pragma once

#ifndef __xe_gfx_meshsubset__
#define __xe_gfx_meshsubset__

#include <memory>
#include <array>
#include <xe/Buffer.hpp>
#include <xe/Forward.hpp>
#include <xe/DataType.hpp>
#include <xe/gfx/BufferType.hpp>

namespace xe { namespace gfx {

    /**
     * @brief Describes how a buffer (or some part of it) will be used during rendering operations.
     */
    struct BufferDescriptor {
        Buffer *        buffer  = nullptr;              //! Buffer where the data is located.
        const char *    attrib  = nullptr;              //! Name of the attribute.
        DataType::Enum  type    = DataType::Unknown;    //! Data type, stored in the buffer.
        std::size_t     count   = 0;                    //! Total count of those elements.
        std::size_t     stride  = 0;                    //! Offset, in bytes, between consecutive data.

        BufferDescriptor() {}

        BufferDescriptor(Buffer* buffer_, const char *attrib_, DataType::Enum type_, std::size_t count_, std::size_t stride_ = 0) 
            : buffer(buffer_), attrib(attrib_), type(type_), count(count_), stride(stride_) {}
    };

    template<std::size_t N>
    using BufferDescriptorArray = std::array<BufferDescriptor, N>;

    /**
     * @brief Associates many buffers together
     */
    class EXENGAPI Subset {
    public:
        static const int BufferCount = 16;
        typedef std::unique_ptr<Subset> Ptr;

    public:
        virtual ~Subset() {}

        virtual BufferArray<BufferCount> getBuffers() = 0;
        virtual const BufferArray<BufferCount> getBuffers() const = 0;
        
        virtual BufferDescriptorArray<BufferCount> getDescriptors() const = 0;
    };
}}

#endif 
