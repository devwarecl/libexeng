/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#pragma once

#ifndef __xe_applicationrt_hpp__
#define __xe_applicationrt_hpp__


#include <xe/Application.hpp>

namespace xe {
    /**
     * @brief Basic application skeleton for realtime, graphic applications.
     */
    class EXENGAPI ApplicationRT : public Application {
    public:
		virtual ~ApplicationRT() {};
        
        virtual int run(int argc, char **argv) override;

	protected:
		virtual void initialize() = 0;
		virtual void terminate() = 0;

		virtual void doEvents() = 0;
		virtual void update(const float seconds) = 0;
		virtual void render() = 0;

		virtual bool isRunning() const = 0;
    };
}

#endif // __xe_applicationrt_hpp__
