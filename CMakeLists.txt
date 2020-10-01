cmake_minimum_required(VERSION 2.6)
project(SNOWBALL)

include_directories(
	src
)

add_executable(demo
	src/demo/main.cpp
)

target_link_libraries(demo snowball)

# .h files included to show in VS
add_library(snowball SHARED
	src/snowball/core.cpp
	src/snowball/core.h
)