#pragma once

#include <string>

namespace UserManagement
{
    // TODO: Comment this section
    // TODO: Change the priority later (unset first)
    enum PrivilageGroup {teacher, student, unset};

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