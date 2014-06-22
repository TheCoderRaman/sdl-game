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
	${CMAKE_CURRENT_SOURCE_DIR}/include/map_helpers.h
)

SET(PROJECT_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/src/debug.cpp
)

#-----------------------------------------------------------------
include(../../cmake/config.cmake)
include(../../cmake/library.cmake)
