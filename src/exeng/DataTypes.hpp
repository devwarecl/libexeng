
//!\file DataTypes.hpp
/*!Define the engine's basic data types. Also, define fixed-size, elemental platform-independent
 * data types, denoted as [U]type[8|16|32|64|...]
 */

#ifndef __EXENG_DATATYPES_HPP__
#define __EXENG_DATATYPES_HPP__

#include "DetectEnv.hpp"

namespace exeng {
#if defined(EXENG_MSVC) || defined(EXENG_BCC) || defined(EXENG_ICC)
    typedef unsigned __int8     UInt8;
    typedef unsigned __int16    UInt16;
    typedef unsigned __int32    UInt32;
    typedef unsigned __int64    UInt64;

    typedef signed __int8       Int8;
    typedef signed __int16      Int16;
    typedef signed __int32      Int32;
    typedef signed __int64      Int64;
#else
    typedef unsigned char		UInt8;
	typedef unsigned short int	UInt16;
	typedef unsigned int		UInt32;
	typedef unsigned long long  UInt64;

	typedef signed char			Int8;
	typedef signed short int	Int16;
	typedef signed int			Int32;
	typedef signed long long    Int64;
#endif

    typedef float               Float32;
    typedef double              Float64;


	//! Data type enumeration
	namespace DataType {
		enum Type {
			Unknown,
			UInt8, UInt16, UInt32, UInt64,
			Int8, Int16, Int32, Int64, 
			Float8, Float16, Float32, Float64
		};
	}


	template<typename _Type> struct DataTypeTraitsBase {
		static const int Size = sizeof(_Type);
		static const DataType::Type TypeEnum = DataType::Unknown;
		typedef _Type Type;
	};


	template<typename _Type> struct DataTypeTraits : public DataTypeTraitsBase<_Type> {};


	template<>
	struct DataTypeTraits<UInt8> : public DataTypeTraitsBase<UInt8> {
		static const DataType::Type TypeEnum = DataType::UInt8;
	};


	template<>
	struct DataTypeTraits<UInt16> : public DataTypeTraitsBase<UInt16> {
		static const DataType::Type TypeEnum = DataType::UInt16;
	};


	template<>
	struct DataTypeTraits<UInt32> : public DataTypeTraitsBase<UInt32> {
		static const DataType::Type TypeEnum = DataType::UInt32;
	};


	template<>
	struct DataTypeTraits<UInt64> : public DataTypeTraitsBase<UInt64> {
		static const DataType::Type TypeEnum = DataType::UInt64;
	};


	template<>
	struct DataTypeTraits<Int8> : public DataTypeTraitsBase<Int8> {
		static const DataType::Type TypeEnum = DataType::Int8;
	};


	template<>
	struct DataTypeTraits<Int16> : public DataTypeTraitsBase<Int16> {
		static const DataType::Type TypeEnum = DataType::Int16;
	};


	template<>
	struct DataTypeTraits<Int32> : public DataTypeTraitsBase<Int32> {
		static const DataType::Type TypeEnum = DataType::Int32;
	};


	template<>
	struct DataTypeTraits<Int64> : public DataTypeTraitsBase<Int64> {
		static const DataType::Type TypeEnum = DataType::Int64;
	};


	template<>
	struct DataTypeTraits<Float32> : public DataTypeTraitsBase<Float32> {
		static const DataType::Type TypeEnum = DataType::Float32;
	};


	template<>
	struct DataTypeTraits<Float64> : public DataTypeTraitsBase<Float64> {
		static const DataType::Type TypeEnum = DataType::Float64;
	};
}

#endif
