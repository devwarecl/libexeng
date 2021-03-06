
#ifndef __EXENG_GRAPHICS_LEGACYMODULE_HPP__
#define __EXENG_GRAPHICS_LEGACYMODULE_HPP__

#include <xe/Config.hpp>
#include <xe/Enum.hpp>
#include <xe/Matrix.hpp>

namespace xe { namespace gfx {
	struct Transform : public Enum {
        enum Enum {View, World, Projection};
    };
	
	class EXENGAPI LegacyModule {
	protected:
		virtual ~LegacyModule();

	public:
		virtual void setTransform(Transform::Enum transform, const Matrix4f &matrix) = 0;
		virtual Matrix4f getTransform(Transform::Enum transform) const = 0;
	};
}}

#endif	// __EXENG_GRAPHICS_LEGACYMODULE_HPP__
