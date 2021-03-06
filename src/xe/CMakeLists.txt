
ADD_DEFINITIONS(-DEXENG_BUILD)

set (BaseFiles_hpp 
	Forward.hpp
    DetectEnv.hpp Config.hpp Enum.hpp DataType.hpp 
    Object.hpp Version.hpp Core.hpp
    TypeInfo.hpp TFlags.hpp Buffer.hpp
    HeapBuffer.hpp StaticBuffer.hpp

    ProductLoader.hpp ProductManager.hpp ProductManagerImpl.hpp
	Timer.hpp
    Common.hpp Boundary.hpp Matrix.hpp Vector.hpp Exception.hpp Quaternion.hpp
	Application.hpp ApplicationRT.hpp 
)

set (BaseFiles_cpp Enum.cpp Object.cpp 
    Version.cpp  Core.cpp TypeInfo.cpp
    Buffer.cpp HeapBuffer.cpp StaticBuffer.cpp
    Timer_Win.cpp Timer_Unix.cpp Exception.cpp
	Application.cpp ApplicationRT.cpp
)
set (BaseFiles ${BaseFiles_hpp} ${BaseFiles_cpp})

set (AudioFiles_cpp sfx/AudioBuffer.cpp sfx/Listener.cpp sfx/Source.cpp)
set (AudioFiles_hpp sfx/AudioBuffer.hpp sfx/Listener.hpp sfx/Source.hpp)
set (AudioFiles ${AudioFiles_hpp} ${AudioFiles_cpp})

set (ComputeFiles_hpp
    cm/Forward.hpp
    cm/ComputeLanguage.hpp
    cm/ComputeManager.hpp
    cm/Device.hpp
    cm/DeviceInfo.hpp
    cm/ComputeModule.hpp
    cm/ComputeModuleDesc.hpp
    cm/ComputeModuleFactory.hpp
    cm/Context.hpp
    cm/ContextOptions.hpp
	cm/Platform.hpp
	cm/PlatformInfo.hpp
    cm/Program.hpp
    cm/ProgramModule.hpp
    cm/Kernel.hpp
    cm/Queue.hpp
)

set (ComputeFiles_cpp
    cm/ComputeLanguage.cpp
    cm/ComputeManager.cpp
    cm/Device.cpp
    cm/DeviceInfo.cpp
    cm/ComputeModule.cpp
    cm/ComputeModuleDesc.cpp
    cm/ComputeModuleFactory.cpp
    cm/Context.cpp
    cm/ContextOptions.cpp
    cm/Program.cpp
    cm/ProgramModule.cpp
    cm/Kernel.cpp
    cm/Queue.cpp
)
set (ComputeFiles ${ComputeFiles_hpp} ${ComputeFiles_cpp})

set (GraphicsFiles_hpp
    gfx/Primitive.hpp
    gfx/ShaderType.hpp           
    gfx/TextureType.hpp			
    gfx/Device.hpp       
    gfx/GraphicsDriverBase.hpp   
    gfx/GraphicsManager.hpp      
    gfx/Image.hpp                
	gfx/ImageLoader.hpp 
    gfx/Material.hpp 
    gfx/PixelFormat.hpp          
	gfx/VertexFormat.hpp 
	gfx/VertexArray.hpp 
    gfx/Vertex.hpp
    gfx/IndexFormat.hpp          
    gfx/Texture.hpp              
    gfx/Shader.hpp               
    gfx/ShaderProgram.hpp        
	gfx/Forward.hpp        
    gfx/Subset.hpp			
    gfx/MeshSubsetBase.hpp	
	gfx/Algorithm.hpp
	gfx/Mesh.hpp
    gfx/MeshManager.hpp
    gfx/MeshLoader.hpp
	gfx/TextureManager.hpp
	gfx/TextureLoader.hpp
	gfx/TextureLoaderImage.hpp
	gfx/ModernModule.hpp
	gfx/LegacyModule.hpp
	gfx/TextureLoader.hpp
	gfx/MaterialLibrary.hpp
	gfx/MaterialLibraryImpl.hpp
	gfx/ShaderLibrary.hpp 
	gfx/MeshSubsetGenerator.hpp
	gfx/MeshSubsetGeneratorPlane.hpp
	gfx/MeshSubsetGeneratorBox.hpp
)

set (GraphicsFiles_cpp
    gfx/TextureType.cpp 
    gfx/Device.cpp 
    gfx/GraphicsManager.cpp 
    gfx/Image.cpp 
	gfx/ImageLoader.cpp 
    gfx/Material.cpp 
    gfx/PixelFormat.cpp 
    gfx/Vertex.cpp
    gfx/VertexFormat.cpp
	gfx/VertexArray.cpp
    gfx/IndexFormat.cpp
    gfx/Texture.cpp
    gfx/Shader.cpp
    gfx/ShaderProgram.cpp
    gfx/Subset.cpp
	gfx/Algorithm.cpp
	gfx/Mesh.cpp
    gfx/MeshManager.cpp
    gfx/MeshLoader.cpp
	gfx/TextureManager.cpp
	gfx/TextureLoader.cpp
	gfx/TextureLoaderImage.cpp
	gfx/LegacyModule.cpp
	gfx/ModernModule.cpp
	gfx/MaterialLibrary.cpp
	gfx/ShaderLibrary.cpp
	gfx/MeshSubsetGenerator.cpp
	gfx/MeshSubsetGeneratorPlane.cpp
	gfx/MeshSubsetGeneratorBox.cpp
)
set (GraphicsFiles ${GraphicsFiles_hpp} ${GraphicsFiles_cpp})

set (InputFiles_hpp
	input/Event.hpp 
	input/IEvent.hpp 
	input/IEventHandler.hpp 
	input/IInputDevice.hpp 
	input/IInputManager.hpp 
	input/IKeyboard.hpp 
	input/IMouse.hpp 
	input/InputManager.hpp 
	input/KeyboardStatus.hpp 
	input/KeyCode.hpp 
	input/KeyStatus.hpp 
	input/KeyStroke.hpp 
)

set (InputFiles_cpp
	input/InputManager.cpp 
	input/KeyboardStatus.cpp 
)

set (InputFiles ${InputFiles_hpp} ${InputFiles_cpp})

set (ScenegraphFiles_cpp
	sg/Renderable.cpp
	sg/Pipeline.cpp
    sg/SceneNode.cpp 
    sg/Scene.cpp
	sg/SceneNodeAnimator.cpp
	sg/SceneLoader.cpp
	sg/SceneManager.cpp
	sg/SceneRenderer.cpp
	sg/SceneRendererGeneric.cpp
	sg/SceneLoader.cpp
    sg/Camera.cpp 
    sg/Light.cpp
    sg/Geometry.cpp
	sg/AssetsLibrary.cpp
	sg/GeometryLibrary.cpp
)

set (ScenegraphFiles_hpp
	sg/Forward.hpp 
	sg/Renderable.hpp
	sg/Pipeline.hpp
    sg/SceneNode.hpp      
    sg/Scene.hpp          
    sg/Camera.hpp         
    sg/Light.hpp          
    sg/Geometry.hpp       
    sg/TSolidGeometry.hpp 
    sg/Segment.hpp 
    sg/Box.hpp            
    sg/Ray.hpp            
    sg/Plane.hpp          
    sg/Intersect.hpp      
    sg/IntersectInfo.hpp  
    sg/Sphere.hpp
    sg/Triangle.hpp
	sg/SceneRenderer.hpp
    sg/SceneRendererGeneric.hpp
	sg/SceneLoader.hpp
	sg/SceneManager.hpp
	sg/SceneNodeAnimator.hpp
	sg/AssetsLibrary.hpp
	sg/GeometryLibrary.hpp
)
set (ScenegraphFiles ${ScenegraphFiles_hpp} ${ScenegraphFiles_cpp})

set (SystemFiles_cpp
    sys/Library.cpp 
    sys/Plugin.cpp 
    sys/PluginManager.cpp 
    sys/LibraryPrivatePosix.cpp sys/LibraryPrivateWin32.cpp
)
set (SystemFiles_hpp
	sys/Forward.hpp        
    sys/Library.hpp        
    sys/Plugin.hpp         
    sys/PluginLibrary.hpp  
    sys/PluginManager.hpp  
    sys/LibraryPrivate.hpp 
)
set (SystemFiles ${SystemFiles_hpp} ${SystemFiles_cpp})

set (UtilFiles_cpp 
	util/FrameCounter.cpp 
	util/MessageBox.cpp)

set (UtilFiles_hpp 
	util/FrameCounter.hpp 
	util/MessageBox.hpp)

set (UtilFiles ${UtilFiles_hpp} ${UtilFiles_cpp})

add_library (xe SHARED
    ${BaseFiles}
    ${AudioFiles}
    ${ComputeFiles}
    ${GraphicsFiles}
    ${InputFiles}
    ${ScenegraphFiles}
    ${SystemFiles}
    ${UtilFiles}
)


set_property (TARGET xe PROPERTY CXX_STANDARD 14)

source_group(\\			FILES ${BaseFiles})
source_group(sfx      	FILES ${AudioFiles})
source_group(cm			FILES ${ComputeFiles})
source_group(gfx   		FILES ${GraphicsFiles})
source_group(input      FILES ${InputFiles})
source_group(sg 		FILES ${ScenegraphFiles})
source_group(sys	    FILES ${SystemFiles})
source_group(util		FILES ${UtilFiles})

TARGET_LINK_LIBRARIES(xe ${UNIX_LIBRARIES} xmlpp ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES})

INSTALL (
	TARGETS xe 
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)

# INSTALL (FILES ExengConfig.cmake		DESTINATION lib/cmake/xe/)
INSTALL (FILES ${BaseFiles_hpp}			DESTINATION include/xe)
INSTALL (FILES ${AudioFiles_hpp}		DESTINATION include/xe/sfx)
INSTALL (FILES ${GraphicsFiles_hpp}		DESTINATION include/xe/gfx)
INSTALL (FILES ${InputFiles_hpp}		DESTINATION include/xe/input)
INSTALL (FILES ${ScenegraphFiles_hpp}	DESTINATION include/xe/sg)
INSTALL (FILES ${SystemFiles_hpp}		DESTINATION include/xe/sys)
INSTALL (FILES ${UtilFiles_hpp}			DESTINATION include/xe/util)
