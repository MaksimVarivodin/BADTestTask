//
// Created by Maksym on 20.12.2024.
//

#ifndef GRAPH_INL
#define GRAPH_INL

namespace graph {
    template<typename vType, size_t vCount>
    void Graph<vType, vCount>::sortByEdgeCount() {
        function<bool(const shared_ptr<Vertex<vType, vCount> > &,
                      const shared_ptr<Vertex<vType, vCount> > &)>
                compare =
                        [&](const shared_ptr<Vertex<vType, vCount> > &a,
                            const shared_ptr<Vertex<vType, vCount> > &b) {
                    return a->edges().size() > b->edges().size();
                };
        std::sort(vertices_.begin(), vertices_.end(), compare);
    }


    template<typename vType, size_t vCount>
    double Graph<vType, vCount>::keyGenerator(
        const std::shared_ptr<Vertex<vType, vCount> > &vertex) {
        return static_cast<double>(vertex->first() * 10000 + vertex->middle() * 100 + vertex->last());
    }


    template<typename vType, size_t vCount>
    string Graph<vType, vCount>::dfsHelper(const shared_ptr<Vertex<vType, vCount> > &vertex,
                                           unordered_set<double> visited,
                                           map<double, string> &visitedCache) {
        // Some random calculations to create unique key
        const double key = keyGenerator(vertex);
        if (!vertex)
            return "";
        if (visited.contains(key))
            return "";
        if (visitedCache.contains(key))
            return visitedCache[key];
        visited.insert(key);

        // Getting the current vertex puzzle part
        string innerTraversal = vertex->puzzlePart();
        if (!vertex->edges().empty()) {
            string longestNeighbor;

            // Iterating over all neighbors
            for (const auto &neighbor: vertex->edges()) {
                // Finding the longest path from the neighbor
                string vertexTempPath = dfsHelper(neighbor, visited, visitedCache);
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

    template<typename vType, size_t vCount>
    string Graph<vType, vCount>::dfs() {
        sortByEdgeCount();
        string longestCombination;
        map<double, string> globalVisited;
        // Итерируемся по всем вершинам графа
        for (const auto &vertex: vertices_) {
            const double key = keyGenerator(vertex);
            string newCombination;
            if (!globalVisited.contains(key))
                newCombination = dfsHelper(vertex, {}, globalVisited);

            if (newCombination.size() > longestCombination.size())
                longestCombination = std::move(newCombination);
        }

        return longestCombination;
    }

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
