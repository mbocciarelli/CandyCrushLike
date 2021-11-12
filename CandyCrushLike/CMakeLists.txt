cmake_minimum_required(VERSION 3.14)
project(HelloSFML)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp headers/main.h headers/candy.h components/candy.cpp components/test.cpp headers/test.h components/sfml_test.cpp headers/sfml_test.h components/Item.cpp headers/Item.h components/Grille.cpp headers/Grille.h)
add_executable(HelloSFML ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
