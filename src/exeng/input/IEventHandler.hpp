/**
 * @file IEventHandler.hpp
 * @brief Defines the Event Handler interface.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_INPUT_IEVTHANDLER_HPP__
#define __EXENG_INPUT_IEVTHANDLER_HPP__

#include <exeng/Config.hpp>
#include <exeng/TypeInfo.hpp>
#include <exeng/input/EventData.hpp>

namespace exeng {
    namespace input {
        /**
         * @brief Interface to a event handler. The event handler is the 
         * object responsible of do a action in response for a event.
         */        
        class EXENGAPI IEventHandler {
        public:
            virtual ~IEventHandler();
            
            /**
             * @brief Called when a undetermined event is called.
             * @param data
             */
            virtual void handleEvent(const EventData &data) = 0;
        };
    }
}

#endif // __EXENG_INPUT_IEVTHANDLER_HPP__
