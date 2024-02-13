cmake_minimum_required(VERSION 3.8)

project("spirv_cross")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SOURCES
	"spirv_cross/spirv_cfg.cpp"
	"spirv_cross/spirv_cpp.cpp"
	"spirv_cross/spirv_cross_c.cpp"
	"spirv_cross/spirv_cross_parsed_ir.cpp"
	"spirv_cross/spirv_cross_util.cpp"
	"spirv_cross/spirv_cross.cpp"
	"spirv_cross/spirv_glsl.cpp"
	"spirv_cross/spirv_parser.cpp"
	"spirv_cross/spirv_reflect.cpp"
)

include_directories(spirv_cross)

add_library(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include)



