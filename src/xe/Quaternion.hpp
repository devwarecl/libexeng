
#pragma once

#ifndef __xe_quaternion_hpp__
#define __xe_quaternion_hpp__

#include <xe/Vector.hpp>

namespace xe {
    template<typename Type>
    struct Quaternion {
        xe::Vector<Type, 4> q;

    };
}

#endif 
