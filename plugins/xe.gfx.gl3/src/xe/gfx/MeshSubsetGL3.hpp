
#ifndef __EXENG_GRAPHICS_GL3_GL3MESHSUBSET_HPP__
#define __EXENG_GRAPHICS_GL3_GL3MESHSUBSET_HPP__

#include <xe/gfx/MeshSubsetBase.hpp>

#include "GL3.hpp"
#include "BufferGL3.hpp"

namespace xe { namespace gfx { namespace gl3 {
    class MeshSubsetGL3 : public MeshSubsetBase<BufferGL3> {
    public:
        MeshSubsetGL3(std::vector<BufferPtr> vertexBuffers, const VertexFormat &format);

		MeshSubsetGL3(std::vector<BufferPtr> vertexBuffers, const VertexFormat &format, BufferPtr indexBuffer, IndexFormat::Enum indexFormat);

        virtual ~MeshSubsetGL3();

        inline GLuint getVertexArrayId() const {
            return this->vertexArrayId;
        }

        virtual TypeInfo getTypeInfo() const override;

	private:
		void construct();

		void initializeVertexArray(std::vector<BufferPtr> vertexBuffers, const VertexFormat &format);
		void initializeIndexArray(BufferPtr vertexBuffers, IndexFormat::Enum indexFormat);

    protected:
        GLuint vertexArrayId = 0;
    };
}}}

#endif  // __EXENG_GRAPHICS_GL3_GL3MESHSUBSET_HPP__
