
#include "GradKey.hpp"

namespace lw {
	GradKey::GradKey() {}
	GradKey::GradKey(::lwGradKey *value) : Wrapper<GradKey, ::lwGradKey>(value) {}
}
