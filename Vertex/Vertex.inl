/**
 * @file Vertex.inl
 * @brief This file contains the implementation of the Vertex class.
 * @author Maksym
 * @date 18.12.2024
 */

#ifndef VERTEX_INL
#define VERTEX_INL

namespace graph {
    /**
     * @brief Converts the vertex to a string representation.
     *
     * @tparam T The type of vertex data.
     * @tparam C The maximum number of vertices in the graph.
     * @param vertex The vertex to convert.
     * @return A string representation of the vertex.
     */
    template<typename T, size_t C>
    string to_string(const Vertex<T, C> &vertex) {
        string result;
        for (T number: *(vertex.vNumbers_))
            result += ((number < 10) ? "0" : "") + std::to_string(number);
        return result;
    }

    /**
     * @brief Returns a reference to the vertex numbers.
     *
     * @tparam vType The type of vertex data.
     * @tparam vCount The maximum number of vertices in the graph.
     * @return A const reference to the vertex numbers.
     */
    template<typename vType, size_t vCount>
    const VertexNumbers<vType, vCount> &Vertex<vType, vCount>::vNumbers() const {
        return vNumbers_;
    }

    /**
     * @brief Returns a reference to the edges of the vertex.
     *
     * @tparam vType The type of vertex data.
     * @tparam vCount The maximum number of vertices in the graph.
     * @return A const reference to the edges of the vertex.
     */
    template<typename vType, size_t vCount>
    const list<Edge<vType, vCount> > &Vertex<vType, vCount>::edges() const {
        return edges_;
    }

    /**
     * @brief Adds an edge to the vertex.
     *
     * @tparam vType The type of vertex data.
     * @tparam vCount The maximum number of vertices in the graph.
     * @param edge The edge to add.
     */
    template<typename vType, size_t vCount>
    void Vertex<vType, vCount>::addEdge(const Edge<vType, vCount> &edge) {
        edges_.push_back(edge);
    }

    /**
     * @brief Returns the puzzle part of the vertex.
     *
     * @tparam vType The type of vertex data.
     * @tparam vCount The maximum number of vertices in the graph.
     * @return The puzzle part of the vertex.
     */
    template<typename vType, size_t vCount>
    string Vertex<vType, vCount>::puzzlePart() const {
        return string(((first() < 10) ? "0" : "") + std::to_string(first()) +
                      ((middle() < 10) ? "0" : "") + std::to_string(middle()) +
                      (edges_.empty()
                           ? ((last() < 10) ? "0" : "") + std::to_string(last())
                           : ""));
    }

    /**
     * @brief Returns the last part of the puzzle for the vertex.
     *
     * @tparam vType The type of vertex data.
     * @tparam vCount The maximum number of vertices in the graph.
     * @return The last part of the puzzle for the vertex.
     */
    template<typename vType, size_t vCount>
    string Vertex<vType, vCount>::puzzlePartLast() const {
        return ((last() < 10) ? "0" : "") + std::to_string(last());
    }
}
#endif //VERTEX_INL