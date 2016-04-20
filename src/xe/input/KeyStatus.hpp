
#pragma once 

#ifndef __xe_input_keystatus__
#define __xe_input_keystatus__

namespace xe { namespace input {
	struct KeyStatus {
		enum Enum {
			Release,
			Press,
			Unknown
		};
	};
}}

#endif
