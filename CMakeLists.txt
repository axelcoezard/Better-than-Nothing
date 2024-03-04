# ==================================================================================================
# Global configuration
# ==================================================================================================
cmake_minimum_required(VERSION 3.8)

project("better-than-nothing")

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# ==================================================================================================
# Dependencies
# ==================================================================================================
add_subdirectory("Better-than-Nothing/ThirdParty/glfw")
add_subdirectory("Better-than-Nothing/ThirdParty/glm")
add_subdirectory("Better-than-Nothing/ThirdParty/vulkan")
add_subdirectory("Better-than-Nothing/ThirdParty/entt")
add_subdirectory("Better-than-Nothing/ThirdParty/imgui")
add_subdirectory("Better-than-Nothing/ThirdParty/stb")
add_subdirectory("Better-than-Nothing/ThirdParty/inih")
add_subdirectory("Better-than-Nothing/ThirdParty/glslang")
add_subdirectory("Better-than-Nothing/ThirdParty/spirv_cross")

# ==================================================================================================
# Modules
# ==================================================================================================
add_subdirectory("Better-than-Nothing/Modules/Core")
add_subdirectory("Better-than-Nothing/Modules/Runtime")




