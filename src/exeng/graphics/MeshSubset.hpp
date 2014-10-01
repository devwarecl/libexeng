
#ifndef __EXENG_GRAPHICS_MESHSUBSET_HPP__
#define __EXENG_GRAPHICS_MESHSUBSET_HPP__

#include <vector>

#include <exeng/Object.hpp>
#include <exeng/Buffer.hpp>
#include <exeng/graphics/Primitive.hpp>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/graphics/IndexFormat.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/Primitive.hpp>

namespace exeng { namespace graphics {
    /**
     * @brief MeshSubset
     **/
    class EXENGAPI MeshSubset : public Object {
    public:
        virtual ~MeshSubset();

        virtual VertexFormat getVertexFormat() const = 0;
        virtual IndexFormat::Enum getIndexFormat() const = 0;

        virtual int getBufferCount() const = 0;
        virtual Buffer* getBuffer(const int index) = 0;
        virtual const Buffer* getBuffer(const int index) const = 0;

        virtual Buffer* getIndexBuffer() = 0;
        virtual const Buffer* getIndexBuffer() const = 0;

        virtual Primitive::Enum getPrimitive() const = 0;
        virtual void setPrimitive(Primitive::Enum primitiveType) = 0;

        virtual const Material* getMaterial() const = 0;
        virtual void setMaterial(const Material *material) = 0;
    };
}}

#endif  // __EXENG_GRAPHICS_MESHSUBSET_HPP__
