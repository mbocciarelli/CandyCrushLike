cmake_minimum_required(VERSION 3.14)
project(CandyCrushLike)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp headers/main.h headers/candy.h components/candy.cpp components/test.cpp headers/test.h components/sfml_test.cpp headers/sfml_test.h components/Item.cpp headers/Item.h components/Grille.cpp headers/Grille.h components/sfml_object.cpp headers/sfml_object.h components/mouse_button.cpp headers/mouse_button.h components/Click.cpp headers/Click.h)
add_executable(CandyCrushLike ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(CandyCrushLike sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
file(COPY asset DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ImGUI DESTINATION ${CMAKE_BINARY_DIR})
