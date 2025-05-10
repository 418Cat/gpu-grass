add_executable(main main.cpp)

target_link_libraries(
	main PUBLIC
	glm
	GL.so
	glfw

	ui
	imgui
	shader
)

target_include_directories(
	main PUBLIC
	${CMAKE_SOURCE_DIR}/libs/glm/glm
	${CMAKE_SOURCE_DIR}/libs/UI
	${CMAKE_SOURCE_DIR}/libs/shader
)

file(
	COPY shaders
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
