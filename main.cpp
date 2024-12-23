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
    bool showGraph = argc >= 3 && string(argv[2]) == "s";
    if (argc >= 2)
        inputFile = argv[1];


    try {
        auto list = tryFunction(__FUNCTION__, readFileToList<int16_t, VERTEX_COUNT, STRING_SIZE>, inputFile);

        cout << "1. Read data from file: {" << inputFile << "}." << endl;

        auto data = listToMap(list);

        cout << "2. Converted string list to map." << endl;

        Graph<int16_t, 3> graph = Graph<int16_t, 3>::createGraph(data);

        cout << "3. Created graph." << endl;

        if (showGraph) {
            cout << "Graph: \n";
            cout << "_____________\n\n";
            cout << graph::to_string(graph);
            cout << "_____________\n\n";
        }


        cout << "4. Starting DFS." << endl;

        auto dfs = graph.dfs();

        cout << "5. DFS finished." << endl;

        cout << "6. Longest puzzle:\n* Combination: \n" << dfs << endl;

        cout << "* Length: " << dfs.length() << endl;

        graph.puzzleCombinationIsValid(dfs);

        cout << "7. Puzzle combination is valid." << endl;
    } catch (const BracedException &ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
