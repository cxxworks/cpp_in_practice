project(constructors)

include_directories(${COMMON_SOURCE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CPP_SOURCES)

add_executable(test_constructors_no_optimalization ${CPP_SOURCES})
target_compile_options(test_constructors_no_optimalization PRIVATE "-fno-elide-constructors")

add_executable(test_constructors ${CPP_SOURCES})

# Notes:
# 1.关于编译器参数"-fno-elide-constructors":
#   The C++ standard allows an implementation to omit creating a temporary that is only used to initialize another object of the same type. 
#   Specifying this option disables that optimization, and forces G++ to call the copy constructor in all cases.