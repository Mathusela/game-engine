cmake_minimum_required(VERSION 3.0.0)
project(game-engine VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(include)

link_directories(lib)
link_libraries(glfw3 opengl32 gdi32)

add_library(game-engine STATIC 
	src/game_engine_application.cpp 
	src/object.cpp 
	src/json.cpp
	src/render_layer.cpp
	src/extern/glad.c
)

add_executable(test-exe test/test_app.cpp) 
target_link_libraries(test-exe game-engine)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
