//
// Created by Maksym on 20.12.2024.
//

#ifndef GRAPH_INL
#define GRAPH_INL

namespace graph {
    template<typename vType, size_t vCount>
    void Graph<vType, vCount>::sortByEdgeCount() {
        function<bool(const shared_ptr<Vertex<vType, vCount> > &,
                      const shared_ptr<Vertex<vType, vCount> > &)> compare =
                [&](const shared_ptr<Vertex<vType, vCount> > &a,
                    const shared_ptr<Vertex<vType, vCount> > &b) {
            return a->edges().size() > b->edges().size();
        };
        std::sort(vertices_.begin(), vertices_.end(), compare);
    }

    //TODO: Implement DFS
    template<typename vType, size_t vCount>
    double Graph<vType, vCount>::keyGenerator(
        const std::shared_ptr<Vertex<vType, vCount> > &vertex) {
        return static_cast<double>(vertex->first() * 10000 + vertex->middle() * 100 + vertex->last());
    }


    template<typename vType, size_t vCount>
    list<shared_ptr<Vertex<vType, vCount> > > Graph<vType, vCount>::dfs() {
        function<void
            (const shared_ptr<Vertex<vType, vCount> > &,
             list<shared_ptr<Vertex<vType, vCount> > > &,
             unordered_set<double>,
             unordered_set<double> &)> dfsHelper =
                [&](const shared_ptr<Vertex<vType, vCount> > &vertex,
                    list<shared_ptr<Vertex<vType, vCount> > > &traversal,
                    unordered_set<double> visited,
                    unordered_set<double> &globalVisited) {
            // Some random calculations to create unique key
            const double key = keyGenerator(vertex);
            if (!vertex || visited.contains(key)) {
                return;
            }

            visited.insert(key);
            if (!globalVisited.contains(key))
                globalVisited.insert(key);
            traversal.push_back(vertex);
            auto traversalCopy = traversal;
            auto visitedCopy = visited;
            // Рекурсивно обходим соседей
            for (const auto &neighbor: vertex->edges()) {
                dfsHelper(neighbor, traversalCopy, visited, globalVisited);
                if (traversalCopy.size() > traversal.size()) {
                    traversal = traversalCopy;
                }
            }
        };
        sortByEdgeCount();

        list<shared_ptr<Vertex<vType, vCount> > > longestCombination;
        unordered_set<double> globalVisited;

        // Итерируемся по всем вершинам графа
        for (const auto &vertex: vertices_) {
            if (const double key = keyGenerator(vertex); !globalVisited.contains(key)) {
                list<shared_ptr<Vertex<vType, vCount> > > newCombination;
                dfsHelper(vertex, newCombination, {}, globalVisited);
                if (newCombination.size() > longestCombination.size()) {
                    longestCombination = newCombination;
                }
            }
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
    string longestPathToString(const list<shared_ptr<Vertex<vType, vCount> > > &p) {
        string result;
        int count = 0;
        auto it = p.begin();
        for (; count < p.size() - 1; ++it, ++count) {
            result += (((*it)->first() < 10) ? "0" : "") + std::to_string((*it)->first());
            result += (((*it)->middle() < 10) ? "0" : "") + std::to_string((*it)->middle());
        }
        result += (((*it)->first() < 10) ? "0" : "") + std::to_string((*it)->first());
        result += (((*it)->middle() < 10) ? "0" : "") + std::to_string((*it)->middle());
        result += (((*it)->last() < 10) ? "0" : "") + std::to_string((*it)->last());
        return result;
    }
}
#endif //GRAPH_INL
