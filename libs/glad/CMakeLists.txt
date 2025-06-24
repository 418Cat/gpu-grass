add_library(
	glad
	glad.c
	glad.h
)


target_link_libraries(
	glad PRIVATE
	libGL.so
)

set_target_properties(
	glad PROPERTIES
	LINKER_LANGUAGE CXX
)

target_include_directories(
	glad PUBLIC
	${CMAKE_SOURCE_DIR}/libs/glad/
)
