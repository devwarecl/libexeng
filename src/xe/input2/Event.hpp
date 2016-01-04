#pragma once

#include <xe/input2/IEvent.hpp>

#ifndef __xe_input2_event_hpp__
#define __xe_input2_event_hpp__

#include <vector>
#include <xe/input2/IEvent.hpp>

namespace xe { namespace input2 {
	template<typename EventData>
	class Event : public IEvent<EventData> {
	public:
		Event() {}
		virtual ~Event() {}

		virtual int getHandlerCount() const override {
			return handlers.size();
		}

		virtual IEventHandler<EventData>* getHandler(const int index) override {
			assert(index >= 0);
			assert(index < this->getHandlerCount());

			return handlers[index];
		}

		virtual void addHandler(IEventHandler<EventData>* handler) override {
			handlers.push_back(handler);
		}

		virtual void removeHandler(IEventHandler<EventData>* handler) override {
			std::remove(handlers.begin(), handlers.end(), handler);
		}

		virtual void raise(const EventData &eventData) override {
			for (IEventHandler<EventData> *handler : this->handlers) {
				if (!handler->handleEvent(eventData)) {
					break;
				}
			}
		}

	private:
		std::vector<IEventHandler<EventData>*> handlers;
	};
}}

#endif 
