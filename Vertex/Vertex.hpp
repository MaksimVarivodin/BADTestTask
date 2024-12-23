//
// Created by Maksym on 18.12.2024.
//

#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <memory>
#include <string>
#include "../FileReader/ReaderFunctions.hpp"

namespace graph {
    using namespace std;
    READER_
    template<typename vType, size_t vCount>
    class Vertex;
    template<typename vType, size_t vCount>
    using Edge = shared_ptr<Vertex<vType, vCount> >;

    template<typename vType, size_t vCount>
    class Vertex {
    public:
        explicit Vertex(const VertexNumbers<vType, vCount> &v_numbers)
            : vNumbers_(v_numbers) {
        }

        Vertex(const VertexNumbers<vType, vCount> &v_numbers, const list<Edge<vType, vCount> > &edges)
            : vNumbers_(v_numbers),
              edges_(edges) {
        }

    private:
        VertexNumbers<vType, vCount> vNumbers_;
        list<Edge<vType, vCount> > edges_;

    public:
        void addEdge(const Edge<vType, vCount> &edge);

        const vType &first() const { return (*vNumbers_)[0]; }
        const vType &last() const { return (*vNumbers_)[vCount - 1]; }
        const vType& middle() const {return (*vNumbers_)[vCount / 2];}

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
