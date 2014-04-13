#-----------------------------------------------------------------
# CMAKE SETTINGS
cmake_minimum_required( VERSION 2.8.4 )

#-----------------------------------------------------------------
# PROJECT NAME
project( SDLInterface )

#-----------------------------------------------------------------
# Package Search
if ( NOT MSVC )
	find_package(PkgConfig)
	pkg_search_module( SDL2 REQUIRED sdl2 )
endif ( NOT MSVC )

set (PROJECT_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Util/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/include	# SDL headers
)	

set (PROJECT_SOURCE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLMain.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLWindow.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLEventLoop.h
)

set(PROJECT_SRCS 
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLMain.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLWindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLEventLoop.cpp
)

#-----------------------------------------------------------------
# COMPILER FLAGS 
if ( NOT MSVC ) # Not needed with vc++
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif( NOT MSVC )
 
#-----------------------------------------------------------------
# PULL IN DEPENDENCIES
if ( MSVC )
	set(SDL2_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/lib/x86/SDL2.lib)
	add_library(SDL2 SHARED IMPORTED)
	set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_LIBRARIES})
endif ( MSVC )

if (NOT TARGET Util)
	add_subdirectory(../Util "Util")
endif() 

#-----------------------------------------------------------------
# INCLUDES AND COMPILE
include_directories(${PROJECT_INCLUDE_DIR})

add_library(${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_HEADERS})

#-----------------------------------------------------------------
# SET THE PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


# Link project with SDL
target_link_libraries(${PROJECT_NAME} 
	${SDL2_LIBRARIES}
	Util 
)
