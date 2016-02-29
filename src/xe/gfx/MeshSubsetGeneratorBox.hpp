
#pragma once

#ifndef __xe_gfx_meshsubsetgeneratorbox_hpp__
#define __xe_gfx_meshsubsetgeneratorbox_hpp__

#include <xe/gfx/MeshSubsetGenerator.hpp>

namespace xe { namespace gfx {
    class EXENGAPI MeshSubsetGeneratorBox : public MeshSubsetGenerator {
    public:
        explicit MeshSubsetGeneratorBox(GraphicsDriver *driver);

        virtual ~MeshSubsetGeneratorBox();

    protected:
        virtual int getBufferSize(const MeshSubsetGeneratorParams &params) const override;
        virtual int getIBufferSize(const MeshSubsetGeneratorParams &params) const override;

        virtual void fillBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const override;
        virtual void fillIBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const override;
    };
}}

#endif 
