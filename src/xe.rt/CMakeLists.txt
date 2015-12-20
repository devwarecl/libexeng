
add_definitions(-DRAYTRACER_ROOT_FOLDER="${PROJECT_SOURCE_DIR}/src/exeng.raytracer/")

find_package(OpenGL REQUIRED)
find_package(OpenCL)
find_package(glfw3 REQUIRED)
# find_package(PNG REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
  find_package(Threads REQUIRED)
endif()

include_directories(${GLFW3_INCLUDE_DIR})
include_directories(${OPENCL_INCLUDE_DIRS})
# include_directories(${PNG_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add_definitions(${PNG_DEFINITIONS})
add_definitions(-D__CL_ENABLE_EXCEPTIONS)

link_directories(${GLFW3_LIBRARY_DIR})
link_directories(${OpenGL_LIBRARY_DIR})
# link_directories(${PNG_LIBRARY})

# Grouping
set (BaseFiles
	RayTracerApp.hpp                RayTracerApp.cpp 
	RayTracerApp2.hpp               RayTracerApp2.cpp 
    RayTracerSceneRenderer.hpp      RayTracerSceneRenderer.cpp 
    SceneLoader.hpp                 SceneLoader.cpp 
)

set (Tracers
	tracers/Tracer.hpp              tracers/Tracer.cpp 
    tracers/SoftwareTracer.hpp      tracers/SoftwareTracer.cpp 
    tracers/HardwareTracer.hpp      tracers/HardwareTracer.cpp 
	tracers/MultiHardwareTracer.hpp	tracers/MultiHardwareTracer.cpp 
	
	tracers/TracerFactory.hpp		tracers/TracerFactory.cpp 
	tracers/TracerCreator.hpp		tracers/TracerCreator.cpp 
)

set (Samplers
	samplers/Sampler.hpp            samplers/Sampler.cpp 
    samplers/JitteredSampler.hpp    samplers/JitteredSampler.cpp 
)

set (Renderers
	renderers/HardwareRenderer.hpp			renderers/HardwareRenderer.cpp
	renderers/HardwareRendererPrivate.hpp	renderers/HardwareRendererPrivate.cpp
	renderers/SoftwareRenderer.hpp			renderers/SoftwareRenderer.cpp
)

set (Loaders
	loaders/LwoMeshLoader.hpp		loaders/LwoMeshLoader.cpp
)

# process resources
set (raytracer_resources_src
	resources/TraceRay.cl
	resources/MultiHardwareTracer.cl
	resources/ComputeSynthesisDataOld.cl
	resources/VertexShader.glsl
	resources/FragmentShader.glsl
	resources/Assets.xml
)

SET (raytracer_resources )

# iterate over resource files for compilation
FOREACH(resource_src ${raytracer_resources_src})
	ADD_CUSTOM_COMMAND (
		OUTPUT	${CMAKE_CURRENT_BINARY_DIR}/${resource_src}.hpp 
				${CMAKE_CURRENT_BINARY_DIR}/${resource_src}.cpp 
		COMMAND file2cpp ${CMAKE_CURRENT_SOURCE_DIR}/${resource_src} -o ${CMAKE_CURRENT_BINARY_DIR}/resources
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${resource_src}
	)
	
	LIST (APPEND raytracer_resources ${resource_src}.hpp ${resource_src}.cpp)
ENDFOREACH(resource_src)

ADD_EXECUTABLE (xe.rt 
	${BaseFiles} 
	${Tracers} 
	${Samplers} 
	${Loaders} 
	${Renderers} 
	${raytracer_resources} 
	${raytracer_resources_src}
)

SET_PROPERTY (TARGET xe.rt PROPERTY CXX_STANDARD 14)
IF (WIN32)
    SET_PROPERTY(TARGET xe.rt	PROPERTY RUNTIME_OUTPUT_DIRECTORY ${DEST_BIN_DIR})
ENDIF ()

TARGET_LINK_LIBRARIES(xe.rt xe xe.main ${OPENGL_LIBRARIES} ${OPENCL_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${PNG_LIBRARIES})

SOURCE_GROUP (\\		FILES ${BaseFiles})
SOURCE_GROUP (samplers	FILES ${Samplers})
SOURCE_GROUP (resources	FILES ${raytracer_resources_src})
SOURCE_GROUP (loaders	FILES ${Loaders})
SOURCE_GROUP (tracers	FILES ${Tracers})
SOURCE_GROUP (renderers	FILES ${Renderers})
