cmake_minimum_required(VERSION 3.8)

project("better-than-nothing")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB ALL_SRCS
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/*.h"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Engine/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Engine/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Handlers/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Handlers/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Scene/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Scene/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Layers/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Layers/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Events/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/Events/*.cpp"

	"${PROJECT_SOURCE_DIR}/Engine/Source/Runtime/sources/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Source/Runtime/sources/*.cpp"
)

add_subdirectory("Engine/ThirdParty/glfw")
add_subdirectory("Engine/ThirdParty/vulkan")
add_subdirectory("Engine/ThirdParty/glm")
#add_subdirectory("Engine/ThirdParty/openal")
add_subdirectory("Engine/ThirdParty/entt")
add_subdirectory("Engine/ThirdParty/imgui")
add_subdirectory("Engine/ThirdParty/stb")

include_directories(
	${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources
	${PROJECT_SOURCE_DIR}/Engine/Source/Editor/sources
	${PROJECT_SOURCE_DIR}/Engine/Source/Runtime/sources
)

add_executable(${PROJECT_NAME} ${ALL_SRCS})

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Engine/Source/Core/sources/pch.hpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw vulkan stb openal imgui)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/vulkan)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/glm/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/stb/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/tinyobjloader)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/openal/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/entt/single_include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/imgui/include)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Source/Core/sources)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Source/Editor/sources)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Source/Runtime/sources)



