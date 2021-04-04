project(static_member)

include_directories(${COMMON_SOURCE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CPP_SOURCES)

add_executable(test_${PROJECT_NAME} ${CPP_SOURCES})