//
// Created by Maksym on 16.12.2024.
//

#ifndef BRACED_EXCEPTION_HPP
#define BRACED_EXCEPTION_HPP

#include <format>
#include <stdexcept>
#include <string>
#include <utility>



namespace brexcept
{
    using namespace std;

    class BracedException: public runtime_error
    {

    public:
        BracedException(const string & errorMessage = "Something went wrong. ('_,' )")
            : runtime_error(errorMessage)
        {  }
        template<typename ... P>
        BracedException(const format_string<P...> &toFormat, P&& ... exceptionArgs)
        : BracedException(format(toFormat, std::forward<P>(exceptionArgs)...))
        {     }
        template<typename ... P>
        BracedException(const string& toFormat,  P&& ... exceptionArgs)
        : BracedException(vformat(toFormat, make_format_args(exceptionArgs...)))
        {     }
        template<typename ... P>
        BracedException(const char* toFormat,  P&& ... exceptionArgs)
        : BracedException(vformat(string(toFormat), make_format_args(exceptionArgs...)))
        {     }

    };

    template<typename ... P>
    BracedException exceptionInFunction(const string& functionName, const string& toFormat, P&& ... exceptionArgs) {
        return BracedException("Exception in " + functionName + ":\n" + toFormat, exceptionArgs...);
    }
    template<typename ... P>
    BracedException exceptionInFunction(const char* functionName, const string& toFormat, P&& ... exceptionArgs) {
        return exceptionInFunction(string(functionName), toFormat, exceptionArgs...);
    }

    template <typename Func, typename... Args>
    auto tryFunction(const std::string& functionName, Func&& function, Args&&... args)
    -> decltype(std::forward<Func>(function)(std::forward<Args>(args)...)) {
        try {
            // Call of a passed function with arguments
            return std::forward<Func>(function)(std::forward<Args>(args)...);
        } catch (const BracedException& ex) {
            // Adding new context to the current one
            throw exceptionInFunction(functionName, ex.what());
        }
    }

};

#define BR_EXCEPT_ using namespace brexcept;
#endif //BRACED_EXCEPTION_HPP
