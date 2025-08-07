CMAKE_MINIMUM_REQUIRED(VERSION 3.31)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project(
	gpu-grass
	VERSION 0.1.0
)

add_subdirectory(libs)
add_subdirectory(src)
