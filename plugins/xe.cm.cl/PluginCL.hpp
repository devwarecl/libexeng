
#pragma once 

#ifndef __xe_cm_plugincl_hpp__
#define __xe_cm_plugincl_hpp__

#include <xe/sys/Plugin.hpp>

namespace xe { namespace cm {
    class PluginCL : public xe::sys::Plugin {
	public:
		virtual std::string getName() const override;

        virtual std::string getDescription() const override;

        virtual Version getVersion() const override;

        virtual void initialize(Core *core) override;

        virtual void terminate() override;
	};
}}

#endif 
