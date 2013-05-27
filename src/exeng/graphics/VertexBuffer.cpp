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

#include <cstdlib>
#include <stdexcept>
#include <cassert>
#include <boost/checked_delete.hpp>

#include <exeng/HeapBuffer.hpp>
#include <exeng/graphics/VertexBuffer.hpp>

namespace exeng {
    namespace graphics {
        VertexBuffer::~VertexBuffer() {
        }
    }
}
