
ADD_DEFINITIONS(-DEXENG_BUILD)

set (BaseFiles_hpp 
    Exeng.hpp DetectEnv.hpp Config.hpp Enum.hpp DataType.hpp 
    Object.hpp Version.hpp Root.hpp
    TypeInfo.hpp TFlags.hpp Buffer.hpp
    HeapBuffer.hpp StaticBuffer.hpp Resource.hpp ResourceLoader.hpp ResourceManager.hpp ISerializable.hpp Timer.hpp
    Common.hpp Boundary.hpp Matrix.hpp Size.hpp Vector.hpp Exception.hpp
)
set (BaseFiles_cpp Enum.cpp Object.cpp 
    Version.cpp  Root.cpp TypeInfo.cpp
    Buffer.cpp HeapBuffer.cpp StaticBuffer.cpp
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


set (FrameworkFiles_cpp
	framework/Application.cpp framework/GraphicsApplication.cpp
)
set (FrameworkFiles_hpp 
	framework/Main.hpp                framework/Main.inl
	framework/Application.hpp         framework/GraphicsApplication.hpp 
)
set (FrameworkFiles ${FrameworkFiles_hpp} ${FrameworkFiles_cpp})

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
	graphics/VertexFormat.hpp 
	graphics/VertexArray.hpp 
    graphics/Vertex.hpp
    graphics/IndexFormat.hpp          
    graphics/Texture.hpp              
    graphics/ColorFormat.hpp          
    graphics/Shader.hpp               
    graphics/ShaderProgram.hpp        

    graphics/MeshSubset.hpp			
    graphics/MeshSubsetBase.hpp	
	graphics/MeshSubsetTransformer.hpp	
	graphics/MeshSubsetGenerator.hpp	

	graphics/TextureManager.hpp
	graphics/TextureLoader.hpp
	graphics/ModernModule.hpp
	graphics/LegacyModule.hpp
	graphics/TextureLoader.hpp
	graphics/MaterialLibrary.hpp
	graphics/ShaderLibrary.hpp 
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
	graphics/VertexArray.cpp
    graphics/IndexFormat.cpp
    graphics/Texture.cpp
    graphics/ColorFormat.cpp
    graphics/Shader.cpp
    graphics/ShaderProgram.cpp
    graphics/MeshSubset.cpp
	graphics/MeshSubsetTransformer.cpp
	graphics/MeshSubsetGenerator.cpp
	graphics/TextureManager.cpp
	graphics/TextureLoader.cpp
	graphics/LegacyModule.cpp
	graphics/ModernModule.cpp
	graphics/MaterialLibrary.cpp
	graphics/ShaderLibrary.cpp
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
    scenegraph/MeshManager.cpp
    scenegraph/IMeshLoader.cpp
    scenegraph/SceneRenderer.cpp
    scenegraph/GenericSceneRenderer.cpp
	scenegraph/SceneNodeAnimator.cpp
	scenegraph/AssetsLibrary.cpp
	scenegraph/GeometryLibrary.cpp
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
    scenegraph/MeshManager.hpp    
    scenegraph/IMeshLoader.hpp    
    scenegraph/SceneRenderer.hpp
    scenegraph/Triangle.hpp
    scenegraph/GenericSceneRenderer.hpp
	scenegraph/SceneNodeAnimator.hpp
	scenegraph/AssetsLibrary.hpp
	scenegraph/GeometryLibrary.hpp
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

SET_PROPERTY (TARGET exeng PROPERTY CXX_STANDARD 14)

IF (WIN32)
	SET_PROPERTY (TARGET exeng PROPERTY RUNTIME_OUTPUT_DIRECTORY ${DEST_BIN_DIR})
ENDIF ()

SOURCE_GROUP(\\			FILES ${BaseFiles})
SOURCE_GROUP(io         FILES ${IoFiles})
SOURCE_GROUP(audio      FILES ${AudioFiles})
SOURCE_GROUP(framework  FILES ${FrameworkFiles})
SOURCE_GROUP(compute    FILES ${ComputeFiles})
SOURCE_GROUP(graphics   FILES ${GraphicsFiles})
SOURCE_GROUP(ui         FILES ${UiFiles})
SOURCE_GROUP(input      FILES ${InputFiles})
SOURCE_GROUP(scenegraph FILES ${ScenegraphFiles})
SOURCE_GROUP(system	    FILES ${SystemFiles})
SOURCE_GROUP(util		FILES ${UtilFiles})

TARGET_LINK_LIBRARIES(exeng ${UNIX_LIBRARIES} lwobject ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES})

INSTALL (
	TARGETS exeng 
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)

INSTALL (FILES ExengConfig.cmake		DESTINATION lib/cmake/exeng/)
INSTALL (FILES ${BaseFiles_hpp}			DESTINATION include/exeng)
INSTALL (FILES ${IoFiles_hpp}			DESTINATION include/exeng/io)
INSTALL (FILES ${AudioFiles_hpp}		DESTINATION include/exeng/audio)
INSTALL (FILES ${FrameworkFiles_hpp}	DESTINATION include/exeng/framework)
INSTALL (FILES ${ComputeFiles_hpp}		DESTINATION include/exeng/compute)
INSTALL (FILES ${GraphicsFiles_hpp}		DESTINATION include/exeng/graphics)
INSTALL (FILES ${UiFiles_hpp}			DESTINATION include/exeng/ui)
INSTALL (FILES ${InputFiles_hpp}		DESTINATION include/exeng/input)
INSTALL (FILES ${ScenegraphFiles_hpp}	DESTINATION include/exeng/scenegraph)
INSTALL (FILES ${SystemFiles_hpp}		DESTINATION include/exeng/system)
INSTALL (FILES ${UtilFiles_hpp}			DESTINATION include/exeng/util)
