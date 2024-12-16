//
// Created by Maksym on 16.12.2024.
//
#include "ErrorCodes.hpp"
namespace errors
{
    extern const vector<string> ERROR_MESSAGES{
        "Success",
        "Parsing failed (non digit symbols found : \"{}\")",
        "Number is too small ({}, min is {})",
        "Number is too big ({}, max is {})",
        "String is empty",
        "String has wrong size ({} instead of {})",
        "Couldn't open file ({})"
    };
}