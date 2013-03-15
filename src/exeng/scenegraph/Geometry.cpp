/**
 * @brief Implemente la clase abstracta Geometry.
 */

#include "Geometry.hpp"

namespace exeng {
    namespace scenegraph {
        Geometry::~Geometry() { }

		TypeInfo Geometry::getTypeInfo() const {
			return TypeInfo::get<Geometry>();
		}
    }
}
