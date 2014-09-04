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
     * @brief Encode a datatype description on a 16-bit value. Used for representation, 
     * and serialization of those data.
     */
    struct DataType {
    public:
        enum Kind {
            Int, Float
        };
        
        enum Enum {
            UInt8 = 0x0004,
            UInt16 = 0x0008,
            UInt32 = 0x000C,
            UInt64 = 0x0010,
            
            Int8 = 0x0005,
            Int16 = 0x0009,
            Int32 = 0x000D,
            Int64 = 0x0011,
            
            Float16 = 0x0049,
            Float32 = 0x004D,
            Float64 = 0x0051
        }; 
        
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
         * @brief Get the current kind of the datatype. 
         *
         * For now, only float and integer kinds are considered.
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
        int geSize() const;
        
        /**
         * @brief Set the size, in bytes, of the current data type.
         * @param size The size in bytes, of the current data type. Only power of two
         * values are accepted.
         */
        void seSize(int size);
        
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
        
        /**
         * @brief Get the raw value of the data type.
         */
        uint16_t getValue() const;
        
        /**
         * @brief Set the raw value of the data type.
         */
        void setValue(uint16_t value);
        
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
    
    
    /**
     * @brief
     */
    template<typename Type> struct DataTypeTraits;
}

#include "DataType.inl"

#endif
