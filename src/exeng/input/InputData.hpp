#ifndef __EXENG_INPUT_INPUTDATA_HPP__
#define __EXENG_INPUT_INPUTDATA_HPP__

namespace exeng {
    namespace input {
        
        struct InputData {
            int code;
            int dimensions;
            float force[3];
        };
        
        struct InputStatus {
            
        };
    }
}

#endif // __EXENG_INPUT_INPUTDATA_HPP__
