//
// Created by Maksym on 16.12.2024.
//

#ifndef ERROR_CODES_STRINGS_HPP
#define ERROR_CODES_STRINGS_HPP

#include <vector>
#include <string>

namespace errors {
    using namespace std;
    extern const vector<string> ERROR_MESSAGES;

    enum ERROR_CODE: size_t {
        SUCCESS,
        // arraySizeIsValid Errors
        BAD_ARRAY_SIZE,
        // stringSizeIsValid
        BAD_STR_SIZE,
        // substringSizeIsValid
        BAD_SUBSTR_SIZE,
        // sto Errors
        PARSE_FAILED,
        // numberIsValid Errors
        TOO_SMALL,
        TOO_BIG,
        // stringIsValid Errors
        STRING_EMPTY,
        STRING_WRONG_SIZE,
        // readFile Errors
        FILE_NOT_OPENED,
    };
}
#endif // ERROR_CODES_STRINGS_HPP
#define ERRORS_ using namespace errors;
