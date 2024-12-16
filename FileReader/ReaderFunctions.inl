//
// Created by Maksym on 16.12.2024.
//

#ifndef READER_FUNCTIONS_INL
#define READER_FUNCTIONS_INL


namespace reader {
    template<typename T>
    T sto(const string &string_value) {
        T val;
        std::stringstream ss(string_value);
        ss >> val;
        // if found symbols then throw exception
        if (!std::all_of(string_value.begin(), string_value.end(), ::isdigit))
            throw exceptionInFunction(__FUNCTION__,
                                      ERROR_MESSAGES[PARSE_FAILED], string_value, val);
        return val;
    }

    template<typename T1>
    void numberIsValid(const T1 &min, const T1 &max, const T1 &numeric_value) {
        // if number is less than min or greater than max then throw exception
        if (numeric_value < min)
            throw exceptionInFunction(__FUNCTION__, ERROR_MESSAGES[TOO_SMALL], numeric_value, min);
        if (numeric_value > max)
            throw exceptionInFunction(__FUNCTION__, ERROR_MESSAGES[TOO_BIG], numeric_value, max);
    }

    template<typename T1>
    void substringIsValid(const T1 &min, const T1 &max, const string &substring) {
        // trying and throwing exception if substring is not valid
        tryFunction(__FUNCTION__, numberIsValid<T1>, min, max, sto<T1>(substring));
    }

    template<typename T1>
    void stringIsValid(
        const string &string_value,
        const size_t &string_size,
        const size_t &substring_size,
        const T1 &min, const T1 &max) {
        // if string is empty then throw exception
        if (string_value.empty())
            throw exceptionInFunction(__FUNCTION__, ERROR_MESSAGES[STRING_EMPTY]);
        // if string size is not equal to string_size then throw exception
        if (string_value.size() != string_size)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[STRING_WRONG_SIZE], string_value.size(), string_size);
        // checking each substring
        for (size_t i = 0; i < string_size; i += substring_size)
            tryFunction(
                __FUNCTION__,
                substringIsValid<T1>, min, max, string_value.substr(i, substring_size));
    }


}
#endif // READER_FUNCTIONS_INL
