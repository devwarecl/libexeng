
#ifndef __EXENG_GRAPHICS_GL3_GL3MESHSUBSET_HPP__
#define __EXENG_GRAPHICS_GL3_GL3MESHSUBSET_HPP__

#include <exeng/graphics/MeshSubsetBase.hpp>

#include "GL3.hpp"

namespace exeng { namespace graphics { namespace gl3 {
    class GL3MeshSubset : public MeshSubsetBase {
    public:
        GL3MeshSubset(std::vector<std::unique_ptr<Buffer>> vertexBuffers, const VertexFormat &format);
        virtual ~GL3MeshSubset();

        inline GLuint getVertexArrayId() const {
            return this->vertexArrayId;
        }

        virtual TypeInfo getTypeInfo() const override;

    protected:
        GLuint vertexArrayId = 0;
    };
}}}

#endif  // __EXENG_GRAPHICS_GL3_GL3MESHSUBSET_HPP__
