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

#include "VertexFormat.hpp"

#include <cstring>
#include <cassert>
#include <stdexcept>

#include <boost/range/numeric.hpp>

namespace exeng  {
    namespace graphics {   
        inline int VertexFormat::getSize() const {
            return boost::accumulate(fields, 0, [](int prev, const VertexField &field) {
                return prev + field.dataType.getSize();
            });
        }
    }
}
