#include <cstdint>
#include <iostream>
#include "BracedException/BracedException.hpp"
#include "FileReader/ReaderFunctions.hpp"

int main()
{
    BR_EXCEPT_
    READER_

    try{
        auto result = tryFunction(__FUNCTION__, readFile, "source.txt");
    }
    catch(const BracedException &ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
