
#include "MeshSubsetTransformer.hpp"

#include <xe/HeapBuffer.hpp>
#include <xe/Vector.hpp>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/VertexArray.hpp>

namespace xe { namespace gfx {

	void MeshSubsetTransformer::transform(MeshSubset *subset, const Matrix4f &transformation) {
		const VertexFormat format = subset->getFormat();

		Buffer *buffer = subset->getBuffer(0);

		auto locker = buffer->getLocker<void>();

		VertexArray array(locker.getPointer(), &format);

		for (int i=0; i<subset->getVertexCount(); i++) {
			Vector4f position = {0.0f, 0.0f, 0.0f, 1.0f};
			Vector4f normal = {0.0f, 0.0f, 0.0f, 0.0f};

			array.getAttribValue(i, VertexAttrib::Position, &position);
			array.getAttribValue(i, VertexAttrib::Normal, &normal);

			position	= xe::transform(transformation, position);
			normal		= xe::transform(transformation, normal);

			array.setAttribValue(i, VertexAttrib::Position, &position);
			array.setAttribValue(i, VertexAttrib::Normal, &normal);
		}
	}
}}
