//
// Created by Maksym on 16.12.2024.
//
#include "ReaderFunctions.hpp"

namespace reader {
    void arraySizeIsValid(const size_t &arraySize) {
        if (arraySize <= 0)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[BAD_ARRAY_SIZE], arraySize);
    }

    void stringSizeIsValid(const size_t &stringSize) {
        if (stringSize <= 0)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[BAD_STR_SIZE], stringSize);
    }

    void substringSizeIsValid(const size_t &substringSize) {
        if (substringSize <= 0)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[BAD_SUBSTR_SIZE], substringSize);
    }

    void stringSizeIsEqual(const string &stringValue, const size_t &stringSize) {
        if (stringValue.size() != stringSize)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[STRING_WRONG_SIZE], stringValue.size(), stringSize);
    }
}
