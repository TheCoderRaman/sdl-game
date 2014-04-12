# Minimum cmake version (required)
cmake_minimum_required( VERSION 2.8.4 )

# Project name
project( SDLInterface )

# Find SDL2
#find_package(PkgConfig)
#pkg_search_module( SDL2 REQUIRED sdl2 )


set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (PROJECT_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include	# SDL headers
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Util/include
)	

set(PROJECT_SRCS 
	${PROJECT_SOURCE_DIR}/SDLMain.cpp
	${PROJECT_SOURCE_DIR}/SDLWindow.cpp
	${PROJECT_SOURCE_DIR}/SDLEventLoop.cpp
)

# Set the compiler flags (specifically the c++11 one)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(${PROJECT_NAME} ${PROJECT_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_library(SDL2 SHARED IMPORTED)
set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_LIBRARIES})

# Link project with SDL
target_link_libraries(${PROJECT_NAME} 
	${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x86/SDL2.lib
	${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x86/SDL2main.lib
)

