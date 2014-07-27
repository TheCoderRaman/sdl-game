#-----------------------------------------------------------------
cmake_minimum_required( VERSION 2.8.4 )

include_directories( ${PROJECT_INCLUDE_DIR} )

add_executable( ${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_HEADERS} )

# SET THE PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)