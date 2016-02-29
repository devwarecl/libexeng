
#pragma once

#ifndef __xe_gfx_meshsubsetgeneratorplane_hpp__
#define __xe_gfx_meshsubsetgeneratorplane_hpp__

#include <xe/gfx/MeshSubsetGenerator.hpp>

namespace xe { namespace gfx {
    class EXENGAPI MeshSubsetGeneratorPlane: public MeshSubsetGenerator {
    public:
        explicit MeshSubsetGeneratorPlane(GraphicsDriver *driver);

    protected:
        virtual int getVertexBufferSize(const MeshSubsetGeneratorParams &params) const override;
        virtual int getIndexBufferSize(const MeshSubsetGeneratorParams &params) const override;

        virtual void generateVertexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const override;
        virtual void generateIndexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const override;
    };
}}

#endif 
