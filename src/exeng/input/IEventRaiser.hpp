/**
 * @file IEventRaiser.hpp
 * @brief Defines the IEvtRaiser interface.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_INPUT_IEVENTRAISER_HPP__
#define __EXENG_INPUT_IEVENTRAISER_HPP__

#include <exeng/Config.hpp>

namespace exeng {
    namespace input {
        class EXENGAPI IEventHandler;
        
        /**
         * @brief Event raiser interface. Collects and raises all pending events, 
         * notifying all the connected event handlers.
         * @todo Must better design this module in the future.
         */
        class IEventRaiser {
        public:
            virtual ~IEventRaiser();
            
            /**
             * @brief Raise all pending events. The events to be raised are 
             * determined by the implementor.
             */
            virtual void pollEvents() = 0;
            
            /**
             * @brief Add a new event handler.
             * @param handler The handler to be added. If is a null pointer,
             * then a std::invalid_argument exception is throw. If 
             */
            virtual void addEventHandler(IEventHandler *handler) = 0;
            
            /**
             * @brief Remove the specified event handler from the raiser. 
             * @param handler The handler to be removed. If is nullptr, then
             * a std::invalid_argument exception is throw. 
             */
            virtual void removeEventHandler(IEventHandler *handler) = 0;
        };
    }
}

#endif  //__EXENG_INPUT_IEVENTRAISER_HPP__
