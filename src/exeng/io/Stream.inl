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
 

namespace exeng { namespace io {
    template<typename Type> 
    void write(Stream *stream, const Type &value) {
        stream->write(&value, 1);
    }
    
    
    template<typename Type> 
    void write(Stream *stream, const Type *values, int count) {
        const int total = sizeof(Type) * count;
        int current = 0;

        while (current < total) {
            total -= stream->write(values, total - current, current);
        }
    }
    
    
    template<typename Type> 
    void read(const Stream *stream, Type &value) {
        stream->read(&value, 1);
    }
    
    
    template<typename Type> 
    void read(const Stream *stream, Type *values, int count) {
        const int total = sizeof(Type) * count;
        int current = 0;

        while (current < total) {
            total -= stream->read(values, total - current, current);
        }
    }
}}
