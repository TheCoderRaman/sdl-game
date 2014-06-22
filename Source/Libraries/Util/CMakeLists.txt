#-----------------------------------------------------------------
# CMAKE SETTINGS
cmake_minimum_required( VERSION 2.8.4 )

#-----------------------------------------------------------------
# PROJECT NAME
project( Util )

#-----------------------------------------------------------------
#DIRECTORIES
set (PROJECT_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/include
)	

set (PROJECT_SOURCE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/debug.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/types.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/math_types.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/map_helpers.h
)

SET(PROJECT_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/src/debug.cpp
)

#-----------------------------------------------------------------
# COMPILER FLAGS 
if ( NOT MSVC ) # Not needed with vc++
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# flags for release and debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_BUILD")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE_BUILD")

# flags for windows builds
if ( MSVC )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWINDOWS_BUILD")
else ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNIX_BUILD")
endif()

#-----------------------------------------------------------------
# INCLUDES AND COMPILE
include_directories( ${PROJECT_INCLUDE_DIR} )

# ADD THE LIBRARY 
add_library( ${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_HEADERS} )

#-----------------------------------------------------------------
# SET THE PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
