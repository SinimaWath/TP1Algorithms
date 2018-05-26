cmake_minimum_required(VERSION 3.10)
project(Graph)

set(CMAKE_CXX_STANDARD 14)

add_executable(Graph main.cpp igraph.h CListGraph.cpp CListGraph.h CMatrixGraph.cpp CMatrixGraph.h CSetGraph.cpp CSetGraph.h CArcGraph.cpp CArcGraph.h)