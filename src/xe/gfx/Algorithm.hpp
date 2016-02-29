
#pragma once

#ifndef __xe_gfx_algorithm_hpp__
#define __xe_gfx_algorithm_hpp__

#include <xe/Config.hpp>
#include <xe/Buffer.hpp>
#include <xe/Matrix.hpp>
#include <xe/Vector.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/gfx/IndexFormat.hpp>
#include <xe/gfx/VertexFormat.hpp>

namespace xe { namespace gfx {
    extern EXENGAPI void transform(MeshSubset *subset, const Matrix4f &transformation);
    extern EXENGAPI void transform(Mesh *mesh, const Matrix4f &transformation);

    ///**
    // * @brief Structure for future generator.
    // */
    //struct EXENGAPI GeneratorParams {
    //    const VertexFormat *format = nullptr;
    //    IndexFormat::Enum iformat = IndexFormat::Enum::Index32;
    //    int slices = 1;
    //    int stacks = 1;

    //    GeneratorParams( 
    //        const VertexFormat *format, 
    //        IndexFormat::Enum iformat = IndexFormat::Enum::Index32,
    //        int slices = 1,
    //        int stacks = 1) {
    //        
    //        this->format = format;
    //        this->iformat = iformat;
    //        this->slices = slices;
    //        this->stacks = stacks;
    //    }
    //};

    ///**
    // * @brief Base class for all SubsetGenerator derived class.
    // */
    //class EXENGAPI SubsetGenerator {
    //public:
    //    explicit SubsetGenerator(GraphicsDriver *driver, const GeneratorParams &params);

    //    virtual ~SubsetGenerator();

    //    MeshSubset generate();

    //    GraphicsDriver* getGraphicsDriver();

    //    const GraphicsDriver* getGraphicsDriver() const;

    //protected:
    //    virtual int getBufferSize(const GeneratorParams &) const = 0;
    //    virtual int getIBufferSize(const GeneratorParams &) const = 0;

    //    virtual void fillBuffer(const GeneratorParams &) const = 0;
    //    virtual void fillIBuffer(const GeneratorParams &) const = 0;

    //protected:
    //    GraphicsDriver *driver = nullptr;
    //    GeneratorParams params;
    //};

    //extern EXENGAPI int boxbuffersize(const VertexFormat *format, const int slices = 1, const int stacks = 1);
    //extern EXENGAPI int boxibuffersize(const IndexFormat::Enum format, const int slices = 1, const int stacks = 1);
    //extern EXENGAPI void fillboxbuffer(Buffer *buffer, const VertexFormat *format, const int slices = 1, const int stacks = 1);
    //extern EXENGAPI void fillboxibuffer(Buffer *buffer, const IndexFormat::Enum format, const int slices = 1, const int stacks = 1);
    //extern EXENGAPI void genbox(MeshSubset *subset, const int slices = 1, const int stacks = 1);

    //extern EXENGAPI int planebuffersize(const VertexFormat *format, const int slices = 1, const int stacks = 1);
    //extern EXENGAPI int planeibuffersize(const IndexFormat::Enum format, const int slices = 1, const int stacks = 1);
    //extern EXENGAPI void fillplanebuffer(Buffer *buffer, const VertexFormat *format, const int slices = 1, const int stacks = 1);
    //extern EXENGAPI void fillplaneibuffer(Buffer *buffer, const IndexFormat::Enum format, const int slices = 1, const int stacks = 1);
    //extern EXENGAPI void genplane(MeshSubset *subset, const int slices = 1, const int stacks = 1);
}}

#endif	// __xe_gfx_transform_hpp__
