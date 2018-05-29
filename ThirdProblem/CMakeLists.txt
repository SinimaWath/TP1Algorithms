cmake_minimum_required(VERSION 3.10)
project(ThirdProblem)

set(CMAKE_CXX_STANDARD 14)

add_executable(ThirdProblem main.cpp igraph.h iweightedgraph.h CMapGraph.cpp CMapGraph.h)