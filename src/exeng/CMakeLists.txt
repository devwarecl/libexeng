
add_definitions(-DEXENG_BUILD -DBOOST_ALL_NO_LIB)

include_directories( ${PROJECT_SOURCE_DIR}/src )

# Boost Configuration
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS filesystem system  REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set (BaseFiles_hpp 
    Exeng.hpp DetectEnv.hpp Config.hpp Enum.hpp DataType.hpp 
    Object.hpp Version.hpp Root.hpp
    TypeInfo.hpp TFlags.hpp Buffer.hpp
    HeapBuffer.hpp Resource.hpp ResourceLoader.hpp ResourceManager.hpp ISerializable.hpp Timer.hpp
    Common.hpp Boundary.hpp Matrix.hpp Size.hpp Vector.hpp Exception.hpp
)
set (BaseFiles_cpp Enum.cpp Object.cpp 
    Version.cpp  Root.cpp TypeInfo.cpp
    Buffer.cpp HeapBuffer.cpp 
    Resource.cpp ResourceLoader.cpp ResourceManager.cpp 
    ISerializable.cpp Timer_Win.cpp Timer_Unix.cpp Exception.cpp
)
set (BaseFiles ${BaseFiles_hpp} ${BaseFiles_cpp})

set (IoFiles_cpp io/Stream.cpp io/Stream.inl io/StreamBuffer.cpp)
set (IoFiles_hpp io/Stream.hpp               io/StreamBuffer.hpp)
set (IoFiles ${IoFiles_hpp} ${IoFiles_hpp})

set (AudioFiles_cpp audio/AudioBuffer.cpp audio/Listener.cpp audio/Source.cpp)
set (AudioFiles_hpp audio/AudioBuffer.hpp audio/Listener.hpp audio/Source.hpp)
set (AudioFiles ${AudioFiles_hpp} ${AudioFiles_cpp})

set (FrameworkFiles
    framework/Main.hpp                framework/Main.inl
    framework/Application.hpp         framework/Application.cpp 
    framework/GraphicsApplication.hpp framework/GraphicsApplication.inl
)

set (ComputeFiles_hpp
    compute/ComputeBuffer.hpp compute/ComputeDevice.hpp compute/ComputeManager.hpp compute/Kernel.hpp 
)
set (ComputeFiles_cpp
    compute/ComputeBuffer.cpp compute/ComputeDevice.cpp compute/ComputeManager.cpp compute/Kernel.cpp            
)
set (ComputeFiles ${ComputeFiles_hpp} ${ComputeFiles_cpp})

set (GraphicsFiles_hpp
    graphics/Primitive.hpp
    graphics/ShaderType.hpp           
    graphics/TextureType.hpp			
    graphics/GraphicsDriver.hpp       
    graphics/GraphicsDriverBase.hpp   
    graphics/GraphicsManager.hpp      
    graphics/Image.hpp                
    graphics/Material.hpp             
    graphics/PixelFormat.hpp          
    graphics/Vertex.hpp               
    graphics/VertexFormat.hpp         
    graphics/VertexBuffer.hpp         
    graphics/VertexBuffer.hpp         
    graphics/IBufferFactory.hpp       
    graphics/HeapVertexBuffer.hpp      
    graphics/HeapIndexBuffer.hpp      
    graphics/IndexBuffer.hpp          
    graphics/IndexFormat.hpp          
    graphics/Texture.hpp              
    graphics/ColorFormat.hpp          
    graphics/IndexArray.hpp           
    graphics/Shader.hpp               
    graphics/ShaderProgram.hpp        
    graphics/MeshSubset.hpp			
    graphics/MeshSubsetBase.hpp		
	graphics/TextureManager.hpp
)

set (GraphicsFiles_cpp
    graphics/TextureType.cpp 
    graphics/GraphicsDriver.cpp 
    graphics/GraphicsManager.cpp 
    graphics/Image.cpp 
    graphics/Material.cpp 
    graphics/PixelFormat.cpp 
    graphics/Vertex.cpp
    graphics/VertexFormat.cpp
    graphics/VertexBuffer.cpp 
    graphics/VertexBuffer.cpp 
    graphics/IBufferFactory.cpp
    graphics/HeapVertexBuffer.cpp
    graphics/HeapIndexBuffer.cpp 
    graphics/IndexBuffer.cpp
    graphics/IndexFormat.cpp
    graphics/Texture.cpp
    graphics/ColorFormat.cpp
    graphics/VertexArray.hpp
    graphics/Shader.cpp
    graphics/ShaderProgram.cpp
    graphics/MeshSubset.cpp
	graphics/TextureManager.cpp
)
set (GraphicsFiles ${GraphicsFiles_hpp} ${GraphicsFiles_cpp})

set (UiFiles_cpp
    ui/Container.cpp 
    ui/Control.cpp 
    ui/Window.cpp
    ui/Label.cpp 
    ui/Button.cpp 
    ui/ControlPrivate.cpp 
    ui/WindowPrivate.cpp 
    ui/ButtonPrivate.cpp 
    ui/LabelPrivate.cpp 
    ui/win32/ControlPrivate.cpp
    ui/win32/WindowPrivate.cpp
    ui/win32/LabelPrivate.cpp 
    ui/win32/ButtonPrivate.cpp 
)
set (UiFiles_hpp
    ui/Container.hpp
    ui/Control.hpp
    ui/Window.hpp
    ui/Label.hpp
    ui/Button.hpp
    ui/ControlPrivate.hpp         
    ui/WindowPrivate.hpp          
    ui/ButtonPrivate.hpp          
    ui/LabelPrivate.hpp           
    ui/win32/ControlPrivate.hpp    
    ui/win32/WindowPrivate.hpp    
    ui/win32/LabelPrivate.hpp     
    ui/win32/ButtonPrivate.hpp    
)
set (UiFiles ${UiFiles_hpp} ${UiFiles_cpp})

set (InputFiles_cpp
    input/IEventRaiser.cpp
    input/IEventHandler.cpp
    input/InputData.cpp 
    input/EventData.cpp 
)
set (InputFiles_hpp
    input/IEventRaiser.hpp    
    input/IEventHandler.hpp   
    input/InputData.hpp       
    input/EventData.hpp       
)
set (InputFiles ${InputFiles_hpp} ${InputFiles_cpp})

set (ScenegraphFiles_cpp
    scenegraph/SceneNode.cpp 
    scenegraph/Scene.cpp
    scenegraph/Camera.cpp 
    scenegraph/Light.cpp
    scenegraph/SceneNodeData.cpp 
    scenegraph/Geometry.cpp
    scenegraph/Mesh.cpp
    scenegraph/MeshPart.cpp
    scenegraph/MeshManager.cpp
    scenegraph/IMeshLoader.cpp
    scenegraph/SceneManager.cpp
    scenegraph/SceneRenderer.cpp
    scenegraph/GenericSceneRenderer.cpp
)

set (ScenegraphFiles_hpp
    scenegraph/SceneNode.hpp      
    scenegraph/Scene.hpp          
    scenegraph/Camera.hpp         
    scenegraph/Light.hpp          
    scenegraph/SceneNodeData.hpp  
    scenegraph/Geometry.hpp       
    scenegraph/TSolidGeometry.hpp 
    scenegraph/Segment.hpp 
    scenegraph/Box.hpp            
    scenegraph/Ray.hpp            
    scenegraph/Plane.hpp          
    scenegraph/Intersect.hpp      
    scenegraph/IntersectInfo.hpp  
    scenegraph/Sphere.hpp         
    scenegraph/Mesh.hpp           
    scenegraph/MeshPart.hpp       
    scenegraph/MeshManager.hpp    
    scenegraph/IMeshLoader.hpp    
    scenegraph/SceneManager.hpp   
    scenegraph/SceneRenderer.hpp
    scenegraph/Triangle.hpp
    scenegraph/GenericSceneRenderer.hpp
)
set (ScenegraphFiles ${ScenegraphFiles_hpp} ${ScenegraphFiles_cpp})


set (SystemFiles_cpp
    system/Library.cpp 
    system/Plugin.cpp 
    system/PluginManager.cpp 
    system/LibraryPrivatePosix.cpp system/LibraryPrivateWin32.cpp
)
set (SystemFiles_hpp
    system/Library.hpp        
    system/Plugin.hpp         
    system/PluginLibrary.hpp  
    system/PluginManager.hpp  
    system/LibraryPrivate.hpp 
)
set (SystemFiles ${SystemFiles_hpp} ${SystemFiles_cpp})

set (UtilFiles_cpp 
	util/FrameCounter.cpp 
	util/MessageBox.cpp)

set (UtilFiles_hpp 
	util/FrameCounter.hpp 
	util/MessageBox.hpp)

set (UtilFiles ${UtilFiles_hpp} ${UtilFiles_cpp})

add_library (exeng SHARED
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
    ${UtilFiles}
)

source_group(\\			FILES ${BaseFiles})
source_group(io         FILES ${IoFiles})
source_group(audio      FILES ${AudioFiles})
source_group(framework  FILES ${FrameworkFiles})
source_group(compute    FILES ${ComputeFiles})
source_group(graphics   FILES ${GraphicsFiles})
source_group(ui         FILES ${UiFiles})
source_group(input      FILES ${InputFiles})
source_group(scenegraph FILES ${ScenegraphFiles})
source_group(system	    FILES ${SystemFiles})
source_group(util		FILES ${UtilFiles})

if(UNIX AND NOT APPLE)
	SET (UNIX_libs dl rt)
endif()

target_link_libraries(exeng ${UNIX_libs} lwobject ${Boost_LIBRARIES})

# install (TARGET exeng DESTINATION lib)
# install (FILES ${} DESTINATION include)
