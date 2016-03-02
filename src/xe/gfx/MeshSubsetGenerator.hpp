
#pragma once

#ifndef __xe_gfx_meshsubsetgenerator_hpp__
#define __xe_gfx_meshsubsetgenerator_hpp__

#include <xe/Config.hpp>
#include <xe/Buffer.hpp>
#include <xe/Matrix.hpp>
#include <xe/Vector.hpp>
#include <xe/gfx/Forward.hpp>
#include <xe/gfx/IndexFormat.hpp>
#include <xe/gfx/VertexFormat.hpp>
#include <xe/gfx/MeshSubset.hpp>

namespace xe { namespace gfx {
    
    /**
     * @brief Structure for future generator.
     */
    struct EXENGAPI MeshSubsetGeneratorParams {
        const VertexFormat *format = nullptr;
        IndexFormat::Enum iformat = IndexFormat::Enum::Index32;
        int slices = 1;
        int stacks = 1;

        MeshSubsetGeneratorParams ( 
            const VertexFormat *format = nullptr, 
            IndexFormat::Enum iformat = IndexFormat::Enum::Index32,
            int slices = 1,
            int stacks = 1) {
            
            this->format = format;
            this->iformat = iformat;
            this->slices = slices;
            this->stacks = stacks;
        }
    };

    /**
     * @brief Base class for all SubsetGenerator derived class.
     */
    class EXENGAPI MeshSubsetGenerator {
    public:
        explicit MeshSubsetGenerator(GraphicsDriver *driver);

        virtual ~MeshSubsetGenerator();

        MeshSubsetPtr generate(const MeshSubsetGeneratorParams &params);

        GraphicsDriver* getGraphicsDriver();

        const GraphicsDriver* getGraphicsDriver() const;

    protected:
        virtual int getVertexBufferSize(const MeshSubsetGeneratorParams &params) const = 0;
        virtual int getIndexBufferSize(const MeshSubsetGeneratorParams &params) const = 0;

        virtual void generateVertexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const = 0;
        virtual void generateIndexBuffer(const MeshSubsetGeneratorParams &params, Buffer *buffer) const = 0;

    protected:
        GraphicsDriver *driver = nullptr;
    };
}}

#endif	
