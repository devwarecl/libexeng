#pragma once

#ifndef __xe_input2_event_hpp__
#define __xe_input2_event_hpp__

#include <cassert>
#include <vector>
#include <algorithm>
#include <xe/input/Event.hpp>

namespace xe { namespace input2 {
	template<typename EventData>
	class Event : public Event<EventData> {
	public:
		Event() {}
		virtual ~Event() {}

		virtual int getHandlerCount() const override {
			return handlers.size();
		}

		virtual EventHandler<EventData>* getHandler(const int index) override {
			assert(index >= 0);
			assert(index < this->getHandlerCount());

			return handlers[index];
		}

		virtual void addHandler(EventHandler<EventData>* handler) override {
			handlers.push_back(handler);
		}

		virtual void removeHandler(EventHandler<EventData>* handler) override {
            std::remove(handlers.begin(), handlers.end(), handler);
		}

		virtual void raise(const EventData &eventData) override {
			for (EventHandler<EventData> *handler : this->handlers) {
				if (!handler->handleEvent(eventData)) {
					break;
				}
			}
		}

	private:
		std::vector<EventHandler<EventData>*> handlers;
	};
}}

#endif 
