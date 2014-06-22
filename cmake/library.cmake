#-----------------------------------------------------------------
cmake_minimum_required( VERSION 2.8.4 )

#-----------------------------------------------------------------
# COMPILE SETUP

include_directories( ${PROJECT_INCLUDE_DIR} )

# ADD THE LIBRARY 
add_library( ${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_HEADERS} )

# SET THE PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)