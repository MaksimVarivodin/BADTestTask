//
// Created by Maksym on 20.12.2024.
//

#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "../Vertex/Vertex.hpp"
#include <functional>
#include <unordered_set>
#include <cmath>

namespace graph {
    template<typename vType, size_t vCount>
    class Graph {
    public:
        explicit Graph(const vector<shared_ptr<Vertex<vType, vCount> > > &vertices)
            : vertices_(vertices) {
        }

    private:
        vector<shared_ptr<Vertex<vType, vCount> > > vertices_;

    public:
        list<shared_ptr<Vertex<vType, vCount> > > dfs();

        static Graph<vType, vCount> createGraph(const map<vType, vector<VertexNumbers<vType, vCount> > > &vData);

        template<typename T, size_t C>
        friend string to_string(const Graph<T, C> &vertex);

    private:
        void sortByEdgeCount();

        double keyGenerator(const std::shared_ptr<Vertex<vType, vCount> > &vertex);
    };
    template<typename vType, size_t vCount>
    string longestPathToString(const list<shared_ptr<Vertex<vType, vCount> > >&p);
} // graph

#endif //GRAPH_HPP
#include "Graph.inl"
