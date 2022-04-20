cmake_minimum_required(VERSION 3.20)
project(EndGame)

set(SFML_DIR "D:/Libraries/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(EndGame main.cpp chessBoard.cpp piece.cpp)
target_link_libraries(EndGame sfml-graphics sfml-audio)
