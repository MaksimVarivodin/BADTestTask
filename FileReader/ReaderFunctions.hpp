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

#include "../ErrorCodeStrings/ErrorCodes.hpp"
#include "../BracedException/BracedException.hpp"

namespace reader {
    ERRORS_
    BR_EXCEPT_

    template<typename T>
    T sto(const string &string_value);

    template<typename T1>
    void numberIsValid(const T1 &min, const T1 &max, const T1 &numeric_value);

    template<typename T1>
    void substringIsValid(const T1 &min, const T1 &max, const string &substring);

    template<typename T1>
    void stringIsValid(
        const string &string_value,
        const size_t &string_size,
        const size_t &substring_size,
        const T1 & min, const T1 & max);

    list<string> readFile(const string &fileName);

}

#endif // READER_FUNCTIONS_HPP
#define READER_ using namespace reader;
#include "ReaderFunctions.inl"
