cmake_minimum_required(VERSION 3.17)
project(CostConstrainedShortestPath)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CostConstrainedShortestPath
        MinHeap.h
        bfs.cpp
        cpath.cpp
        CPath.h
        demo.cpp
        demo2.cpp
        dfs.cpp
        display.cpp
        g.h
        Graph.h
        topo.cpp
        minheap.cpp
        )
