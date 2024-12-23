/**
 * @file ErrorCodes.cpp
 * @brief This file contains the implementation of error messages for the error codes.
 * @author Maksym
 * @date 16.12.2024
 */

#include "ErrorCodes.hpp"

namespace errors {
    /**
     * @brief Const vector of error messages corresponding to the error codes.
     *
     * This vector contains error messages for each error code, including placeholders for dynamic values.
     */
    extern const vector<string> ERROR_MESSAGES{
        "Success",
        "Array size is invalid ({})",
        "String size is invalid ({})",
        "Substring size is invalid ({})",
        "Parsing failed (non digit symbols found : \"{}\")",
        "Number is too small ({}, min is {})",
        "Number is too big ({}, max is {})",
        "String is empty",
        "String has wrong size ({} instead of {})",
        "Couldn't open file ({})",
        "Puzzle combination is invalid ({} at position {}-{})",
    };
}