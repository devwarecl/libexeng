include_directories( ${PROJECT_SOURCE_DIR}/src )

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set (BaseFiles 
  ./Exeng.hpp ./DetectEnv.hpp ./Config.hpp 
  ./Enum.hpp                ./Enum.cpp
  ./DataType.hpp            ./DataType.inl
  ./Object.hpp              ./Object.cpp 
  ./Version.hpp             ./Version.cpp 
  ./Root.hpp                ./Root.cpp
  ./TypeInfo.hpp            ./TypeInfo.cpp
  ./TFlags.hpp              ./TFlags.inl
  ./Buffer.hpp              ./Buffer.cpp 
  ./HeapBuffer.hpp          ./HeapBuffer.cpp 
  ./Resource.hpp            ./Resource.cpp 
  ./ResourceFactory.hpp     ./ResourceFactory.cpp 
)

set (AudioFiles
  ./audio/AudioBuffer.hpp ./audio/AudioBuffer.cpp
  ./audio/Listener.hpp    ./audio/Listener.cpp
  ./audio/Source.hpp      ./audio/Source.cpp
)

set (FrameworkFiles
  ./framework/Application.hpp ./framework/Application.cpp 
  ./framework/Main.hpp        ./framework/Main.inl
)

set (ComputeFiles
  ./compute/ComputeBuffer.cpp     ./compute/ComputeBuffer.hpp  
  ./compute/ComputeDevice.cpp     ./compute/ComputeDevice.hpp  
  ./compute/ComputeManager.cpp    ./compute/ComputeManager.hpp  
  ./compute/Kernel.cpp            ./compute/Kernel.hpp          
)

set (GraphicsFiles
  ./graphics/Primitive.hpp
  ./graphics/ShaderType.hpp           ./graphics/TextureType.hpp 
  ./graphics/GraphicsDriver.hpp       ./graphics/GraphicsDriver.cpp 
  ./graphics/GraphicsDriverBase.hpp   ./graphics/GraphicsDriverBase.inl 
  ./graphics/GraphicsManager.hpp      ./graphics/GraphicsManager.cpp 
  ./graphics/Image.hpp                ./graphics/Image.cpp 
  ./graphics/Material.hpp             ./graphics/Material.cpp 
  ./graphics/PixelFormat.hpp          ./graphics/PixelFormat.cpp 
  ./graphics/VertexFormat.hpp         ./graphics/VertexFormat.cpp
  ./graphics/VertexBuffer.hpp         ./graphics/VertexBuffer.cpp 
  ./graphics/HeapVertexBuffer.hpp     ./graphics/HeapVertexBuffer.cpp 
  ./graphics/HeapIndexBuffer.hpp      ./graphics/HeapIndexBuffer.cpp 
  ./graphics/IndexBuffer.hpp          ./graphics/IndexBuffer.cpp
  ./graphics/Color.hpp                ./graphics/Color.inl
  ./graphics/Texture.hpp              ./graphics/Texture.cpp
  ./graphics/ColorFormat.hpp          ./graphics/ColorFormat.cpp
  ./graphics/IndexArray.hpp           ./graphics/VertexArray.hpp
  ./graphics/Shader.hpp               ./graphics/Shader.cpp
  ./graphics/ShaderProgram.hpp        ./graphics/ShaderProgram.cpp
)

set (UiFiles
  ./ui/Widget.hpp ./ui/Widget.cpp 
  ./ui/Window.hpp ./ui/Window.cpp 
)

set (InputFiles
  ./input/IEventRaiser.hpp    ./input/IEventRaiser.cpp
  ./input/IEventHandler.hpp   ./input/IEventHandler.cpp
  ./input/InputData.hpp       ./input/InputData.cpp 
  ./input/EventData.hpp       ./input/EventData.cpp 
)

set (ScenegraphFiles
  ./scenegraph/SceneNode.hpp      ./scenegraph/SceneNode.cpp 
  ./scenegraph/Scene.hpp          ./scenegraph/Scene.cpp
  ./scenegraph/Camera.hpp         ./scenegraph/Camera.cpp 
  ./scenegraph/Light.hpp          ./scenegraph/Light.cpp
  ./scenegraph/SceneNodeData.hpp  ./scenegraph/SceneNodeData.cpp 
  ./scenegraph/Geometry.hpp       ./scenegraph/Geometry.cpp
  ./scenegraph/Ray.hpp            ./scenegraph/Ray.inl
  ./scenegraph/Plane.hpp          ./scenegraph/Plane.inl
  ./scenegraph/IntersectInfo.hpp  ./scenegraph/IntersectInfo.inl
  ./scenegraph/Sphere.hpp         ./scenegraph/Sphere.inl
  ./scenegraph/Mesh.hpp           ./scenegraph/Mesh.cpp
  ./scenegraph/MeshPart.hpp       ./scenegraph/MeshPart.cpp
  ./scenegraph/MeshManager.hpp    ./scenegraph/MeshManager.cpp
  ./scenegraph/IMeshLoader.hpp    ./scenegraph/IMeshLoader.cpp
  ./scenegraph/SceneManager.hpp   ./scenegraph/SceneManager.cpp
  ./scenegraph/ISceneRenderer.hpp ./scenegraph/ISceneRenderer.cpp
  ./scenegraph/Triangle.hpp       ./scenegraph/Triangle.inl
)

set (SystemFiles
  ./system/Library.hpp        ./system/Library.cpp 
  ./system/Plugin.hpp         ./system/Plugin.cpp 
  ./system/PluginLibrary.hpp  ./system/PluginLibrary.inl
  ./system/PluginManager.hpp  ./system/PluginManager.cpp 
  ./system/LibraryPrivate.hpp ./system/LibraryPrivatePosix.cpp ./system/LibraryPrivateWin32.cpp
)

set (MathFiles
  ./math/Operations.hpp   ./math/Operations.inl
  ./math/Common.hpp       ./math/Common.inl 
  ./math/TBoundary.hpp    ./math/TBoundary.inl 
  ./math/TMatrix.hpp      ./math/TMatrix.inl 
  ./math/TSize.hpp        ./math/TSize.inl 
  ./math/TVector.hpp      ./math/TVector.inl 
)

add_library(exeng SHARED 
  ${BaseFiles}
  ${AudioFiles}
  ${FrameworkFiles}
  ${ComputeFiles}
  ${GraphicsFiles}
  ${UiFiles}
  ${InputFiles}
  ${ScenegraphFiles}
  ${SystemFiles}
  ${MathFiles}
)

source_group(Base       FILES ${BaseFiles})
source_group(Audio      FILES ${AudioFiles})
source_group(Framework  FILES ${FrameworkFiles})
source_group(Compute    FILES ${ComputeFiles})
source_group(Graphics   FILES ${GraphicsFiles})
source_group(Ui         FILES ${UiFiles})
source_group(Input      FILES ${InputFiles})
source_group(Scenegraph FILES ${ScenegraphFiles})
source_group(System	    FILES ${SystemFiles})
source_group(Math       FILES ${MathFiles})

if (UNIX AND NOT APPLE)
  target_link_libraries(exeng dl)
endif()
