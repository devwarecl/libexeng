include_directories( ${PROJECT_SOURCE_DIR}/src )

add_library(exeng SHARED
./Exeng.hpp ./DetectEnv.hpp ./Config.hpp 

./DataType.hpp ./DataType.inl
./Object.hpp ./Object.cpp 
./Version.hpp ./Version.cpp 
./Root.hpp ./Root.cpp
./TypeInfo.hpp ./TypeInfo.cpp
./TFlags.hpp ./TFlags.inl
./Buffer.hpp ./Buffer.cpp 
./HeapBuffer.hpp ./HeapBuffer.cpp 

./graphics/GraphicsDriver.hpp ./graphics/GraphicsDriver.cpp 
./graphics/GraphicsDriverBase.hpp ./graphics/GraphicsDriverBase.inl 
./graphics/GraphicsManager.hpp ./graphics/GraphicsManager.cpp 
./graphics/Image.hpp ./graphics/Image.cpp 
./graphics/Material.hpp ./graphics/Material.cpp 
./graphics/PixelFormat.hpp ./graphics/PixelFormat.cpp 
./graphics/VertexFormat.hpp ./graphics/VertexFormat.cpp
./graphics/VertexBuffer.hpp ./graphics/VertexBuffer.cpp 
./graphics/HeapVertexBuffer.hpp ./graphics/HeapVertexBuffer.cpp 
./graphics/HeapIndexBuffer.hpp ./graphics/HeapIndexBuffer.cpp 
./graphics/IndexBuffer.hpp ./graphics/IndexBuffer.cpp
./graphics/Color.hpp ./graphics/Color.inl
./graphics/Texture.hpp
./graphics/Primitive.hpp
./graphics/ColorFormat.hpp ./graphics/ColorFormat.cpp
./graphics/IndexArray.hpp ./graphics/VertexArray.hpp
./graphics/Shader.hpp ./graphics/Shader.cpp
./graphics/ShaderProgram.hpp ./graphics/ShaderProgram.cpp

./graphics/rasterization/Rasterizer.hpp ./graphics/rasterization/Rasterizer.cpp

./graphics/raytracing/Tracer.hpp ./graphics/raytracing/Tracer.cpp 
./graphics/raytracing/ISampler.hpp ./graphics/raytracing/ISampler.cpp 

./ui/Widget.hpp ./ui/Widget.cpp 
./ui/Window.hpp ./ui/Window.cpp 

./input/IEventRaiser.hpp ./input/IEventRaiser.cpp
./input/IEventHandler.hpp ./input/IEventHandler.cpp
./input/InputData.hpp ./input/InputData.cpp 

./scenegraph/SceneNode.hpp ./scenegraph/SceneNode.cpp ./scenegraph/Scene.hpp ./scenegraph/Scene.cpp
./scenegraph/Camera.hpp ./scenegraph/Camera.cpp ./scenegraph/Light.hpp ./scenegraph/Light.cpp
./scenegraph/SceneNodeData.hpp ./scenegraph/SceneNodeData.cpp 
./scenegraph/Geometry.hpp ./scenegraph/Geometry.cpp
./scenegraph/Ray.hpp ./scenegraph/Ray.inl
./scenegraph/Plane.hpp ./scenegraph/Plane.inl
./scenegraph/IntersectInfo.hpp ./scenegraph/IntersectInfo.cpp
./scenegraph/Sphere.hpp ./scenegraph/Sphere.inl
./scenegraph/Mesh.hpp ./scenegraph/Mesh.cpp
./scenegraph/MeshPart.hpp ./scenegraph/MeshPart.cpp
./scenegraph/MeshManager.hpp ./scenegraph/MeshManager.cpp
./scenegraph/IMeshLoader.hpp ./scenegraph/IMeshLoader.cpp
./scenegraph/SceneManager.hpp ./scenegraph/SceneManager.cpp
./scenegraph/ISceneRenderer.hpp ./scenegraph/ISceneRenderer.cpp

./system/Library.hpp ./system/Library.cpp 
./system/Plugin.hpp ./system/Plugin.cpp 
./system/PluginLibrary.hpp ./system/PluginLibrary.inl
./system/PluginManager.hpp ./system/PluginManager.cpp 
./system/LibraryPrivate.hpp ./system/LibraryPrivatePosix.cpp ./system/LibraryPrivateWin32.cpp

./math/Operations.hpp ./math/Operations.inl
./math/Common.hpp ./math/Common.inl 
./math/TBoundary.hpp ./math/TBoundary.inl 
./math/TMatrix.hpp ./math/TMatrix.inl 
./math/TSize.hpp ./math/TSize.inl 
./math/TVector.hpp ./math/TVector.inl 
)

target_link_libraries(exeng dl)
