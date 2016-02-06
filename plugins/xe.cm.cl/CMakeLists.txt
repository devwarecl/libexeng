
find_package(OpenCL REQUIRED)

# OpenCL configuration
include_directories(${OPENCL_INCLUDE_DIRS})
add_definitions(-D__CL_ENABLE_EXCEPTIONS)
add_definitions(-DCL_USE_DEPRECATED_OPENCL_1_1_APIS)

set (xe_cm_cl_src
	ComputeModuleCL.cpp ComputeModuleCL.hpp 
	ComputeModuleFactoryCL.cpp ComputeModuleFactoryCL.hpp 
	BufferCL.cpp BufferCL.hpp 
	KernelCL.cpp KernelCL.hpp 
	PluginCL.cpp PluginCL.hpp 
	QueueCL.cpp QueueCL.hpp 
	ProgramCL.cpp ProgramCL.hpp 
	ProgramModuleCL.cpp ProgramModuleCL.hpp 
)

source_group(\\ FILES ${xe_cm_cl_src})

add_library(xe.cm.cl SHARED ${xe_cm_cl_src})

set_property(TARGET xe.cm.cl PROPERTY CXX_STANDARD 14)

target_link_libraries(xe.cm.cl xe ${OPENCL_LIBRARIES})

install (
	TARGETS xe.cm.cl 
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
