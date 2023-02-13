cmake_minimum_required(VERSION 3.24.2)
project(n-puzzle)
set(CMAKE_CXX_STANDARD 14)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES
        srcs/main.cpp
        srcs/graphics/Visualizer.hpp
        srcs/models/Puzzle.cpp
        srcs/models/Puzzle.hpp
        srcs/algorithm/SearchAlgorithm.hpp
        srcs/algorithm/Heuristics.hpp
        srcs/utility/utility.hpp
        srcs/utility/solve.cpp
        srcs/utility/parse.cpp)


include_directories(./srcs/resources/SFML-2.5.1/include/)
include_directories(./srcs/algorithm/)
include_directories(./srcs/graphics/)
include_directories(./srcs/resources/)
#set (SFML_LIBRARIES
#        libsfml-graphics.2.5.1.dylib
#        libsfml-window.2.5.1.dylib
#        libsfml-system.2.5.1.dylib)

set (SFML_DEPENDENCIES
        -lsfml-graphics
        -lsfml-window
        -lsfml-system)

link_directories(./srcs/resources/SFML-2.5.1/build/lib/)
link_directories(./srcs/resources/)
include_directories(./srcs/resources/SFML-2.5.1/include/)
include_directories(./srcs/resources/)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(n-puzzle  ${SOURCE_FILES})

target_link_libraries(n-puzzle ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_compile_features(n-puzzle PUBLIC cxx_std_17)
target_compile_definitions(n-puzzle PRIVATE SFML_STATIC)


