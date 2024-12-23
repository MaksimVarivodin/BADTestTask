/**
 * @file Vertex.hpp
 * @brief This file contains the declaration of the Vertex class.
 * @author Maksym
 * @date 18.12.2024
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <memory>
#include <string>
#include "../FileReader/ReaderFunctions.hpp"

namespace graph {
    using namespace std;

    // Forward declaration of Reader_ macro
    READER_

    // Forward declaration of template classes
    template<typename vType, size_t vCount>
    class Vertex;

    template<typename vType, size_t vCount>
    using Edge = shared_ptr<Vertex<vType, vCount> >;

    /**
     * @brief Template class representing a vertex in a graph.
     * @tparam vType Type of vertex data.
     * @tparam vCount Number of elements in the vertex data.
     */
    template<typename vType, size_t vCount>
    class Vertex {
    public:
        /**
        * @brief Constructor for a vertex with edges.
        * @param vNumbers Vertex data.
        * @param edges List of edges connected to the vertex.
        */
        Vertex(const VertexNumbers<vType, vCount> &vNumbers, const list<Edge<vType, vCount> > &edges)
            : vNumbers_(vNumbers),
              edges_(edges) {
        }

        /**
         * @brief Constructor for a vertex with no edges.
         * @param vNumbers Vertex data.
         */
        explicit Vertex(const VertexNumbers<vType, vCount> &vNumbers)
            : Vertex(vNumbers, {}) {
        }

    private:
        VertexNumbers<vType, vCount> vNumbers_;
        list<Edge<vType, vCount> > edges_;

    public:
        void addEdge(const Edge<vType, vCount> &edge);

        const vType &first() const { return (*vNumbers_)[0]; }
        const vType &last() const { return (*vNumbers_)[vCount - 1]; }
        const vType &middle() const { return (*vNumbers_)[vCount / 2]; }

        const VertexNumbers<vType, vCount> &vNumbers() const;

        const list<Edge<vType, vCount> > &edges() const;

        template<typename T, size_t C>
        friend string to_string(const Vertex<T, C> &vertex);

        [[nodiscard]] string puzzlePart() const;

        [[nodiscard]] string puzzlePartLast() const;
    };
}


#endif //VERTEX_HPP

#include "Vertex.inl"
#define GRAPH_ using namespace graph;
