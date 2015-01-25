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


#ifndef __EXENG_DATATYPE_HPP__
#define __EXENG_DATATYPE_HPP__

#include <exeng/Config.hpp>
#include <exeng/Enum.hpp>
#include <iostream>
#include <cstdint>

#define EXENG_DATA_TYPE_TRAITS(KeyEnum, BasicType)  \
    template<> struct DataTypeTraits<BasicType> {   \
        typedef BasicType Type;                     \
        static const int Enum=static_cast<int>(KeyEnum);	\
    }

namespace exeng {
    
    /**
     * @brief Basic data type enumeration.
     */
    struct DataType : public Enum 
	{
        enum Kind {
            Int, Float
        };
        
        enum Enum {
            Unknown,
            UInt8, UInt16, UInt32,
            Int8, Int16, Int32,
            Float16, Float32 
        }; 
        
		static bool isSigned(DataType::Enum dt);

		static DataType::Kind getKind(DataType::Enum dataType);

		static int getSize(DataType::Enum dataType);
    };
    
	// template<typename Type> struct DataTypeTraits;

	/* Implementation */

	inline bool DataType::isSigned(DataType::Enum dt) 
	{
		switch (dt) {
			case DataType::UInt8:
			case DataType::UInt16:
			case DataType::UInt32:
				return false;

			default:
				return true;
		}
	}

	inline DataType::Kind DataType::getKind(DataType::Enum dataType) 
	{
		switch (dataType) {
			case DataType::Float16: 
			case DataType::Float32: 
				return DataType::Float;

			default:
				return DataType::Int;
		}
	}

	inline int DataType::getSize(DataType::Enum dataType)
	{
		switch (dataType) {
			case DataType::UInt8:
			case DataType::Int8:
				return 1;

			case DataType::UInt16:
			case DataType::Int16:
			case DataType::Float16:
				return 2;

			case DataType::UInt32:
			case DataType::Int32:
			case DataType::Float32:
				return 4;

			default:
				return -1;
		}
	}

	/*
    EXENG_DATA_TYPE_TRAITS(DataType::UInt8,  std::uint8_t);
    EXENG_DATA_TYPE_TRAITS(DataType::UInt16, std::uint16_t);
    EXENG_DATA_TYPE_TRAITS(DataType::UInt32, std::uint32_t);
    EXENG_DATA_TYPE_TRAITS(DataType::Int8,  std::int8_t);
    EXENG_DATA_TYPE_TRAITS(DataType::Int16, std::int16_t);
    EXENG_DATA_TYPE_TRAITS(DataType::Int32, std::int32_t);
    EXENG_DATA_TYPE_TRAITS(DataType::Float32, float);
	*/
}

#endif
