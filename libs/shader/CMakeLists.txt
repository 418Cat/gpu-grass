add_library(
	shader
	shader.h
)

set_target_properties(
	shader PROPERTIES
	LINKER_LANGUAGE CXX
)

target_link_libraries(
	shader PUBLIC
	GL.so.3
)
