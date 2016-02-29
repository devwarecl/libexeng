
#include "MeshSubsetGenerator.hpp"

#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/VertexArray.hpp>


namespace xe { namespace gfx {
    MeshSubsetGenerator::MeshSubsetGenerator(GraphicsDriver *driver_) : driver(driver_) {}

    MeshSubsetGenerator::~MeshSubsetGenerator() {}

    MeshSubsetPtr MeshSubsetGenerator::generate(const MeshSubsetGeneratorParams &params) {
        const int buffer_size = this->getBufferSize(params);
        const int ibuffer_size = this->getIBufferSize(params);

        BufferPtr buffer = this->getGraphicsDriver()->createVertexBuffer(buffer_size);
        BufferPtr ibuffer = this->getGraphicsDriver()->createIndexBuffer(ibuffer_size);

        this->fillBuffer(params, buffer.get());
        this->fillIBuffer(params, buffer.get());

        return this->getGraphicsDriver()->createMeshSubset(std::move(buffer), params.format, std::move(ibuffer), params.iformat);
    }

    GraphicsDriver* MeshSubsetGenerator::getGraphicsDriver() {
        return driver;
    }

    const GraphicsDriver* MeshSubsetGenerator::getGraphicsDriver() const {
        return driver;
    }
}}
