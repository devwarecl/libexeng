
add_definitions(-DEXENG_BUILD)

include_directories( ${PROJECT_SOURCE_DIR}/src )

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set (BaseFiles 
  Exeng.hpp DetectEnv.hpp Config.hpp 
  Enum.hpp                Enum.cpp
  DataType.hpp            DataType.inl
  Object.hpp              Object.cpp 
  Version.hpp             Version.cpp 
  Root.hpp                Root.cpp
  TypeInfo.hpp            TypeInfo.cpp
  TFlags.hpp              TFlags.inl
  Buffer.hpp              Buffer.cpp 
  HeapBuffer.hpp          HeapBuffer.cpp 
  Resource.hpp            Resource.cpp 
  ResourceManager.hpp     ResourceManager.cpp 
  Timer.hpp               Timer_Win.cpp Timer_Unix.cpp 
)

set (IoFiles 
  io/Stream.hpp              io/Stream.cpp          io/Stream.inl
  io/StreamBuffer.hpp        io/StreamBuffer.cpp
)

set (AudioFiles
  audio/AudioBuffer.hpp audio/AudioBuffer.cpp
  audio/Listener.hpp    audio/Listener.cpp
  audio/Source.hpp      audio/Source.cpp
)

set (FrameworkFiles
  framework/Main.hpp                framework/Main.inl
  framework/Application.hpp         framework/Application.cpp 
  framework/GraphicsApplication.hpp framework/GraphicsApplication.inl
)

set (ComputeFiles
  compute/ComputeBuffer.cpp     compute/ComputeBuffer.hpp  
  compute/ComputeDevice.cpp     compute/ComputeDevice.hpp  
  compute/ComputeManager.cpp    compute/ComputeManager.hpp  
  compute/Kernel.cpp            compute/Kernel.hpp          
)

set (GraphicsFiles
  graphics/Primitive.hpp
  graphics/ShaderType.hpp           graphics/TextureType.hpp 
  graphics/GraphicsDriver.hpp       graphics/GraphicsDriver.cpp 
  graphics/GraphicsDriverBase.hpp   graphics/GraphicsDriverBase.inl 
  graphics/GraphicsManager.hpp      graphics/GraphicsManager.cpp 
  graphics/Image.hpp                graphics/Image.cpp 
  graphics/Material.hpp             graphics/Material.cpp 
  graphics/PixelFormat.hpp          graphics/PixelFormat.cpp 
  graphics/VertexFormat.hpp         graphics/VertexFormat.cpp
  graphics/VertexBuffer.hpp         graphics/VertexBuffer.cpp 
  graphics/HeapVertexBuffer.hpp     graphics/HeapVertexBuffer.cpp 
  graphics/HeapIndexBuffer.hpp      graphics/HeapIndexBuffer.cpp 
  graphics/IndexBuffer.hpp          graphics/IndexBuffer.cpp
  graphics/Color.hpp                graphics/Color.inl
  graphics/Texture.hpp              graphics/Texture.cpp
  graphics/ColorFormat.hpp          graphics/ColorFormat.cpp
  graphics/IndexArray.hpp           graphics/VertexArray.hpp
  graphics/Shader.hpp               graphics/Shader.cpp
  graphics/ShaderProgram.hpp        graphics/ShaderProgram.cpp
)

set (UiFiles
  ui/Container.hpp                  ui/Container.cpp 
  
  ui/Control.hpp                    ui/Control.cpp 
  ui/Window.hpp                     ui/Window.cpp
  ui/Label.hpp                      ui/Label.cpp 
  ui/Button.hpp                     ui/Button.cpp 
  
  ui/ControlPrivate.hpp         ui/ControlPrivate.cpp 
  ui/WindowPrivate.hpp          ui/WindowPrivate.cpp 
  ui/ButtonPrivate.hpp          ui/ButtonPrivate.cpp 
  ui/LabelPrivate.hpp           ui/LabelPrivate.cpp 
  
  ui/win32/ControlPrivate.hpp   ui/win32/ControlPrivate.cpp 
  ui/win32/WindowPrivate.hpp    ui/win32/WindowPrivate.cpp
  ui/win32/LabelPrivate.hpp     ui/win32/LabelPrivate.cpp 
  ui/win32/ButtonPrivate.hpp    ui/win32/ButtonPrivate.cpp 
)

set (InputFiles
  input/IEventRaiser.hpp    input/IEventRaiser.cpp
  input/IEventHandler.hpp   input/IEventHandler.cpp
  input/InputData.hpp       input/InputData.cpp 
  input/EventData.hpp       input/EventData.cpp 
)

set (ScenegraphFiles
  scenegraph/SceneNode.hpp      scenegraph/SceneNode.cpp 
  scenegraph/Scene.hpp          scenegraph/Scene.cpp
  scenegraph/Camera.hpp         scenegraph/Camera.cpp 
  scenegraph/Light.hpp          scenegraph/Light.cpp
  scenegraph/SceneNodeData.hpp  scenegraph/SceneNodeData.cpp 
  scenegraph/Geometry.hpp       scenegraph/Geometry.cpp
  scenegraph/Box.hpp            scenegraph/Box.inl
  scenegraph/Ray.hpp            scenegraph/Ray.inl
  scenegraph/Plane.hpp          scenegraph/Plane.inl
  scenegraph/Intersect.hpp      scenegraph/Intersect.inl
  scenegraph/IntersectInfo.hpp  scenegraph/IntersectInfo.inl
  scenegraph/Sphere.hpp         scenegraph/Sphere.inl
  scenegraph/Mesh.hpp           scenegraph/Mesh.cpp
  scenegraph/MeshPart.hpp       scenegraph/MeshPart.cpp
  scenegraph/MeshManager.hpp    scenegraph/MeshManager.cpp
  scenegraph/IMeshLoader.hpp    scenegraph/IMeshLoader.cpp
  scenegraph/SceneManager.hpp   scenegraph/SceneManager.cpp
  scenegraph/ISceneRenderer.hpp scenegraph/ISceneRenderer.cpp
  scenegraph/Triangle.hpp       scenegraph/Triangle.inl
)

set (SystemFiles
  system/Library.hpp        system/Library.cpp 
  system/Plugin.hpp         system/Plugin.cpp 
  system/PluginLibrary.hpp  system/PluginLibrary.inl
  system/PluginManager.hpp  system/PluginManager.cpp 
  system/LibraryPrivate.hpp system/LibraryPrivatePosix.cpp system/LibraryPrivateWin32.cpp
)

set (MathFiles
  math/Operations.hpp   math/Operations.inl
  math/Common.hpp       math/Common.inl 
  math/TBoundary.hpp    math/TBoundary.inl 
  math/TMatrix.hpp      math/TMatrix.inl 
  math/TSize.hpp        math/TSize.inl 
  math/TVector.hpp      math/TVector.inl 
)

add_library(exeng SHARED 
  ${BaseFiles}
  ${IoFiles}
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

source_group(base       FILES ${BaseFiles})
source_group(io         FILES ${IoFiles})
source_group(audio      FILES ${AudioFiles})
source_group(framework  FILES ${FrameworkFiles})
source_group(compute    FILES ${ComputeFiles})
source_group(graphics   FILES ${GraphicsFiles})
source_group(ui         FILES ${UiFiles})
source_group(input      FILES ${InputFiles})
source_group(scenegraph FILES ${ScenegraphFiles})
source_group(system	    FILES ${SystemFiles})
source_group(math       FILES ${MathFiles})

if (UNIX AND NOT APPLE)
  target_link_libraries(exeng dl rt)
endif()

add_subdirectory(ui/win32)

add_subdirectory(ui/gtk2)
