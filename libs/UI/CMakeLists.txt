add_library(
	ui STATIC
	ui.cpp
	ui.h
)

set_target_properties(ui PROPERTIES
	LINKER_LANGUAGE	CXX
	CXX_STANDARD 20
)

target_include_directories(
	ui PUBLIC
	${CMAKE_SOURCE_DIR}/libs/imgui
	${CMAKE_SOURCE_DIR}/libs/imgui/backends
)

target_link_libraries(
	ui PUBLIC
	imgui
)
