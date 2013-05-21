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
#include <iostream>
#include <cstdint>

namespace exeng {

    /**
     * @brief
     */
    enum class DataTypeEnum {
        UInt8,  UInt16,     UInt32,     UInt64,
        Int8,   Int16,      Int32,      Int64,
                Float16,    Float32,    Float64
    };

    /**
     * @brief
     */
    template<typename Type> struct DataTypeTraits;
    
    template<> struct DataTypeTraits<uint8_t> {
        typedef uint8_t Type;
        enum { Enum= static_cast<int>(DataTypeEnum::UInt8) };
    };
    
    template<> struct DataTypeTraits<uint16_t> {
        typedef uint16_t Type;
        enum { Enum=static_cast<int>(DataTypeEnum::UInt16) };
    };

    template<> struct DataTypeTraits<uint32_t> {
        typedef uint32_t Type;
        enum { Enum=static_cast<int>(DataTypeEnum::UInt32) };
    };
    
    template<> struct DataTypeTraits<uint64_t> {
        typedef uint64_t Type;
        enum { Enum=static_cast<int>(DataTypeEnum::UInt64) };
    };
    
    template<> struct DataTypeTraits<int8_t> {
        typedef int8_t Type;
        enum { Enum=static_cast<int>(DataTypeEnum::Int8) };
    };
    
    template<> struct DataTypeTraits<int16_t> {
        typedef int16_t Type;
        enum { Enum=static_cast<int>(DataTypeEnum::Int16) };
    };

    template<> struct DataTypeTraits<int32_t> {
        typedef int32_t Type;
        enum { Enum=static_cast<int>(DataTypeEnum::Int32) };
    };
    
    template<> struct DataTypeTraits<int64_t> {
        typedef int64_t Type;
        enum { Enum=static_cast<int>(DataTypeEnum::Int64) };
    };
    
    template<> struct DataTypeTraits<float> {
        typedef float Type;
        enum { Enum=static_cast<int>(DataTypeEnum::Float32) };
    };
    
    template<> struct DataTypeTraits<double> {
        typedef double Type;
        enum { Enum=static_cast<int>(DataTypeEnum::Float64) };
    };
    
    /**
     * @brief Encode a datatype description on a 16-bit value. Used for generic representation
     * of data, and serialization of those data.
     */
    struct DataType {
    public:
        enum Kind {
            Int, Float
        };
        
    public:
        static DataType UInt8()  { return DataType::makeDataType<false, DataType::Int, 1>(); }
        static DataType UInt16() { return DataType::makeDataType<false, DataType::Int, 2>(); }
        static DataType UInt32() { return DataType::makeDataType<false, DataType::Int, 4>(); }
        static DataType UInt64() { return DataType::makeDataType<false, DataType::Int, 8>(); }
        
        static DataType Int8()  { return DataType::makeDataType<true, DataType::Int, 1>(); }
        static DataType Int16() { return DataType::makeDataType<true, DataType::Int, 2>(); }
        static DataType Int32() { return DataType::makeDataType<true, DataType::Int, 4>(); }
        static DataType Int64() { return DataType::makeDataType<true, DataType::Int, 8>(); }
        
        static DataType Float16() { return DataType::makeDataType<true, DataType::Float, 2>(); }
        static DataType Float32() { return DataType::makeDataType<true, DataType::Float, 4>(); }
        static DataType Float64() { return DataType::makeDataType<true, DataType::Float, 8>(); }
        
    public:
        /**
         * @brief Default constructor.
         *
         * Initialize the data type to a invalid state. 
         */
        DataType();
        
        /**
         * @brief Construct a DataType directly from a 16 bit raw value.
         */
        DataType(uint16_t value);
        
        
        /**
         * @brief Construct a DataType from the specified attributes.
         */
        DataType(bool sign, DataType::Kind kind, int size);
        
        
        /**
         * @brief Templated default constructor.
         *
         * Used for enabling the use on template metaprogramming.
         */
        
        template<bool typeSign, DataType::Kind typeKind, int typeSize>
        static DataType makeDataType() {
            return DataType(typeSign, typeKind, typeSize);
        }
        
        /**
         * @brief Implicit conversion to a 16-bit value.
         */
        operator uint16_t () const;
        
        /**
         * @brief Get the current kind of the datatype. 
         *
         * For now, only float and integer kinds are considered.
         * @return 
         */
        DataType::Kind getKind() const;
        
        /**
         * @brief Set the current kind of the datatype.
         */
        void setKind(DataType::Kind kind);
        
        /**
         * @brief Get the sign datatype flag.
         */
        bool getSign() const;
        
        /**
         * @brief Set the sign datatype flag.
         */
        void setSign(bool value);
        
        /**
         * @brief Get the size, in bytes, of the data type
         */
        int getSize() const;
        
        /**
         * @brief Set the size, in bytes, of the current data type.
         * @param size The size in bytes, of the current data type. Only power of two
         * values are accepted.
         */
        void setSize(int size);
        
        /**
         * @brief Check if the current state of the data type is valid.
         */
        bool isValid() const;
        
        bool operator== (const DataType &other) const;
        
        bool operator!= (const DataType &other) const;
        
        bool operator> (const DataType &other) const;
        
        bool operator< (const DataType &other) const;
        
        bool operator>= (const DataType &other) const;
        
        bool operator<= (const DataType &other) const;
        
    private:
        union {
            struct {
                uint16_t sign:1;        //! Sign bit
                uint16_t __unused0:1;   //! Reserved for future use.
                uint16_t size:4;        //! Size, in bytes
                uint16_t kind:4;        //! Elemental type (floating and integer for now).
                uint16_t __unused1:6;   //! Reserved for future use.
            };
            
            uint16_t value;             //! The above attributes, encoded in a 16-bit value.
        };
    };
    
    
    inline DataType::DataType() {
        this->value = 0;
    }
    
    
    inline DataType::DataType(uint16_t value) {
        this->value = value;
    }
    
    
    inline DataType::DataType(bool sign, DataType::Kind kind, int size) {
        this->value = 0;
        this->setSize(size);
        this->setSign(sign);
        this->setKind(kind);
        
        /*
        std::cout << "before: " << this->value << std::endl;
        std::cout << sign << ", " << kind << ", " << size << std::endl;
        std::cout << "after: " << this->value << std::endl;
        std::cout << std::endl;
        */
    }
    
    
    inline DataType::operator uint16_t () const {
        return this->value;
    }
    
    
    inline DataType::Kind DataType::getKind() const {
        return static_cast<DataType::Kind>(this->kind);
    }
    
    
    inline void DataType::setKind(DataType::Kind kind) {
        this->kind = static_cast<int>(kind);
    }

    
    inline bool DataType::getSign() const {
        return this->value == 1;
    }
    
    
    inline void DataType::setSign(bool value) {
        if (value == true) {
            this->sign = 1;
        } else {
            this->sign = 0;
        }
    }
    
    
    inline int DataType::getSize() const {
        //! FIXME: Reimplement this based on bit operations instead.
        int size = 0;
        
        switch(this->size) {
            case 1: size = 1; break;
            case 2: size = 2; break;
            case 3: size = 4; break;
            case 4: size = 8; break;
            default: size = 0; break;
        }
        
        return size;
    }
    
    
    inline void DataType::setSize(int size) {
        //! FIXME: Reimplement this based on bit operations instead.
        int binSize = 0;
        
        switch(size) {
            case 1: binSize = 1; break;
            case 2: binSize = 2; break;
            case 4: binSize = 3; break;
            case 8: binSize = 4; break;
            default: binSize = 0; break;
        }
        
        this->size = binSize;
    }
    
    
    inline bool DataType::isValid() const {
        bool validReserved = this->__unused0 == 0 && this->__unused1 == 0;
        bool validSize = this->size != 0;
        bool validFloat = (this->sign == true && this->getKind() == DataType::Float);
        bool validInt = (this->getKind() == DataType::Int);
        
        return validReserved && validSize && (validFloat || validInt);
    }
    
    
    inline bool DataType::operator== (const DataType &other) const {
        return this->value == other.value;
    }
    
    
    inline bool DataType::operator!= (const DataType &other) const {
        return this->value != other.value;
    }
    
    
    inline bool DataType::operator> (const DataType &other) const {
        return this->size > other.size;
    }
    
    
    inline bool DataType::operator< (const DataType &other) const {
        return this->size < other.size;
    }
    
    
    inline bool DataType::operator>= (const DataType &other) const {
        return (*this == other) || (*this > other);
    }
    
    
    inline bool DataType::operator<= (const DataType &other) const {
        return (*this == other) || (*this < other);
    }
}
#endif
