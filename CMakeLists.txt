cmake_minimum_required(VERSION 3.20)
project(EndGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(EndGame main.cpp chessBoard.cpp piece.cpp stateAnalysis.cpp decisionTreeNode.cpp)
