cmake_minimum_required(VERSION 3.8)

project("better-than-nothing")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory("BetterThanNothing/libs/glfw")
add_subdirectory("BetterThanNothing/libs/vulkan")
add_subdirectory("BetterThanNothing/libs/glm")
#add_subdirectory("BetterThanNothing/libs/openal")
#add_subdirectory("BetterThanNothing/libs/libsndfile")
#add_subdirectory("BetterThanNothing/libs/stb")

file(GLOB ALL_SRCS
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/*.hpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Engine/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Engine/*.hpp"
	"${PROJECT_SOURCE_DIR}/Sandbox/*.cpp"
	"${PROJECT_SOURCE_DIR}/Sandbox/*.h"
)

include_directories(
	${PROJECT_SOURCE_DIR}/BetterThanNothing/sources
	${PROJECT_SOURCE_DIR}/Sandbox
)

add_executable(${PROJECT_NAME} ${ALL_SRCS})

add_compile_definitions(ENGINE_EDITOR_MODE=false)
add_compile_definitions(ENGINE_VERBOSE_MODE=true)

target_precompile_headers(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/pch.hpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -O2)

target_link_libraries(${PROJECT_NAME} glfw vulkan) #openal sndfile stb)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BetterThanNothing/libs/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BetterThanNothing/libs/vulkan)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BetterThanNothing/libs/glm/include)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BetterThanNothing/libs/openal/include)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BetterThanNothing/libs/libsndfile/include)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BetterThanNothing/libs/stb)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BetterThanNothing/sources)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox)



