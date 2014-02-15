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
 
#include <exeng/io/Stream.hpp>

namespace exeng { namespace io {
    
    Stream::~Stream() {}
        
    bool Stream::isWritable() const {
        return false;
    }
        
    bool Stream::isReadable() const {
        return false;
    }
}}
