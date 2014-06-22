#-----------------------------------------------------------------
# CMAKE SETTINGS
cmake_minimum_required( VERSION 2.8.4 )

#-----------------------------------------------------------------
# PROJECT NAME
project( Ffiseg )

#-----------------------------------------------------------------
# Set the include directories
set (PROJECT_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Util/include
)	

# Set the include directories for SDL
set (PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/../../../Box2D/Box2D/
		${CMAKE_CURRENT_SOURCE_DIR}/../../../Box2D/
	)

set (PROJECT_SOURCE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/FCommon.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/FWorld.h
)

set(PROJECT_SRCS 
	${CMAKE_CURRENT_SOURCE_DIR}/src/FWorld.cpp
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
# PULL IN DEPENDENCIES

if (NOT TARGET Util)
	add_subdirectory(../Util "Util")
endif()

#-----------------------------------------------------------------
# INCLUDES AND COMPILE
include_directories(${PROJECT_INCLUDE_DIR})


add_library(${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_HEADERS})

add_dependencies(${PROJECT_NAME} Box2D)

#-----------------------------------------------------------------
# SET THE PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


# Link project with Box2D
target_link_libraries(${PROJECT_NAME} 
	Util 
	Box2D
)

