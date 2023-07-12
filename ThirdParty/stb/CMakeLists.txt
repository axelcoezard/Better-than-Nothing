cmake_minimum_required(VERSION 3.8)

project("stb")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_library(${PROJECT_NAME} SHARED
	"${PROJECT_SOURCE_DIR}/stb_image.cpp"
	"${PROJECT_SOURCE_DIR}/stb_image.h"
	"${PROJECT_SOURCE_DIR}/stb_image_resize.h"
	"${PROJECT_SOURCE_DIR}/stb_image_write.h"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER stb_image.h)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER stb_image_resize.h)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER stb_image_write.h)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
