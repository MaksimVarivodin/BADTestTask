//
// Created by Maksym on 16.12.2024.
//

#ifndef READER_FUNCTIONS_HPP
#define READER_FUNCTIONS_HPP

#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <map>
#include <memory>
#include <array>

#include "../ErrorCodeStrings/ErrorCodes.hpp"
#include "../BracedException/BracedException.hpp"

namespace reader {
    using namespace std;

    ERRORS_
    BR_EXCEPT_


    template<typename vType, size_t vCount>
    using VertexNumbers = shared_ptr<array<vType, vCount>>;



    template<typename vType, size_t vCount>
    using VertexList = list<VertexNumbers<vType, vCount> >;

    template<typename vType, size_t vCount>
    using HashVertexData =
    pair<
        map<vType, VertexList<vType, vCount> >,
        map<vType, VertexList<vType, vCount> >
    >;


    void arraySizeIsValid(const size_t &vCount);

    void stringSizeIsValid(const size_t &stringSize);

    void substringSizeIsValid(const size_t &substringSize);

    void stringSizeIsEqual(const string &stringValue, const size_t &stringSize);

    template<typename T>
    T sto(const string &stringValue);

    template<typename vType>
    void numberIsValid(const vType &min, const vType &max, const vType &numericValue);

    template<typename vType>
    void substringIsValid(const vType &min, const vType &max, const string &substring);

    template<typename vType, size_t stringSize, size_t substringSize>
    void stringIsValid(
        const string &stringValue,
        const vType &min, const vType &max);

    template<typename arrayType, size_t vCount, size_t substringSize>
    VertexNumbers<arrayType, vCount> stringToVectorVertex(const string &stringValue);


    template<typename vType, size_t vCount, size_t stringSize>
    list<VertexNumbers<vType, vCount> > readFileToList(const string &fileName);
}

#endif // READER_FUNCTIONS_HPP
#define READER_ using namespace reader;
#include "ReaderFunctions.inl"
