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
    
    template<typename Type> void Stream::write(const Type &value) {
        this->write(&value, 1);
    }
    
    
    template<typename Type> void Stream::write(const Type *values, int count) {
        const int total = sizeof(Type) * count;
        int current = 0;

        while (current < total) {
            total -= this->write(values, total - current, current);
        }
    }
    
    
    template<typename Type> void Stream::read(Type &value) const {
        this->read(&value, 1);
    }
    
    
    template<typename Type> void Stream::read(Type *values, int count) const {
        const int total = sizeof(Type) * count;
        int current = 0;

        while (current < total) {
            total -= this->read(values, total - current, current);
        }
    }
}}
