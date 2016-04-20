
#pragma once 

#ifndef __xe_input_event__
#define __xe_input_event__

#include <xe/input/EventHandler.hpp>

namespace xe { namespace input {
	template<typename EventData>
	class Event {
	public:
		virtual ~Event() {}

		virtual int getHandlerCount() const = 0;
		virtual EventHandler<EventData>* getHandler(const int index) = 0;

		virtual void addHandler(EventHandler<EventData>*) = 0;
		virtual void removeHandler(EventHandler<EventData>*) = 0;

		virtual void raise(const EventData &) = 0;
	};
}}

#endif
