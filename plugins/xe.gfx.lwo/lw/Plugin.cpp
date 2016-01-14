
#include "Plugin.hpp"

namespace lw {
	Plugin::Plugin() {}
	Plugin::Plugin(::lwPlugin *value) : Collection<Plugin, ::lwPlugin>(value) {}

	void* Plugin::data() const {
		return this->value->data;
	}

	int Plugin::flags() const {
		return this->value->flags;
	}

	std::string Plugin::name() const {
		return this->value->name;
	}

	std::string Plugin::ord() const {
		return this->value->ord;
	}
}
