cmake_minimum_required(VERSION 3.29)
project(BADTestTask)

set(HEADERS
        FileReader/ReaderFunctions.hpp
        ErrorCodeStrings/ErrorCodes.hpp
        BracedException/BracedException.hpp
        FileReader/ReaderFunctions.inl
        Vertex/Vertex.hpp
        Vertex/Vertex.inl
        Graph/Graph.hpp
        Graph/Graph.inl
)
set(SOURCE

        ErrorCodeStrings/ErrorCodes.cpp
        FileReader/ReaderFunctions.cpp
)
# Setting c++ standard of the project
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        # Adding project folders, so we can see if they don't exist
        ConsoleUI
        FileReader
        ErrorCodeStrings
        BracedException
        Vertex
        # Adding project headers
        ${HEADERS}
        # Adding project source files
        ${SOURCE}
        # Adding main
        main.cpp)
