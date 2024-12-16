//
// Created by Maksym on 16.12.2024.
//
#include "ReaderFunctions.hpp"

namespace reader {
    list<string> readFile(const string &fileName) {
        ifstream in(fileName);
        // if file is not opened then throw exception
        if (!in.is_open())
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[FILE_NOT_OPENED], fileName);
        list<string> lines;

        while (!in.eof()) {
            string line;
            getline(in, line);
            // if line is invalid then throw exception and continue
            try {
                tryFunction(__FUNCTION__, stringIsValid<int16_t>, line, 6, 2, 0, 99);
                lines.push_back(line);
            } catch (const BracedException &ex) {
                cerr << ex.what() << endl;
            }
        }
        in.close();
        return lines;
    }
}