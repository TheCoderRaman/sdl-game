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
		${CMAKE_CURRENT_SOURCE_DIR}/../../../Box2D/
	)

set (PROJECT_SOURCE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/FCommon.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/FInternal.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/FWorld.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/FRigidBody.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/FShape.h
)

set(PROJECT_SRCS 
	${CMAKE_CURRENT_SOURCE_DIR}/src/FWorld.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/FRigidBody.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/FInternal.cpp
)


#-----------------------------------------------------------------
include(../../cmake/config.cmake)
include(../../cmake/library.cmake)

#-----------------------------------------------------------------
# Link project with Box2D
target_link_libraries(${PROJECT_NAME} 
	Util 
	Box2D
)

