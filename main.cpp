#include <iostream>
#include <ranges>
#include "BracedException/BracedException.hpp"
#include "FileReader/ReaderFunctions.hpp"
#include "Graph/Graph.hpp"
#include "Vertex/Vertex.hpp"
BR_EXCEPT_
READER_
GRAPH_
#define VERTEX_COUNT 3
#define STRING_SIZE 6

int main(int argc, char *argv[]) {
    string inputFile = "source.txt";
    string outputFile = "output.txt";
    if (argc > 1)
        inputFile = argv[1];
    if (argc > 2)
        outputFile = argv[2];
    try {
        auto list = tryFunction(__FUNCTION__, readFileToList<int16_t, VERTEX_COUNT, STRING_SIZE>, inputFile);
        auto data = listToMap(list);
        Graph<int16_t, 3> graph = Graph<int16_t, 3>::createGraph(data);
        cout << graph::to_string(graph) << endl;
        auto dfs = graph.dfs();
        for (auto &df: dfs) {
            cout << graph::to_string(*df) << "->";
        }
    } catch (const BracedException &ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
