/**
 * @file Graph.hpp
 * @brief This file contains the declaration of the Graph class.
 * @author Maksym
 * @date 20.12.2024
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../Vertex/Vertex.hpp"
#include <functional>
#include <unordered_set>
#include <cmath>
#include <utility>

namespace graph {
    /**
     * @brief Represents a graph data structure.
     *
     * @tparam vType The type of vertex data.
     * @tparam vCount The maximum number of vertices in the graph.
     */
    template<typename vType, size_t vCount>
    class Graph {
    public:
        /**
         * @brief Constructs a new graph with the given vertices.
         *
         * @param vertices A vector of shared pointers to vertex objects.
         */
        explicit Graph(const vector<shared_ptr<Vertex<vType, vCount> > > &vertices)
            : vertices_(vertices) {
        }

    private:
        /**
         * @brief A vector of shared pointers to vertex objects.
         */
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
