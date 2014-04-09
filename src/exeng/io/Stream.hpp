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

#ifndef __EXENG_STREAM_HPP__
#define __EXENG_STREAM_HPP__

#include <exeng/Object.hpp>
 
namespace exeng { namespace io {
    class EXENGAPI Stream : public Object {
    public:
        virtual ~Stream() = 0;
        
        virtual bool isWritable() const;
        virtual int write(const void* data, int size, int offset) = 0;
         
        virtual bool isReadable() const;
        virtual int read(void* data, int size, int offset) const = 0;
    };
    
    template<typename Type> void write(Stream *stream, const Type &value);
    template<typename Type> void write(Stream *stream, const Type *values, int count);

    template<typename Type> void read(const Stream *stream, Type &value);
    template<typename Type> void read(const Stream *stream, Type *values, int count);
}}

#include <exeng/io/Stream.inl>

#endif //__EXENG_STREAM_HPP__
