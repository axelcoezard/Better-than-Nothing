cmake_minimum_required(VERSION 3.8)

project("better-than-nothing")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory("ThirdParty/glfw")
add_subdirectory("ThirdParty/vulkan")
add_subdirectory("ThirdParty/glm")
add_subdirectory("ThirdParty/openal")
add_subdirectory("ThirdParty/entt")

file(GLOB ALL_SRCS
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/*.hpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Engine/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Engine/*.hpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Handlers/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Handlers/*.hpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Scene/*.cpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Scene/*.hpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Layers/*.hpp"
	"${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/Layers/*.cpp"
	"${PROJECT_SOURCE_DIR}/Sandbox/*.cpp"
	"${PROJECT_SOURCE_DIR}/Sandbox/*.h"
)

add_library(imgui SHARED
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/imgui.h
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/imgui.cpp
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/imconfig.h
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/imgui_internal.h
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/imgui_draw.cpp
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/imgui_demo.cpp
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/imgui_tables.cpp
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/imgui_widgets.cpp
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/backends/imgui_impl_glfw.h
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/backends/imgui_impl_glfw.cpp
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/backends/imgui_impl_vulkan.h
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui/backends/imgui_impl_vulkan.cpp
)

add_library(stb SHARED
	"${PROJECT_SOURCE_DIR}/ThirdParty/stb/stb_image.cpp"
	"${PROJECT_SOURCE_DIR}/ThirdParty/stb/stb_image.h"
	"${PROJECT_SOURCE_DIR}/ThirdParty/stb/stb_image_resize.h"
	"${PROJECT_SOURCE_DIR}/ThirdParty/stb/stb_image_write.h"
)

include_directories(
	${PROJECT_SOURCE_DIR}/BetterThanNothing/sources
	${PROJECT_SOURCE_DIR}/Sandbox
	${PROJECT_SOURCE_DIR}/ThirdParty/imgui
)

add_executable(${PROJECT_NAME} ${ALL_SRCS} ${IMGUI_SOURCES})

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/BetterThanNothing/sources/pch.hpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw vulkan stb openal imgui)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/vulkan)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/stb)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/tinyobjloader)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/openal/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/entt/single_include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/backends)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BetterThanNothing/sources)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox)



