add_library(
	imgui
	imgui/imgui.h
	imgui/imgui.cpp
	imgui/imgui_demo.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_tables.cpp
	imgui/imgui_widgets.cpp
	imgui/backends/imgui_impl_opengl3.h
	imgui/backends/imgui_impl_opengl3.cpp
	imgui/backends/imgui_impl_opengl3_loader.h
	imgui/backends/imgui_impl_glfw.h
	imgui/backends/imgui_impl_glfw.cpp
)

target_include_directories(
	imgui PUBLIC
	${CMAKE_SOURCE_DIR}/libs/imgui
	${CMAKE_SOURCE_DIR}/libs/imgui/backends
)

add_subdirectory(glad)
add_subdirectory(glm/glm)
add_subdirectory(UI)
add_subdirectory(shader)
