
#pragma once 

#ifndef __xe_input2_ievent_hpp__
#define __xe_input2_ievent_hpp__

#include <xe/input/IEventHandler.hpp>

namespace xe { namespace input2 {
	template<typename EventData>
	class IEvent {
	public:
		virtual ~IEvent() {}

		virtual int getHandlerCount() const = 0;
		virtual IEventHandler<EventData>* getHandler(const int index) = 0;

		virtual void addHandler(IEventHandler<EventData>*) = 0;
		virtual void removeHandler(IEventHandler<EventData>*) = 0;

		virtual void raise(const EventData &) = 0;
	};
}}

#endif
