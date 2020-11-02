cmake_minimum_required(VERSION 2.6)
project(SNOWBALL)

include_directories(
	src
)

if (MSVC)
 include_directories(${PROJECT_SOURCE_DIR}/contrib/msvc-windows-x86_64/include)
 link_directories( ${PROJECT_SOURCE_DIR}/contrib/msvc-windows-x86_64/lib)
endif()


add_executable(demo
	src/demo/main.cpp
)

add_definitions(-DSDL_MAIN_HANDLED)

add_library(rend
  src/rend/Exception.cpp
  src/rend/Context.cpp
  src/rend/Texture.cpp
  src/rend/RenderTexture.cpp
  src/rend/Shader.cpp
  src/rend/Buffer.cpp
  src/rend/Mesh.cpp
  src/rend/Util.cpp

  src/rend/Exception.h
  src/rend/Context.h
  src/rend/Texture.h
  src/rend/RenderTexture.h
  src/rend/Shader.h
  src/rend/Buffer.h
  src/rend/Mesh.h
  src/rend/Util.h
)
if(MSVC OR MINGW)
  target_link_libraries(rend glew32 opengl32)
else()
  target_link_libraries(rend GLEW GL)
endif()




# .h files included to show in VS
add_library(snowball 
	src/snowball/core.cpp
	src/snowball/entity.cpp
	src/snowball/component.cpp
    src/snowball/renderer.cpp
	src/snowball/transform.cpp
	src/snowball/screen.cpp

    src/snowball/core.h
    src/snowball/entity.h
	src/snowball/component.h
    src/snowball/renderer.h
	src/snowball/snowball.h
	src/snowball/transform.h
	src/snowball/screen.h
)

target_link_libraries(demo snowball)

target_link_libraries(demo SDL2)
target_link_libraries(snowball rend)






