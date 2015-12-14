/**
 * @file InputData.hpp
 * @brief Defines the InputData structure.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_INPUT_INPUTDATA_HPP__
#define __EXENG_INPUT_INPUTDATA_HPP__

#include <exeng/Config.hpp>

namespace exeng {
    namespace input {
        
        /**
         * @brief The InputData struct
         */
        struct EXENGAPI InputData {
            int code;
            bool status;
            int dimensions;
            float force[3];
        };
    }
}

#endif // __EXENG_INPUT_INPUTDATA_HPP__
