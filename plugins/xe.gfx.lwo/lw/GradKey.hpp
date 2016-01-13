
#pragma once

namespace lw {
	
	class GradKey : public Wrapper<GradKey, ::lwGradKey> {
	public:
		GradKey() {}
		GradKey(::lwGradKey *value) : Wrapper<GradKey, ::lwGradKey>(value) {}

	};

}
