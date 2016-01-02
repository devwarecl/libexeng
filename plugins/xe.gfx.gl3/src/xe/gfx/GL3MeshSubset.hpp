
#ifndef __EXENG_GRAPHICS_GL3_GL3MESHSUBSET_HPP__
#define __EXENG_GRAPHICS_GL3_GL3MESHSUBSET_HPP__

#include <xe/gfx/MeshSubsetBase.hpp>

#include "GL3.hpp"
#include "GL3Buffer.hpp"

namespace xe { namespace gfx { namespace gl3 {
    class GL3MeshSubset : public MeshSubsetBase<GL3Buffer> {
    public:
        GL3MeshSubset(std::vector<BufferPtr> vertexBuffers, const VertexFormat &format);

		GL3MeshSubset(std::vector<BufferPtr> vertexBuffers, const VertexFormat &format, BufferPtr indexBuffer, IndexFormat::Enum indexFormat);

        virtual ~GL3MeshSubset();

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
