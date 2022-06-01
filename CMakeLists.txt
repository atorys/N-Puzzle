cmake_minimum_required(VERSION 3.13)
project(n-puzzle)
set(CMAKE_CXX_STANDARD 14)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES srcs/app/main.cpp
        srcs/models/Puzzle.cpp
        srcs/models/Puzzle.hpp
        srcs/algorithm/AStar.cpp
        srcs/algorithm/AStar.hpp
        srcs/algorithm/Strategy.hpp
        srcs/utility/utility.hpp
        srcs/utility/print.cpp
        srcs/utility/solve.cpp
        srcs/utility/parse.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(n-puzzle ${SOURCE_FILES})
