//
// Created by Maksym on 20.12.2024.
//

#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "../Vertex/Vertex.hpp"
#include <functional>
#include <unordered_set>
#include <cmath>
#include <utility>

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
        string dfs();

        void puzzleCombinationIsValid(const string &) const;

        static Graph<vType, vCount> createGraph(const map<vType, vector<VertexNumbers<vType, vCount> > > &vData);

        template<typename T, size_t C>
        friend string to_string(const Graph<T, C> &vertex);

    private:
        signed long long findVertex(const string &vertex) const;

        void sortByEdgeCount();

        double keyGenerator(const std::shared_ptr<Vertex<vType, vCount> > &vertex);

        string dfsHelper(const shared_ptr<Vertex<vType, vCount> > &vertex,
                         unordered_set<double> visited,
                         map<double, string> &visitedCache);
    };
} // graph

#endif //GRAPH_HPP
#include "Graph.inl"
