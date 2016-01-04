
#pragma once 

#ifndef __xe_input2_ieventhandler_hpp__
#define __xe_input2_ieventhandler_hpp__

namespace xe { namespace input2 {

	template<typename EventData>
	class IEventHandler {
	public:
		virtual bool handleEvent(const EventData &) = 0;
	};
}}

#endif 
