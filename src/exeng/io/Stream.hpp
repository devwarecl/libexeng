/**
 * @file
 * @desc
 */
 
/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */
 
#include <exeng/Object.hpp>
 
namespace exeng { namespace io {
    class EXENGAPI Stream : public Object {
    public:
        virtual ~Stream() = 0;
        
        virtual bool isWritable() const;
        virtual int write(const void* data, int size, int offset) = 0;
        template<typename Type> void write(const Type &value);
        template<typename Type> void write(const Type *values, int count);
         
        virtual bool isReadable() const;
        virtual int read(void* data, int size, int offset) const = 0;
        template<typename Type> void read(Type &value) const;
        template<typename Type> void read(Type *values, int count) const;
    };
}}

#include <exeng/io/Stream.inl>
