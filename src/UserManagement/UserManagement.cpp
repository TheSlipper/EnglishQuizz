#include "UserManagement.hpp"

namespace UserManagement
{
    bool logIn(std::string username, std::string password)
    {
        return true;
    }

    void logOut(User *user)
    {
        delete user;
    }

    bool changePasswd(std::string username, std::string password)
    {
        return true;
    }

    bool addUser(std::string username, std::string password)
    {
        return true;
    }

    bool removeUser(std::string username, std::string password)
    {
        return true;
    }

    bool purgeUserDB()
    {
        return true;
    }
}