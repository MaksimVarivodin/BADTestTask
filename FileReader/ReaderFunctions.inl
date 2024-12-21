//
// Created by Maksym on 16.12.2024.
//

#ifndef READER_FUNCTIONS_INL
#define READER_FUNCTIONS_INL


namespace reader {
    template<typename T>
    T sto(const string &stringValue) {
        T val;
        std::stringstream ss(stringValue);
        ss >> val;
        // if found symbols then throw exception
        if (!std::all_of(stringValue.begin(), stringValue.end(), ::isdigit))
            throw exceptionInFunction(__FUNCTION__,
                                      ERROR_MESSAGES[PARSE_FAILED], stringValue, val);
        return val;
    }

    template<typename T1>
    void numberIsValid(const T1 &min, const T1 &max, const T1 &numericValue) {
        // if number is less than min or greater than max then throw exception
        if (numericValue < min)
            throw exceptionInFunction(__FUNCTION__, ERROR_MESSAGES[TOO_SMALL], numericValue, min);
        if (numericValue > max)
            throw exceptionInFunction(__FUNCTION__, ERROR_MESSAGES[TOO_BIG], numericValue, max);
    }

    template<typename T1>
    void substringIsValid(const T1 &min, const T1 &max, const string &substring) {
        // trying and throwing exception if substring is not valid
        tryFunction(__FUNCTION__, numberIsValid<T1>, min, max, sto<T1>(substring));
    }

    template<typename T1, size_t stringSize, size_t substringSize>
    void stringIsValid(
        const string &stringValue,
        const T1 &min, const T1 &max) {
        tryFunction(__FUNCTION__, stringSizeIsValid, stringSize);
        tryFunction(__FUNCTION__, substringSizeIsValid, substringSize);
        // if string is empty then throw exception
        if (stringValue.empty())
            throw exceptionInFunction(__FUNCTION__, ERROR_MESSAGES[STRING_EMPTY]);

        // if string size is not equal to string_size then throw exception
        tryFunction(__FUNCTION__, stringSizeIsEqual, stringValue, stringSize);
        // checking each substring
        for (size_t i = 0; i < stringSize; i += substringSize)
            tryFunction(
                __FUNCTION__,
                substringIsValid<T1>, min, max, stringValue.substr(i, substringSize));
    }

    template<typename vType, size_t vCount, size_t substringSize>
    VertexNumbers<vType, vCount> stringToVectorVertex(
        const string &stringValue) {
        tryFunction(__FUNCTION__, arraySizeIsValid, vCount);
        tryFunction(__FUNCTION__, substringSizeIsValid, substringSize);
        VertexNumbers<vType, vCount> vertex = make_shared<array<vType, vCount> >();

        for (size_t i = 0; i < stringValue.size(); i += substringSize)
            (*vertex)[i / substringSize] = sto<vType>(stringValue.substr(i, substringSize));

        return vertex;
    }

    template<typename vType, size_t vCount, size_t stringSize>
    list<VertexNumbers<vType, vCount> > readFileToList(const string &fileName) {
        ifstream in(fileName);
        // if file is not opened then throw exception
        if (!in.is_open())
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[FILE_NOT_OPENED], fileName);

        list<VertexNumbers<vType, vCount> > lines;

        while (!in.eof()) {
            string line;
            getline(in, line);
            // if line is invalid then throw exception and continue
            try {
                tryFunction(__FUNCTION__, stringIsValid<vType, stringSize, stringSize / vCount>, line, 0, 99);
                lines.emplace_back(stringToVectorVertex<vType, vCount, stringSize / vCount>(line));
            } catch (const BracedException &ex) {
                cerr << ex.what() << endl;
            }
        }
        in.close();
        return lines;
    }

    template<typename vType, size_t vCount>
    map<vType, vector<VertexNumbers<vType, vCount> > > listToMap(const list<VertexNumbers<vType, vCount> > &lines) {
        map<vType, VertexList<vType, vCount> > firstNumberCriteria;
        map<vType, VertexList<vType, vCount> > lastNumberCriteria;
        map<vType, vector<VertexNumbers<vType, vCount> > > resultMap;
        for (const auto &row: lines) {
            // Adding pointer to a line to the first table
            firstNumberCriteria[(*row)[0]].push_back(row);
            // Adding pointer to a line to the 3rd table
            lastNumberCriteria[(*row)[vCount - 1]].push_back(row);
        }
        // Here we are looking for matches between the first and last tables
        for (const auto &[key, listLast]: lastNumberCriteria) {
            // if there is a match
            if (firstNumberCriteria.contains(key)) {
                // we copy elements from the lastNumberTable
                resultMap[key] = {std::begin(listLast), std::end(listLast)};
                // here we search for numbers that don't have a pair for the last number and filter
                for (const auto &element: firstNumberCriteria[key]) {
                    if (!firstNumberCriteria.contains((*element)[vCount - 1]))
                        resultMap[-key - 1].push_back(element);
                }
            }
        }
        return resultMap;
    }
}
#endif // READER_FUNCTIONS_INL
