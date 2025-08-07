add_executable(main main.cpp)

target_link_libraries(
	main PUBLIC
	ui
	glm
	glfw
	shader
)

file(
	COPY shaders
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
