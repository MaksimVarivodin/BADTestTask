//
// Created by Maksym on 18.12.2024.
//

#ifndef VERTEX_INL
#define VERTEX_INL

namespace graph {
    template<typename T, size_t C>
    string to_string(const Vertex<T, C> &vertex) {
        string result;
        for (T number: *(vertex.vNumbers_))
            result += ((number < 10) ? "0" : "") + std::to_string(number);
        return result;
    }

    template<typename vType, size_t vCount>
    const VertexNumbers<vType, vCount> &Vertex<vType, vCount>::vNumbers() const {
        return vNumbers_;
    }

    template<typename vType, size_t vCount>
    const list<Edge<vType, vCount> > &Vertex<vType, vCount>::edges() const {
        return edges_;
    }

    template<typename vType, size_t vCount>
    void Vertex<vType, vCount>::addEdge(const Edge<vType, vCount> &edge) {
        edges_.push_back(edge);
    }

    template<typename vType, size_t vCount>
    string Vertex<vType, vCount>::puzzlePart() const {
        return string(((first() < 10) ? "0" : "") + std::to_string(first()) +
                      ((middle() < 10) ? "0" : "") + std::to_string(middle()) +
                      (edges_.empty()
                           ? ((last() < 10) ? "0" : "") + std::to_string(last())
                           : ""));
    }

    template<typename vType, size_t vCount>
    string Vertex<vType, vCount>::puzzlePartLast() const {
        return ((last() < 10) ? "0" : "") + std::to_string(last());
    }
}
#endif //VERTEX_INL
