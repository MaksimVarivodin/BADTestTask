/**
 * @file ReaderFunctions.inl
 * @brief This file contains the implementation of various reader functions for processing data from files.
 * @author Maksym
 * @date 16.12.2024
 */

#ifndef READER_FUNCTIONS_INL
#define READER_FUNCTIONS_INL

namespace reader {
    /**
     * @brief Template function to convert a string to a numeric value.
     *
     * This function converts a string to a numeric value using stringstream.
     * If the string contains non-digit symbols, it throws a BracedException with a specific error message.
     *
     * @tparam T The type of the numeric value to be converted.
     * @param stringValue The string to be converted.
     * @return The converted numeric value.
     */
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

    /**
     * @brief Template function to validate a numeric value against a minimum and maximum value.
     *
     * This function checks if a numeric value is less than the minimum or greater than the maximum.
     * If the value is invalid, it throws a BracedException with a specific error message.
     *
     * @tparam T1 The type of the numeric value to be validated.
     * @param min The minimum value.
     * @param max The maximum value.
     * @param numericValue The numeric value to be validated.
     */
    template<typename T1>
    void numberIsValid(const T1 &min, const T1 &max, const T1 &numericValue) {
        // if number is less than min or greater than max then throw exception
        if (numericValue < min)
            throw exceptionInFunction(__FUNCTION__, ERROR_MESSAGES[TOO_SMALL], numericValue, min);
        if (numericValue > max)
            throw exceptionInFunction(__FUNCTION__, ERROR_MESSAGES[TOO_BIG], numericValue, max);
    }

    /**
     * @brief Template function to validate a substring against a minimum and maximum value.
     *
     * This function converts the substring to a numeric value using the sto function,
     * and then validates the numeric value using the numberIsValid function.
     *
     * @tparam T1 The type of the numeric value to be validated.
     * @param min The minimum value.
     * @param max The maximum value.
     * @param substring The substring to be validated.
     */
    template<typename T1>
    void substringIsValid(const T1 &min, const T1 &max, const string &substring) {
        // trying and throwing exception if substring is not valid
        tryFunction(__FUNCTION__, numberIsValid<T1>, min, max, sto<T1>(substring));
    }

    /**
     * @brief Template function to validate a string against a minimum and maximum value,
     * and the size of the string and the size of each substring.
     *
     * This function validates the string size, each substring, and the numeric values in the string.
     * If any validation fails, it throws a BracedException with a specific error message.
     *
     * @tparam T1 The type of the numeric values to be validated.
     * @tparam stringSize The size of the string.
     * @tparam substringSize The size of each substring.
     * @param stringValue The string to be validated.
     * @param min The minimum value.
     * @param max The maximum value.
     */
    template<typename T1, size_t stringSize, size_t substringSize>
    void stringIsValid(
        const string &stringValue,
        const T1 &min, const T1 &max) {
        //
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

    /**
     * @brief Template function to convert a string to a vector of numeric values.
     *
     * This function converts a string to a vector of numeric values using the sto function.
     * It also validates the size of the vector and the size of each substring.
     *
     * @tparam vType The type of the numeric values in the vector.
     * @tparam vCount The size of the vector.
     * @tparam substringSize The size of each substring.
     * @param stringValue The string to be converted.
     * @return A shared pointer to the vector of numeric values.
     */
    template<typename vType, size_t vCount, size_t substringSize>
    VertexNumbers<vType, vCount> stringToVectorVertex(
        const string &stringValue) {
        //
        tryFunction(__FUNCTION__, arraySizeIsValid, vCount);
        tryFunction(__FUNCTION__, substringSizeIsValid, substringSize);

        VertexNumbers<vType, vCount> vertex = make_shared<array<vType, vCount> >();

        for (size_t i = 0; i < stringValue.size(); i += substringSize)
            (*vertex)[i / substringSize] = sto<vType>(stringValue.substr(i, substringSize));

        return vertex;
    }

    /**
     * @brief Template function to read a file and convert its content to a list of vectors of numeric values.
     *
     * This function reads a file line by line, converts each line to a vector of numeric values using the stringToVectorVertex function,
     * and stores the vectors in a list.
     * If any line is invalid, it throws a BracedException with a specific error message and continues processing the remaining lines.
     *
     * @tparam vType The type of the numeric values in the vectors.
     * @tparam vCount The size of the vectors.
     * @tparam stringSize The size of each line in the file.
     * @param fileName The name of the file to be read.
     * @return A list of shared pointers to the vectors of numeric values.
     */
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

    /**
     * @brief Template function to convert a list of vectors of numeric values to a map of numeric values and vectors.
     *
     * This function converts a list of vectors of numeric values to a map of numeric values and vectors.
     * It searches for matches between the first and last numbers in each vector, and filters out numbers that don't have a pair for the last number.
     *
     * @tparam vType The type of the numeric values in the vectors.
     * @tparam vCount The size of the vectors.
     * @param lines The list of vectors of numeric values.
     * @return A map of numeric values and vectors.
     */
    template<typename vType, size_t vCount>
    map<vType, vector<VertexNumbers<vType, vCount> > > listToMap(const list<VertexNumbers<vType, vCount> > &lines) {
        //
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
            //
            // if there is a match
            if (firstNumberCriteria.contains(key)) {
                //
                // we copy elements from the lastNumberTable
                resultMap[key] = {std::begin(listLast), std::end(listLast)};

                // here we search for numbers that don't have a pair for the last number and filter
                for (const auto &element: firstNumberCriteria[key])
                    if (!firstNumberCriteria.contains((*element)[vCount - 1]))
                        resultMap[-key - 1].push_back(element);
            }
        }
        return resultMap;
    }
}
#endif // READER_FUNCTIONS_INL
