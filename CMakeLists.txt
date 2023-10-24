cmake_minimum_required(VERSION 3.8)

project("better-than-nothing")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory("ThirdParty/glfw")
add_subdirectory("ThirdParty/vulkan")
add_subdirectory("ThirdParty/glm")
add_subdirectory("ThirdParty/stb")
#add_subdirectory("ThirdParty/tinyobjloader2")
#add_subdirectory("ThirdParty/openal")
#add_subdirectory("ThirdParty/libsndfile")

file(GLOB ALL_SRCS
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/*.hpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Engine/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Engine/*.hpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Handlers/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Handlers/*.hpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Scene/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Scene/*.hpp"
	"${PROJECT_SOURCE_DIR}/Sandbox/*.cpp"
	"${PROJECT_SOURCE_DIR}/Sandbox/*.h"
)

include_directories(
	${PROJECT_SOURCE_DIR}/BetterThanNothing/sources
	${PROJECT_SOURCE_DIR}/Sandbox
)

add_executable(${PROJECT_NAME} ${ALL_SRCS})

target_precompile_headers(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/pch.hpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

target_link_libraries(${PROJECT_NAME} glfw vulkan stb) #openal sndfile)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/vulkan)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/stb)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/tinyobjloader2)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/openal/include)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/libsndfile/include)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BetterThanNothing/sources)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox)



