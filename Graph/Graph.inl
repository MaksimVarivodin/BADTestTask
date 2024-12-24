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
                    return a->edges().size() < b->edges().size();
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
     * @brief Helper function for depth-first search (DFS) traversal.
     *
     * This function performs a DFS traversal starting from the given vertex.
     * It keeps track of visited vertices using a set and constructs the longest path
     * by recursively visiting neighboring vertices.
     *
     * @param vertex The starting vertex for the DFS traversal.
     * @param visited A set to keep track of visited vertices.
     * @return The longest path found from the starting vertex.
     */
    template<typename vType, size_t vCount>
    string Graph<vType, vCount>::dfsHelper(const shared_ptr<Vertex<vType, vCount> > &vertex,
                                           unordered_set<double> &visited) {
        // Generate a unique key for the current vertex
        double vertexKey = keyGenerator(vertex);

        // If the vertex is null, return an empty string
        if (!vertex)
            return {};

        // If the vertex has already been visited, return an empty string
        if (visited.contains(vertexKey))
            return {};

        // Mark the vertex as visited
        visited.insert(vertexKey);

        // If the vertex has no edges, return its puzzle part
        if (vertex->edges().empty())
            return vertex->puzzlePart();

        // Initialize a string to store the maximum path
        string maxPath;

        // Iterate over all neighboring vertices
        for (const auto &neighbor: vertex->edges()) {
            // Recursively find the longest path from the neighbor
            string neighborPath = dfsHelper(neighbor, visited);

            // Update the maximum path if the neighbor's path is longer
            if (neighborPath.length() > maxPath.length())
                maxPath = std::move(neighborPath);
        }

        // If no path was found, use the vertex's last puzzle part
        if (maxPath.empty())
            maxPath = vertex->puzzlePartLast();

        // Return the concatenated path
        return vertex->puzzlePart() + maxPath;
    }

    /**
     * @brief Performs a depth-first search (DFS) on the graph.
     *
     * This function sorts the vertices by the number of edges and then
     * iterates over each vertex to find the longest path using DFS.
     *
     * @return The longest path found in the graph.
     */
    template<typename vType, size_t vCount>
    string Graph<vType, vCount>::dfs() {
        // Sort vertices by the number of edges
        sortByEdgeCount();

        // Initialize a string to store the longest combination
        string longestCombination;

        // Iterate over all vertices in the graph
        for (const auto &vertex: vertices_) {
            // Create a set to track visited vertices for the current vertex
            unordered_set<double> oneVertexVisited;

            // Perform DFS from the current vertex
            string newCombination = dfsHelper(vertex, oneVertexVisited);

            // Update the longest combination if the new combination is longer
            if (newCombination.size() > longestCombination.size())
                longestCombination = std::move(newCombination);
        }

        // Return the longest combination found
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
