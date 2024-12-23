/**
 * @file BracedException.hpp
 * @brief This file contains the definition of BracedException class and related functions.
 * @author Maksym
 * @date 16.12.2024
 */

#ifndef BRACED_EXCEPTION_HPP
#define BRACED_EXCEPTION_HPP

#include <format>
#include <stdexcept>
#include <string>
#include <utility>

/**
 * @brief Namespace for custom exception handling.
 */
namespace brexcept {
    using namespace std;

    /**
     * @brief Custom exception class that extends std::runtime_error.
     *
     * This class provides a way to throw exceptions with formatted error messages.
     */
    class BracedException : public runtime_error {
    public:
        /**
         * @brief Constructor with default error message.
         *
         * Constructs a BracedException with a default error message.
         */
        BracedException(const string &errorMessage = "Something went wrong. ('_,' )")
            : runtime_error(errorMessage) {
        }

        /**
         * @brief Constructor with formatted error message using std::format.
         *
         * Constructs a BracedException with a formatted error message using std::format.
         *
         * @tparam P Types of the arguments to be formatted.
         * @param toFormat Format string.
         * @param exceptionArgs Arguments to be formatted.
         */
        template<typename... P>
        BracedException(const format_string<P...> &toFormat, P &&... exceptionArgs)
            : BracedException(format(toFormat, std::forward<P>(exceptionArgs)...)) {
        }

        /**
         * @brief Constructor with formatted error message using std::vformat.
         *
         * Constructs a BracedException with a formatted error message using std::vformat.
         *
         * @tparam P Types of the arguments to be formatted.
         * @param toFormat Format string.
         * @param exceptionArgs Arguments to be formatted.
         */
        template<typename... P>
        BracedException(const string &toFormat, P &&... exceptionArgs)
            : BracedException(vformat(toFormat, make_format_args(exceptionArgs...))) {
        }

        /**
         * @brief Constructor with formatted error message using std::vformat.
         *
         * Constructs a BracedException with a formatted error message using std::vformat.
         *
         * @tparam P Types of the arguments to be formatted.
         * @param toFormat Format string.
         * @param exceptionArgs Arguments to be formatted.
         */
        template<typename... P>
        BracedException(const char *toFormat, P &&... exceptionArgs)
            : BracedException(vformat(string(toFormat), make_format_args(exceptionArgs...))) {
        }
    };

    /**
     * @brief Function to create a BracedException with a formatted error message.
     *
     * This function creates a BracedException with a formatted error message, including the name of the function.
     *
     * @tparam P Types of the arguments to be formatted.
     * @param functionName Name of the function.
     * @param toFormat Format string.
     * @param exceptionArgs Arguments to be formatted.
     * @return A BracedException with the formatted error message.
     */
    template<typename... P>
    BracedException exceptionInFunction(const string &functionName, const string &toFormat, P &&... exceptionArgs) {
        return BracedException("Exception in " + functionName + ":\n" + toFormat, exceptionArgs...);
    }

    /**
     * @brief Function to create a BracedException with a formatted error message.
     *
     * This function creates a BracedException with a formatted error message, including the name of the function.
     *
     * @tparam P Types of the arguments to be formatted.
     * @param functionName Name of the function.
     * @param toFormat Format string.
     * @param exceptionArgs Arguments to be formatted.
     * @return A BracedException with the formatted error message.
     */
    template<typename... P>
    BracedException exceptionInFunction(const char *functionName, const string &toFormat, P &&... exceptionArgs) {
        return exceptionInFunction(string(functionName), toFormat, exceptionArgs...);
    }

    /**
     * @brief Function to call a function and handle BracedExceptions.
     *
     * This function calls a function with arguments and handles BracedExceptions by adding a new context to the current one.
     *
     * @tparam Func Type of the function to be called.
     * @tparam Args Types of the arguments to be passed to the function.
     * @param functionName Name of the function.
     * @param function Function to be called.
     * @param args Arguments to be passed to the function.
     * @return The result of the function call.
     */
    template<typename Func, typename... Args>
    auto tryFunction(const std::string &functionName, Func &&function, Args &&... args)
        -> decltype(std::forward<Func>(function)(std::forward<Args>(args)...)) {
        try {
            // Call of a passed function with arguments
            return std::forward<Func>(function)(std::forward<Args>(args)...);
        } catch (const BracedException &ex) {
            // Adding new context to the current one
            throw exceptionInFunction(functionName, ex.what());
        }
    }
};

/**
 * @brief Macro to simplify the use of the brexcept namespace.
 */
#define BR_EXCEPT_ using namespace brexcept;

#endif //BRACED_EXCEPTION_HPP