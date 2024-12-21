//
// Created by Maksym on 16.12.2024.
//
#include "ErrorCodes.hpp"
namespace errors
{
    /*
     * Const vector of error messages for BracedException
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
        "Couldn't open file ({})"
    };
}