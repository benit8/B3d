##
## B3d tests, 2019
## CMakeLists.txt
##

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
cmake_policy(SET CMP0076 NEW)

project(B3d_test VERSION 0.1.0 LANGUAGES CXX)
add_executable(test)
add_subdirectory(extern/B3d)

target_compile_features(test
PRIVATE
	cxx_std_17
)

target_compile_options(test
PRIVATE
	-W -Wall -Wextra
	-g3
)

# target_include_directories(test
# PRIVATE
# 	.
# )

target_sources(test
PRIVATE
	Main.cpp
)

target_link_libraries(test
PUBLIC
	B3d
)