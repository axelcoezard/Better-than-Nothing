cmake_minimum_required(VERSION 3.8)

project("stb")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SOURCES
	"stb_image.cpp"
	"include/stb_image.h"
	"include/stb_image_resize.h"
	"include/stb_image_write.h"
)

include_directories(include)

add_library(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include)



