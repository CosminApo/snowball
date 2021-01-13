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
  target_link_libraries(rend glew32 opengl32 OpenAL32)
else()
  target_link_libraries(rend GLEW GL)
endif()




# .h files included to show in VS
add_library(snowball 
	src/snowball/Core.cpp
	src/snowball/Entity.cpp
	src/snowball/Component.cpp
  src/snowball/Renderer.cpp
	src/snowball/Transform.cpp
	src/snowball/Screen.cpp
	src/snowball/Resource.cpp
	src/snowball/ResourceManager.cpp
	src/snowball/Sound.cpp
  src/snowball/SoundSource.cpp
	src/snowball/Texture.cpp
	src/snowball/Keyboard.cpp
	src/snowball/Exception.cpp
  src/snowball/Camera.cpp
  src/snowball/Model.cpp
  src/snowball/Shader.cpp
  src/snowball/Player.cpp
  src/snowball/RenderTexture.cpp
  src/snowball/UIElement.cpp
  src/snowball/Mouse.cpp
    src/snowball/Collider.cpp

  src/snowball/Core.h
  src/snowball/Entity.h
	src/snowball/Component.h
  src/snowball/Renderer.h
	src/snowball/Snowball.h
	src/snowball/Transform.h
	src/snowball/Screen.h
	src/snowball/Resource.h
	src/snowball/ResourceManager.h
	src/snowball/Sound.h
	src/snowball/Texture.h
  src/snowball/SoundSource.h
  src/snowball/Camera.h
	src/snowball/Keyboard.h
	src/snowball/Exception.h
  src/snowball/Model.h
  src/snowball/Shader.h
  src/snowball/Player.h
  src/snowball/RenderTexture.h
  src/snowball/UIElement.h
  src/snowball/Mouse.h
  src/snowball/Collider.h


)

target_link_libraries(demo snowball)

target_link_libraries(demo SDL2)
target_link_libraries(snowball rend)
