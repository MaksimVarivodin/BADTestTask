/**
 * @file ReaderFunctions.cpp
 * @brief This file contains the implementation of various reader functions for processing data from files.
 * @author Maksym
 * @date 16.12.2024
 */

#include "ReaderFunctions.hpp"

namespace reader {
    /**
     * @brief Function to validate the size of an array.
     *
     * This function checks if the size of an array is greater than zero.
     * If the size is not greater than zero, it throws a BracedException with a specific error message.
     *
     * @param arraySize The size of the array to be validated.
     */
    void arraySizeIsValid(const size_t &arraySize) {
        if (arraySize <= 0)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[BAD_ARRAY_SIZE], arraySize);
    }

    /**
     * @brief Function to validate the size of a string.
     *
     * This function checks if the size of a string is greater than zero.
     * If the size is not greater than zero, it throws a BracedException with a specific error message.
     *
     * @param stringSize The size of the string to be validated.
     */
    void stringSizeIsValid(const size_t &stringSize) {
        if (stringSize <= 0)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[BAD_STR_SIZE], stringSize);
    }

    /**
     * @brief Function to validate the size of a substring.
     *
     * This function checks if the size of a substring is greater than zero.
     * If the size is not greater than zero, it throws a BracedException with a specific error message.
     *
     * @param substringSize The size of the substring to be validated.
     */
    void substringSizeIsValid(const size_t &substringSize) {
        if (substringSize <= 0)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[BAD_SUBSTR_SIZE], substringSize);
    }

    /**
     * @brief Function to validate the size of a string against a specific size.
     *
     * This function checks if the size of a string is equal to a specific size.
     * If the sizes are not equal, it throws a BracedException with a specific error message.
     *
     * @param stringValue The string to be validated.
     * @param stringSize The specific size to compare against.
     */
    void stringSizeIsEqual(const string &stringValue, const size_t &stringSize) {
        if (stringValue.size() != stringSize)
            throw exceptionInFunction(
                __FUNCTION__,
                ERROR_MESSAGES[STRING_WRONG_SIZE], stringValue.size(), stringSize);
    }
}