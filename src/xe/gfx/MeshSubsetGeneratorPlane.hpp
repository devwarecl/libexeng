
#pragma once

#ifndef __xe_gfx_meshsubsetgeneratorplane_hpp__
#define __xe_gfx_meshsubsetgeneratorplane_hpp__

#include <xe/gfx/MeshSubsetGenerator.hpp>

namespace xe { namespace gfx {
    class EXENGAPI MeshSubsetGeneratorPlane: public MeshSubsetGenerator {
    public:
        explicit MeshSubsetGeneratorPlane(GraphicsDriver *driver);

    protected:
        virtual int getBufferSize(const MeshSubsetGeneratorParams &params) const override;
        virtual int getIBufferSize(const MeshSubsetGeneratorParams &params) const override;

        virtual void fillBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const override;
        virtual void fillIBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const override;
    };
}}

#endif 
