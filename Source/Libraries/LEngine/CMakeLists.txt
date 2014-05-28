#-----------------------------------------------------------------
# CMAKE SETTINGS
cmake_minimum_required( VERSION 2.8.4 )

#-----------------------------------------------------------------
# PROJECT NAME
project( LEngine )

#-----------------------------------------------------------------
#DIRECTORIES
set (PROJECT_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Util/include
	${CMAKE_CURRENT_SOURCE_DIR}/../SDLInterface/include
)	

set (PROJECT_SOURCE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/LEngine.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LGameBase.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LUpdatable.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LUpdateLoop.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LRenderer.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LSprite.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LEvents.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LInput.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LError.h
)

SET(PROJECT_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/src/LEngine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LGameBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LUpdateLoop.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LRenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LSprite.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LInput.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LUpdatable.cpp
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
if (NOT TARGET SDLInterface)
	add_subdirectory(../SDLInterface "SDLInterface")
endif()

if (NOT TARGET Util)
	add_subdirectory(../Util)
endif()

#-----------------------------------------------------------------
# INCLUDES AND COMPILE
include_directories( ${PROJECT_INCLUDE_DIR} )

# ADD THE LIBRARY 
add_library( ${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_HEADERS} )

#-----------------------------------------------------------------
# SET THE PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

#-----------------------------------------------------------------
# LINKING
target_link_libraries( ${PROJECT_NAME} 
	SDLInterface
	Util )