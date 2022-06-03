cmake_minimum_required(VERSION 3.19)
project(n-puzzle)
set(CMAKE_CXX_STANDARD 14)


#set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2.5.1 COMPONENTS window graphics system)


# Add main.cpp file of project root directory as source file
set(SOURCE_FILES
        srcs/app/main.cpp
        srcs/models/Puzzle.cpp
        srcs/models/Puzzle.hpp
        srcs/algorithm/SearchAlgorithm.hpp
        srcs/algorithm/Heuristics.hpp
        srcs/utility/utility.hpp
        srcs/utility/print.cpp
        srcs/utility/solve.cpp
        srcs/utility/parse.cpp)

set(SOURCE_FILES_GAME
        srcs/graphics/main.cpp
        srcs/models/Puzzle.cpp
        srcs/models/Puzzle.hpp
        srcs/algorithm/SearchAlgorithm.hpp
        srcs/algorithm/Heuristics.hpp
        srcs/utility/utility.hpp
        srcs/utility/print.cpp
        srcs/utility/solve.cpp
        srcs/utility/parse.cpp)

set (SFML_LIBRARIES
        sfml-graphics
        sfml-window
        sfml-system)

set (SFML_DEPENDENCIES
        -lsfml-graphics
        -lsfml-window
        -lsfml-system)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(n-puzzle ${SOURCE_FILES})
add_executable(n-puzzle-game ${SOURCE_FILES_GAME})

target_compile_features(n-puzzle-game PUBLIC cxx_std_17)
target_compile_definitions(n-puzzle-game PRIVATE SFML_STATIC)

target_link_libraries(n-puzzle-game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
