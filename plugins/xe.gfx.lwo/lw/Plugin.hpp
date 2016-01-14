
#pragma once

#ifndef __lw_plugin_hpp__
#define __lw_plugin_hpp__

#include <string>
#include "Collection.hpp"
#include "lwo/lwo2.h"

namespace lw {
	class Plugin : public Collection<Plugin, ::lwPlugin> {
	public:
		Plugin();
		Plugin(::lwPlugin *value);

		void* data() const;

		int flags() const;

		std::string name() const;

		std::string ord() const;
	};
}

#endif
