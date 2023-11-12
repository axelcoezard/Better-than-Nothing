cmake_minimum_required(VERSION 3.8)

project("better-than-nothing")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory("Engine/ThirdParty/glfw")
add_subdirectory("Engine/ThirdParty/vulkan")
add_subdirectory("Engine/ThirdParty/glm")
add_subdirectory("Engine/ThirdParty/entt")
add_subdirectory("Engine/ThirdParty/imgui")
add_subdirectory("Engine/ThirdParty/stb")

add_subdirectory("Engine/Modules/Core")
add_subdirectory("Engine/Modules/Runtime")





