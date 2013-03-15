#ifndef __EXENG_NUMERICTRAITS_HPP__
#define __EXENG_NUMERICTRAITS_HPP__

#include <cstdint>
#include <climits>

namespace exeng {
	template<typename _type> struct TypeTraits;

	template<> struct TypeTraits<std::uint8_t> {
		enum {
			min = 0x00,
			max = UCHAR_MAX
		};
	};


	template<> struct TypeTraits<std::uint16_t> {
		enum {
			min = 0x00,
			max = USHRT_MAX
		};
	};


	template<> struct TypeTraits<std::uint32_t> {
		enum {
			min = 0x00,
			max = UINT_MAX
		};
	};


	template<> struct TypeTraits<std::uint64_t> {
		enum : std::uint64_t {
			min = 0x00,
			max = ULLONG_MAX
		};
	};
}

#endif	// __EXENG_NUMERICTRAITS_HPP__
