
#ifndef __EXENG_GRAPHICS_INDEXFORMAT_HPP__
#define __EXENG_GRAPHICS_INDEXFORMAT_HPP__

#include <xe/Resource.hpp>
#include <xe/Enum.hpp>

#include <stdexcept>
#include <cstdint>

namespace xe { namespace gfx {
	struct IndexFormat : public Enum {
		enum Enum {
			Unknown=0,
			Index16=2,
			Index32=4
		};
        
		inline static std::size_t getSize(IndexFormat::Enum format)  {
			return format;
		}
	};
}}

#endif
