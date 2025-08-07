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
	${CMAKE_CURRENT_SOURCE_DIR}/imgui/
	${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/
)

target_link_libraries(
	imgui PUBLIC
	libglfw.so.3
	libGL.so
)




# _____ Glad loader _____
add_library(
	glad
	glad/src/glad.c
	glad/include/glad/glad.h
	glad/include/KHR/khrplatform.h
)

target_include_directories(
	glad PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

target_link_libraries(
	glad PUBLIC
	libglfw.so.3
	libGL.so
)

# _____ GLM _____
add_library(
	glm
	glm/glm/glm.hpp
)

set_target_properties(
	glm PROPERTIES
	LINKER_LANGUAGE CXX
)

target_include_directories(
	glm PUBLIC
	glm/glm
)

add_subdirectory(utils/UI)
add_subdirectory(utils/shader)
