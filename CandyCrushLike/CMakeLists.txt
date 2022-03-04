cmake_minimum_required(VERSION 3.14)
project(CandyCrushLike)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp components/Grille.cpp headers/Grille.h headers/Bonbon.h headers/Game.h components/Game.cpp headers/Item.h components/Item.cpp)
add_executable(CandyCrushLike ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(CandyCrushLike sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
file(COPY asset DESTINATION ${CMAKE_BINARY_DIR})
