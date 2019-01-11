#include "MiscUtils.hpp"

namespace MiscUtils
{
    std::string decrypt(std::string data)
    {

    }

    std::string encrypt(std::string data)
    {

    }

    void clearScreen()
    {
    #ifdef __UNIX__
        system("clear");
    #endif
    #ifdef __WINDOWS__
        system("cls");
    #endif
    }
}