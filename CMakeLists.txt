cmake_minimum_required(VERSION 3.8)

project("better-than-nothing")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB ALL_SRCS
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/*.h"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Engine/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Engine/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Handlers/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Handlers/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Scene/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Scene/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Layers/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Layers/*.cpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Events/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/Events/*.cpp"

	"${PROJECT_SOURCE_DIR}/Engine/Modules/Runtime/src/*.hpp"
	"${PROJECT_SOURCE_DIR}/Engine/Modules/Runtime/src/*.cpp"
)

add_subdirectory("Engine/ThirdParty/glfw")
add_subdirectory("Engine/ThirdParty/vulkan")
add_subdirectory("Engine/ThirdParty/glm")
#add_subdirectory("Engine/ThirdParty/openal")
add_subdirectory("Engine/ThirdParty/entt")
add_subdirectory("Engine/ThirdParty/imgui")
add_subdirectory("Engine/ThirdParty/stb")

include_directories(
	${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src
	${PROJECT_SOURCE_DIR}/Engine/Modules/Editor/src
	${PROJECT_SOURCE_DIR}/Engine/Modules/Runtime/src
)

add_executable(${PROJECT_NAME} ${ALL_SRCS})

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Engine/Modules/Core/src/pch.hpp)

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

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Modules/Core/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Modules/Editor/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Modules/Runtime/src)



