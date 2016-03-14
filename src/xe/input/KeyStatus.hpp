
#pragma once 

#ifndef __xe_input2_keystatus_hpp__
#define __xe_input2_keystatus_hpp__

namespace xe { namespace input2 {
	struct KeyStatus {
		enum Enum {
			Release,
			Press,
			Unknown
		};
	};
}}

#endif
