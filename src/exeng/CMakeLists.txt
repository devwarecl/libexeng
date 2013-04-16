include_directories( ${PROJECT_SOURCE_DIR}/src )

add_library(exeng 
./Exeng.hpp ./DetectEnv.hpp ./Config.hpp ./DataTypes.hpp 

./Object.hpp ./Object.cpp 
./Version.hpp ./Version.cpp 
./Root.hpp ./Root.cpp
./TypeInfo.hpp ./TypeInfo.cpp
./TFlags.hpp ./TFlags.inl

./graphics/GraphicsDriverBase.cpp ./graphics/GraphicsManager.cpp ./graphics/Image.cpp 
./graphics/Material.cpp ./graphics/PixelFormat.cpp ./graphics/VertexBufferFormat.cpp

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
./scenegraph/VertexBuffer.hpp ./scenegraph/VertexBuffer.cpp
./scenegraph/IndexBuffer.hpp ./scenegraph/IndexBuffer.cpp

./system/Library.hpp ./system/Library.cpp 
./system/Plugin.hpp ./system/Plugin.cpp 
./system/PluginManager.hpp ./system/PluginManager.cpp 
./system/LibraryPrivate.hpp

./math/Operations.hpp ./math/Operations.inl
./math/Common.hpp ./math/Common.inl 
./math/TBoundary.hpp ./math/TBoundary.inl 
./math/TMatrix.hpp ./math/TMatrix.inl 
./math/TSize.hpp ./math/TSize.inl 
./math/TVector.hpp ./math/TVector.inl 
)
