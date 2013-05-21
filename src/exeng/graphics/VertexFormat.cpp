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

#include <cstring>
#include <cassert>
#include <stdexcept>
#include <boost/range/numeric.hpp>

#include <exeng/graphics/VertexFormat.hpp>

namespace exeng  {
    namespace graphics {   
        inline int VertexFormat::getSize() const {
            return boost::accumulate(fields, 0, [](int prev, const VertexField &field) {
                return prev + field.dataType.getSize();
            });
        }
    }
}
