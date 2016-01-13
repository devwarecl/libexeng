
#pragma once

namespace lw {
	class Plugin : public Collection<Plugin, ::lwPlugin> {
	public:
		Plugin() {}
		Plugin(::lwPlugin *value) : Collection<Plugin, ::lwPlugin>(value) {}

		void* data() const {
			return this->value->data;
		}

		int flags() const {
			return this->value->flags;
		}

		std::string name() const {
			return this->value->name;
		}

		std::string ord() const {
			return this->value->ord;
		}
	};
}
