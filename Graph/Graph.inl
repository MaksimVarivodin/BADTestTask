//
// Created by Maksym on 20.12.2024.
//

#ifndef GRAPH_INL
#define GRAPH_INL

namespace graph {
    /**
     * @brief Sorts vertices in the graph by the number of edges they have.
     *
     * This function uses a lambda function as the comparison criterion for the std::sort function.
     * The vertices are sorted in descending order based on the number of edges they have.
     */
    template<typename vType, size_t vCount>
    void Graph<vType, vCount>::sortByEdgeCount() {
        function<bool(const shared_ptr<Vertex<vType, vCount> > &, const shared_ptr<Vertex<vType, vCount> > &)>
                compare = [&](const shared_ptr<Vertex<vType, vCount> > &a,
                              const shared_ptr<Vertex<vType, vCount> > &b) {
                    return a->edges().size() > b->edges().size();
                };
        std::sort(vertices_.begin(), vertices_.end(), compare);
    }

    /**
     * @brief Generates a unique key for a given vertex.
     *
     * This function calculates a unique key based on the first, middle, and last parts of the vertex.
     * The key is a double value that is obtained by multiplying the first part by 10000,
     * the middle part by 100, and adding the last part.
     *
     * @param vertex The vertex for which the key needs to be generated.
     * @return The unique key for the given vertex.
     */
    template<typename vType, size_t vCount>
    double Graph<vType, vCount>::keyGenerator(const std::shared_ptr<Vertex<vType, vCount> > &vertex) {
        return static_cast<double>(vertex->first() * 10000 + vertex->middle() * 100 + vertex->last());
    }

    /**
     * @brief Helper function for the depth-first search (DFS) algorithm.
     *
     * This function recursively explores the graph starting from a given vertex,
     * keeping track of visited vertices and the paths taken to reach them.
     * It uses a unique key for each vertex to avoid revisiting vertices and to cache the paths.
     *
     * @param vertex The vertex from which the DFS traversal starts.
     * @param visited Set to keep track of visited vertices.
     * @param visitedCache Map to cache the paths taken to reach visited vertices.
     * @return The longest path found from the given vertex.
     */
    template<typename vType, size_t vCount>
    string Graph<vType, vCount>::dfsHelper(const shared_ptr<Vertex<vType, vCount> > &vertex,
                                           unordered_set<double> visited,
                                           map<double, string> &visitedCache) {
        // Some random calculations to create unique key
        const double key = keyGenerator(vertex);

        // The vertex mustn't be null
        if (!vertex)
            return "";

        // The vertex mustn't be visited
        if (visited.contains(key))
            return "";

        // If we have cached result, we return it
        if (visitedCache.contains(key))
            return visitedCache[key];

        // Adding the vertex to the visited set
        visited.insert(key);

        // Getting the current vertex puzzle part
        string innerTraversal = vertex->puzzlePart();

        // If the vertex has neighbors
        if (!vertex->edges().empty()) {
            string longestNeighbor;

            // Iterating over all neighbors
            for (const auto &neighbor: vertex->edges()) {
                // Finding the longest path from the neighbor
                string vertexTempPath = dfsHelper(neighbor, visited, visitedCache);

                // Setting the longest path from the neighbor
                if (vertexTempPath.length() > longestNeighbor.length())
                    longestNeighbor = vertexTempPath;
            }

            // if all neighbors are visited, we need to add the last part of the puzzle
            if (longestNeighbor.empty())
                longestNeighbor += vertex->puzzlePartLast();

            // Saving longest path from the current vertex
            innerTraversal += longestNeighbor;
        }

        // Caching  the current vertex path
        if (!visitedCache.contains(key))
            visitedCache[key] = innerTraversal;
        return innerTraversal;
    }

    /**
     * @brief Performs a depth-first search (DFS) traversal of the graph.
     *
     * This function starts the DFS traversal from each vertex in the graph,
     * and keeps track of the longest path found.
     * It uses the dfsHelper function to perform the actual DFS traversal.
     *
     * @return The longest path found in the graph.
     */
    template<typename vType, size_t vCount>
    string Graph<vType, vCount>::dfs() {
        // Sorting vertices by the number of edges
        sortByEdgeCount();

        // Current longest path
        string longestCombination;

        // Map to store cached vertices
        map<double, string> globalVisited;

        // Iterating over all vertices in the graph
        for (const auto &vertex: vertices_) {
            // Calculating unique key for the vertex
            const double key = keyGenerator(vertex);

            // If the vertex is not visited, we start DFS from it
            string newCombination;
            if (!globalVisited.contains(key))
                newCombination = dfsHelper(vertex, {}, globalVisited);

            if (newCombination.size() > longestCombination.size())
                longestCombination = std::move(newCombination);
        }

        return longestCombination;
    }

    /**
     * @brief Creates a graph from a given map of vertex data.
     *
     * This function takes a map of vertex data as input and creates a graph by
     * creating vertices and adding edges between them.
     * It also checks for any missing edges and adds them if necessary.
     *
     * @param vData The map of vertex data used to create the graph.
     * @return The created graph.
     */
    template<typename vType, size_t vCount>
    Graph<vType, vCount> Graph<vType, vCount>::createGraph(
        const map<vType, vector<VertexNumbers<vType, vCount> > > &vData) {
        // Map to save vertices for quick access by key
        map<vType, list<shared_ptr<Vertex<vType, vCount> > > > vertexMap;
        // Filling the vertexMap with lists of Vertices(Vertex class)
        for (const auto &[key, vDataList]: vData)
            for (const auto &vDataListElement: vDataList)
                vertexMap[key].push_back(make_shared<Vertex<vType, vCount> >(vDataListElement));
        // Adding edges that don't have any neighbors
        auto vertexIterator(vertexMap.begin());
        for (; vertexIterator->first < 0; ++vertexIterator) {
            for (const auto &vertex: vertexIterator->second)
                if (vertexMap.contains(vertex->first()))
                    for (auto &addEdgeElement: vertexMap[vertex->first()])
                        if (addEdgeElement->first() != vertex->first())
                            addEdgeElement->addEdge(vertex);
        }
        // Adding to edges to vertices that have at least 1 edge
        for (; vertexIterator != vertexMap.end(); ++vertexIterator)
            for (const auto &vertex: vertexIterator->second)
                if (vertexMap.contains(vertex->first()))
                    for (auto &addEdgeElement: vertexMap[vertex->first()])
                        if (addEdgeElement->first() != vertex->first())
                            addEdgeElement->addEdge(vertex);
        // Copying map to vector
        vector<shared_ptr<Vertex<vType, vCount> > > graph;
        for (const auto &[key, vertex]: vertexMap)
            for (const auto &vertexElement: vertex)
                graph.push_back(vertexElement);

        return Graph(graph);
    }

    /**
     * @brief Validates the puzzle combination.
     *
     * This function checks if the given puzzle combination is valid or not.
     * It throws an exception if the combination is invalid, indicating the invalid part.
     *
     * @param combination The puzzle combination to be validated.
     */
    template<typename vType, size_t vCount>
    void Graph<vType, vCount>::puzzleCombinationIsValid(const string &combination) const {
        size_t i = 0;

        // Check all connected vertices
        for (; i < combination.length() - 4; i += 4) {
            if (findVertex(combination.substr(i, 6)) == -1)
                throw exceptionInFunction(
                    __FUNCTION__,
                    ERROR_MESSAGES[PUZZLE_INVALID], combination.substr(i, 6), i, i + 6);
        }
        i = combination.length() - 6;
        // Check the last vertex
        if (findVertex(combination.substr(i, 6)) == -1)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[PUZZLE_INVALID], combination.substr(i, 6), i, i + 6);
    }

    /**
     * @brief Converts a graph to a string representation.
     *
     * This function converts a graph to a string representation,
     * displaying the vertices and their edges in a readable format.
     *
     * @param vertex The graph to be converted to a string.
     * @return The string representation of the graph.
     */
    template<typename T, size_t C>
    string to_string(const Graph<T, C> &vertex) {
        string result;
        for (auto &v: vertex.vertices_) {
            result += "[" + graph::to_string(*v) + "]:\n";
            for (auto &e: v->edges()) {
                result += "  ->" + to_string(*e) + "\n";
            }
        }
        return result;
    }

    /**
     * @brief Finds a vertex in the graph based on its string representation.
     *
     * This function searches for a vertex in the graph based on its string representation.
     * It iterates over all vertices in the graph and compares their string representations.
     *
     * @param vertex The string representation of the vertex to be found.
     * @return The index of the vertex in the graph if found, or -1 if not found.
     */
    template<typename vType, size_t vCount>
    signed long long Graph<vType, vCount>::findVertex(const string &vertex) const {
        signed long long index = 0;

        for (; index < vertices_.size(); ++index)
            if (!to_string(*(vertices_[index])).compare(vertex))
                return index;
        return -1;
    }
}
#endif //GRAPH_INL
