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
    /*template<typename vType, size_t vCount>
    double Graph<vType, vCount>::keyGenerator(
        const std::shared_ptr<Vertex<vType, vCount> > &vertex) {
        return static_cast<double>(vertex->first() * vertex->last() * vertex->middle());
    }



    template<typename vType, size_t vCount>
    list<shared_ptr<Vertex<vType, vCount> > > Graph<vType, vCount>::dfs() {
        sortByEdgeCount();
        std::unordered_set<double> visited;
        std::list<std::shared_ptr<Vertex<vType, vCount> > > traversal;

        function<list<shared_ptr<Vertex<vType, vCount> > >
            (const std::shared_ptr<Vertex<vType, vCount> > &)> dfsHelper =
                [&](const std::shared_ptr<Vertex<vType, vCount> > &vertex) {
            // Some random calculations to create unique key
            const double key = keyGenerator(vertex);
            cout << "Key: " << key << endl;
            if (!vertex || visited.contains(key)) {
                return;
            }

            visited.insert(key);
            traversal.push_back(vertex);

            // Рекурсивно обходим соседей
            for (const auto &neighbor: vertex->edges()) {
                dfsHelper(neighbor);
            }
        };
        // Итерируемся по всем вершинам графа
        for (const auto &vertex: vertices_) {
            if (!vertex) continue;
            double key = keyGenerator(vertex);
            cout << "Key: " << key << endl;
            if (!visited.contains(key)) {
                dfsHelper(vertex);
            }
        }

        return traversal;
    }*/

    template<typename vType, size_t vCount>
    Graph<vType, vCount> Graph<vType, vCount>::createGraph(
        const map<vType, vector<VertexNumbers<vType, vCount> > > &vData) {
        // Map to save vertices for quick access by key
        map<vType, list<shared_ptr<Vertex<vType, vCount> > > > vertexMap;
        // Filling the vertexMap with lists of Vertices(Vertex class)
        for (const auto &[key, vDataList]: vData)
            for (const auto &vDataListElement: vDataList)
                vertexMap[key].push_back(make_shared<Vertex<vType, vCount> >(vDataListElement));
        // Creating connections between vertices
        auto vertexIterator(vertexMap.begin());
        for (; vertexIterator->first < 0; ++vertexIterator) {
            for (const auto &vertex: vertexIterator->second)
                if (vertexMap.contains(vertex->first()))
                    for (auto &addEdgeElement: vertexMap[vertex->first()])
                        if (addEdgeElement->first() != vertex->first())
                            addEdgeElement->addEdge(vertex);
        }

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
}
#endif //GRAPH_INL
