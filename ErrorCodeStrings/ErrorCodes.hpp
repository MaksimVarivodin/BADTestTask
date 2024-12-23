/**
 * @file ErrorCodes.hpp
 * @brief This file contains the definition of error codes and their corresponding error messages.
 * @author Maksym
 * @date 16.12.2024
 */

#ifndef ERROR_CODES_STRINGS_HPP
#define ERROR_CODES_STRINGS_HPP

#include <vector>
#include <string>

/**
 * @brief Namespace for error codes and error messages.
 */
namespace errors {
    using namespace std;

    /**
     * @brief Vector of error messages corresponding to the error codes.
     */
    extern const vector<string> ERROR_MESSAGES;

    /**
     * @brief Enumeration of error codes.
     */
    enum ERROR_CODE: size_t {
        SUCCESS,
        // arraySizeIsValid Errors
        BAD_ARRAY_SIZE, ///< Indicates that the array size is invalid.
        // stringSizeIsValid
        BAD_STR_SIZE, ///< Indicates that the string size is invalid.
        // substringSizeIsValid
        BAD_SUBSTR_SIZE, ///< Indicates that the substring size is invalid.
        // sto Errors
        PARSE_FAILED, ///< Indicates that parsing failed.
        // numberIsValid Errors
        TOO_SMALL, ///< Indicates that the number is too small.
        TOO_BIG, ///< Indicates that the number is too big.
        // stringIsValid Errors
        STRING_EMPTY, ///< Indicates that the string is empty.
        STRING_WRONG_SIZE, ///< Indicates that the string has an incorrect size.
        // readFile Errors
        FILE_NOT_OPENED, ///< Indicates that the file could not be opened.
        // puzzleCombinationIsValid Errors
        PUZZLE_INVALID, ///< Indicates that the puzzle combination is invalid.
    };
}

/**
 * @brief Macro to simplify the use of the errors namespace.
 */
#define ERRORS_ using namespace errors;

#endif // ERROR_CODES_STRINGS_HPP
