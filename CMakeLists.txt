cmake_minimum_required(VERSION 2.6)
project(SNOWBALL)

include_directories(
	src
	${CMAKE_SOURCE_DIR}/contrib/SDL2-2.0.12/include
)

if (MSVC)
 include_directories(${PROJECT_SOURCE_DIR}/contrib/msvc-windows-x86_64/include)
 link_directories( ${PROJECT_SOURCE_DIR}/contrib/msvc-windows-x86_64/lib)
endif()


link_directories(${CMAKE_SOURCE_DIR}/contrib/SDL2-2.0.12/lib/x64)

add_executable(demo WIN32
	src/demo/main.cpp
)



add_library(rend
  src/rend/Exception.cpp
  src/rend/Context.cpp
  src/rend/Texture.cpp
  src/rend/RenderTexture.cpp
  src/rend/Shader.cpp
  src/rend/Buffer.cpp
  src/rend/Mesh.cpp
  src/rend/Util.cpp
)
if(MSVC OR MINGW)
  target_link_libraries(rend glew32 opengl32)
else()
  target_link_libraries(rend GLEW GL)
endif()


target_link_libraries(demo snowball)

target_link_libraries(demo SDL2 SDL2Main)

# .h files included to show in VS
add_library(snowball 
	src/snowball/core.cpp
	src/snowball/core.h
)

target_link_libraries(snowball rend)






