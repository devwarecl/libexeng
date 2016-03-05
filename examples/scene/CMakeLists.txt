
set (scene_src scene.cpp fshader.hpp fshader.cpp vshader.hpp vshader.cpp SceneRenderer.hpp SceneRenderer.cpp AssetRenderer.hpp AssetRenderer.cpp)

source_group(\\ FILES ${scene_src})

add_executable(scene ${scene_src})

set_property(TARGET scene PROPERTY CXX_STANDARD 14)

target_link_libraries(scene xe)

install (
	TARGETS scene
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
