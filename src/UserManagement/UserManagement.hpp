#pragma once

#include <string>

namespace UserManagement
{
    enum PrivilageGroup {student, teacher, unset};

    struct User
    {
        std::string username;
        std::string password;
        PrivilageGroup group;
    };

    bool logIn(std::string username, std::string password);

    void logOut(User *user);

    bool changePasswd(std::string username, std::string password);

    bool addUser(std::string username, std::string password);

    bool removeUser(std::string username, std::string password);

    bool purgeUserDB();
}