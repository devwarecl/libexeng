#pragma once

#ifndef __xe_traits__
#define __xe_traits__

#include <xe/DataType.hpp>
#include <xe/Vector.hpp>


#define EXENG_DATA_TYPE_TRAITS(BasicType, DataTypeEnum)     \
    template<> struct DataTypeTraits<BasicType> {           \
        typedef BasicType Type;                             \
        static const DataType::Enum Enum = DataTypeEnum;	\
		static const int count = 0;							\
    }

namespace xe {

    template<typename Type> struct DataTypeTraits;
    EXENG_DATA_TYPE_TRAITS(std::uint8_t , DataType::UInt8);
    EXENG_DATA_TYPE_TRAITS(std::uint16_t, DataType::UInt16);
    EXENG_DATA_TYPE_TRAITS(std::uint32_t, DataType::UInt32);
    EXENG_DATA_TYPE_TRAITS(std::int8_t  , DataType::Int8);
    EXENG_DATA_TYPE_TRAITS(std::int16_t , DataType::Int16);
    EXENG_DATA_TYPE_TRAITS(std::int32_t , DataType::Int32);
    EXENG_DATA_TYPE_TRAITS(float        , DataType::Float32);


}

#endif
