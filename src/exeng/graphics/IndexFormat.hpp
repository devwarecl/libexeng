
#ifndef __EXENG_GRAPHICS_INDEXFORMAT_HPP__
#define __EXENG_GRAPHICS_INDEXFORMAT_HPP__

#include <exeng/Resource.hpp>
#include <exeng/Enum.hpp>

#include <stdexcept>
#include <cstdint>

namespace exeng { namespace graphics {
    struct IndexFormat : public Enum {
        enum Enum {
			Unknown=0,
            Index16=16,
            Index32=32
        };
        
         inline static std::size_t getSize(IndexFormat::Enum format)  {
             return format;
         }
     };
}}

#endif
