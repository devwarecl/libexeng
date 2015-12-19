
#include "MeshSubsetTransformer.hpp"

#include <exeng/HeapBuffer.hpp>
#include <exeng/Vector.hpp>
#include <exeng/graphics/MeshSubset.hpp>
#include <exeng/graphics/VertexArray.hpp>

namespace xe { namespace gfx {

	void MeshSubsetTransformer::transform(MeshSubset *subset, const Matrix4f &transformation) {
		const VertexFormat format = subset->getVertexFormat();

		Buffer *buffer = subset->getBuffer(0);

		HeapBuffer tempBuffer(buffer->getSize());

		tempBuffer.setData(buffer->getPointer());

		VertexArray array(tempBuffer.getPointer(), &format);

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
		
		buffer->setData(tempBuffer.getPointer());
	}
}}
