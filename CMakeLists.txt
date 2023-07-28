cmake_minimum_required(VERSION 3.0.0)
project(game-engine VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(include)

add_library(game-engine STATIC 
	src/game_engine_application.cpp 
	src/object.cpp 
	src/json_internal.cpp 
)

ADD_EXECUTABLE(test-exe test/test_app.cpp) 
TARGET_LINK_LIBRARIES(test-exe game-engine)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
