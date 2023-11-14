cmake_minimum_required(VERSION 3.8)

project("Core")

set(CMAKE_CXX_STANDARD 20)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB SOURCES
	"src/*.cpp"
	"src/*.hpp"
	"src/*.h"
	"src/Ressources/*.cpp"
	"src/Ressources/*.hpp"
	"src/Renderer/*.cpp"
	"src/Renderer/*.hpp"
	"src/Handlers/*.cpp"
	"src/Handlers/*.hpp"
	"src/Scene/*.cpp"
	"src/Scene/*.hpp"
	"src/Layers/*.hpp"
	"src/Layers/*.cpp"
	"src/Events/*.hpp"
	"src/Events/*.cpp"
)

include_directories(src)

add_library(${PROJECT_NAME} ${SOURCES})

target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../pch.hpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw vulkan stb imgui)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ThirdParty/glfw/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ThirdParty/vulkan)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ThirdParty/glm/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ThirdParty/stb/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ThirdParty/tinyobjloader)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ThirdParty/entt/single_include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ThirdParty/imgui/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include)
