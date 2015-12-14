/**
 * @file EventData.hpp
 * @brief EventData class definition
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_INPUT_EVENTDATA_HPP__
#define __EXENG_INPUT_EVENTDATA_HPP__

#include <exeng/TypeInfo.hpp>

namespace exeng { namespace input {

	/**
	 * @brief Holds specific data of a determined event type.
	 */
	struct EventData {
		/**
		 * @brief Specific event type info. Used for validations.
		 */
		TypeInfo eventType;
    
		/**
		 * @brief If after a event is raised this attribute is true, then
		 * the event raiser stop notifying to other 
		 */
		mutable bool handled;   
    
		inline EventData() : handled(false) {
		}
    
		explicit inline EventData(TypeInfo e) : 
			eventType(e), handled(false) {
		}

		template<typename DerivedEventType>
		const DerivedEventType& cast() const {
#if defined(EXENG_DEBUG)
			if (this->eventType != TypeId<DerivedEventType>()) {
				throw std::bad_cast();
			}
#endif
			return static_cast<const DerivedEventType&>(*this);
		}

		template<typename DerivedEventType>
		DerivedEventType& cast() {
#if defined(EXENG_DEBUG)
			if (this->eventType != TypeId<DerivedEventType>()) {
				throw std::bad_cast();
			}
#endif
			return static_cast<DerivedEventType&>(*this);
		}
	};


	template<typename DerivedEventDataType>
	struct EventDataImpl : public EventData {
		EventDataImpl() : EventData( TypeId<DerivedEventDataType>() ) {
		}
	};
}}

#endif // __EXENG_INPUT_EVENTDATA_HPP__
