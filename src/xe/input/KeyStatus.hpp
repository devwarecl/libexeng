
#pragma once 

#ifndef __xe_input2_keystatus_hpp__
#define __xe_input2_keystatus_hpp__

#include <xe/Enum.hpp>
#include <ostream>

namespace xe { namespace input2 {
	struct KeyStatus : public Enum {
		enum Enum {
            Unknown,
			Release,
			Press
		};
		
		friend std::ostream& operator<< (std::ostream& os, Enum keyStatus) {
            switch (keyStatus) {
                case Unknown:   os << "Unknown"; break;
                case Release:   os << "Release"; break;
                case Press:     os << "Press"; break;
            }
            
            return os;
        }
	};	
}}

#endif
