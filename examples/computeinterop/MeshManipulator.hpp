
#pragma once

#ifndef __meshmanipulator_hpp__
#define __meshmanipulator_hpp__

#include <xe/gfx/Forward.hpp>
#include <xe/cm/ComputeModule.hpp>

/**
 * @brief Mesh manipulator based on computing
 */
class MeshManipulator {
public:
	explicit MeshManipulator(xe::cm::ComputeModulePtr computeModule, xe::gfx::GraphicsDriver *graphicsDriver);

	~MeshManipulator();

	xe::cm::Device* findDevice() const;

	void manipulate(xe::gfx::Mesh *mesh);

private:
	xe::cm::ComputeModulePtr computeModule;
    xe::cm::ContextPtr context;
    xe::cm::QueuePtr queue;
    xe::cm::ProgramPtr program;
    xe::cm::KernelPtr manipulateMeshKernel;
};

#endif
