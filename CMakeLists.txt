cmake_minimum_required(VERSION 3.8)

project("better-than-nothing")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory("libs/glfw")
add_subdirectory("libs/glew")

file(GLOB ALL_SRCS
	"${PROJECT_SOURCE_DIR}/includes/*.h"
	"${PROJECT_SOURCE_DIR}/includes/Core/*.h"
	"${PROJECT_SOURCE_DIR}/includes/Events/*.h"
	"${PROJECT_SOURCE_DIR}/sources/*.cpp"
	"${PROJECT_SOURCE_DIR}/sources/Engine/Core/*.cpp"
	"${PROJECT_SOURCE_DIR}/sources/Engine/Core/GarbageCollector/*.cpp"
	"${PROJECT_SOURCE_DIR}/sources/Engine/Events/*.cpp"
)

include_directories(
	${PROJECT_SOURCE_DIR}/includes
	${PROJECT_SOURCE_DIR}/sources
)

add_executable(${PROJECT_NAME} ${ALL_SRCS})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

target_link_libraries(${PROJECT_NAME} glfw libglew_static)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)



