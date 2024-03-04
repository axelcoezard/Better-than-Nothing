cmake_minimum_required(VERSION 3.8)

project("imgui")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SOURCES
	"imgui.cpp"
	"imgui_draw.cpp"
	"imgui_demo.cpp"
	"imgui_tables.cpp"
	"imgui_widgets.cpp"
	"imgui_impl_glfw.cpp"
	"imgui_impl_vulkan.cpp"
	"include/imgui.h"
	"include/imconfig.h"
	"include/imgui_internal.h"
	"include/imgui_impl_glfw.h"
	"include/imgui_impl_vulkan.h"
	"include/imstb_rectpack.h"
	"include/imstb_textedit.h"
	"include/imstb_truetype.h"
)

include_directories(include)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include)

install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include)



