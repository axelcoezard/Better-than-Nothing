cmake_minimum_required(VERSION 3.8)

project("better-than-nothing")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory("Engine/libs/glfw")
add_subdirectory("Engine/libs/glew")
add_subdirectory("Engine/libs/glm")
add_subdirectory("Engine/libs/openal")
add_subdirectory("Engine/libs/libsndfile")
add_subdirectory("Engine/libs/entt")
add_subdirectory("Engine/libs/stb")

file(GLOB ALL_SRCS
	"${PROJECT_SOURCE_DIR}/Engine/sources/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Core/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Core/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Renderer/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Renderer/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Audio/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Audio/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Scene/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Scene/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Scene/Components/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Scene/Components/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Events/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/sources/Events/*.hpp"

	"${PROJECT_SOURCE_DIR}/Sandbox/*.cpp"
	"${PROJECT_SOURCE_DIR}/Sandbox/*.h"
)

include_directories(
	${PROJECT_SOURCE_DIR}/Engine/sources
	${PROJECT_SOURCE_DIR}/Sandbox
)

add_executable(${PROJECT_NAME} ${ALL_SRCS})

add_compile_definitions(ENGINE_EDITOR_MODE=false)
add_compile_definitions(ENGINE_VERBOSE_MODE=true)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

target_link_libraries(${PROJECT_NAME} glfw libglew_static openal sndfile stb)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/libs/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/libs/glew/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/libs/glm/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/libs/openal/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/libs/libsndfile/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/libs/entt/single_include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/libs/stb)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/sources)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox)



