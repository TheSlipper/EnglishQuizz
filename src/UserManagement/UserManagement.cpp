////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "UserManagement.hpp"

namespace UserManagement
{
    ////////////////////////////////////////////////////////////
    void makeTempMainDb()
    {
#ifdef __WINDOWS__
        // TODO: Implement moving files for windows
#endif
#ifdef __UNIX__
        std::string command = "mv ";
        command.append(USER_TEMP_DB_FILE_PATH);
        command.append(" ");
        command.append(USER_DB_FILE_PATH);
        system(command.c_str());
#endif
    }

    ////////////////////////////////////////////////////////////
    bool logIn(std::string username, std::string password, User *user)
    {
        auto *helper = new User;
        FILE *filePtr = fopen(USER_DB_FILE_PATH, "rb");

        if (filePtr == NULL)
        {
            std::cerr << "bool logIn(std::string username, std::string password, User *user)" << std::endl;
            return nullptr;
        }

        while(fread(helper, sizeof(User), 1, filePtr) != 0)
        {
            std::string helperUsername, helperPasswd;
            helperUsername = helper->username;
            helperPasswd = helper->password;
            if (username.compare(helperUsername) == 0 && password.compare(helperPasswd) == 0)
            {
                user->group = helper->group;
                delete helper;
                return true;
            }
        }

        return false;
    }

    ////////////////////////////////////////////////////////////
    void logOut(User *user)
    {
        user->group = PrivilageGroup::unset;
        for (int i=0; i < 50; i++)
        {
            user->username[i] = 0;
            user->password[i] = 0;
        }
    }

    ////////////////////////////////////////////////////////////
    bool changePasswd(std::string username, std::string password)
    {
        // TODO:
        return true;
    }

    ////////////////////////////////////////////////////////////
    FILE* reWriteUsers()
    {
        auto *user = new User;
        FILE *filePtr = fopen(USER_DB_FILE_PATH, "rb");
        FILE *tmpPtr = fopen(USER_TEMP_DB_FILE_PATH, "wb");

        if (filePtr == NULL || tmpPtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (FILE* reWriteUsers())" << std::endl;
            return nullptr;
        }

        while(fread(user, sizeof(User), 1, filePtr) != 0)
            fwrite(user, sizeof(User), 1, tmpPtr);

        fclose(filePtr);
        return tmpPtr;
    }

    ////////////////////////////////////////////////////////////
    bool addUser(std::string username, std::string password, PrivilageGroup group)
    {
        auto *user = new User;
        FILE *filePtr = reWriteUsers();
        if (filePtr == nullptr)
            return false;

        strcpy(user->username, username.c_str());
        strcpy(user->password, password.c_str());
        user->group = group;

        fwrite(user, sizeof(User), 1, filePtr);

        fclose(filePtr);
        makeTempMainDb();
        return true;
    }

    ////////////////////////////////////////////////////////////
    bool removeUser(std::string username)
    {
        // TODO: Check if this works
        auto *user = new User;
        FILE *filePtr = fopen(USER_DB_FILE_PATH, "rb");
        FILE *tmpPtr = fopen(USER_TEMP_DB_FILE_PATH, "wb");

        if (filePtr == NULL || tmpPtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (FILE* reWriteUsers())" << std::endl;
            return false;
        }

        while(fread(user, sizeof(User), 1, filePtr) != 0)
        {
            std::string helperUsername;
            helperUsername = user->username;
            if (helperUsername.compare(username) != 0)
                fwrite(user, sizeof(User), 1, tmpPtr);
        }

        fclose(filePtr);
        fclose(tmpPtr);
        makeTempMainDb();

        return true;
    }

    ////////////////////////////////////////////////////////////
    void purgeUserDB()
    {
        // TODO:
    }

    ////////////////////////////////////////////////////////////
    bool loadNthUsr(User *user, int n)
    {
        FILE *filePtr = fopen(USER_DB_FILE_PATH, "rb");

        if (filePtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (bool loadNthUsr(User *user, int n))" << std::endl;
            return false;
        }

        int iteration_num = 1;
        while(fread(user, sizeof(User), 1, filePtr) != 0)
        {
            if (iteration_num == n)
                return true;
            iteration_num++;
        }

        fclose(filePtr);
        return false;
    }

    ////////////////////////////////////////////////////////////
    bool getUserByNickname(User *user, std::string username)
    {
        FILE *filePtr = fopen(USER_DB_FILE_PATH, "rb");

        if (filePtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (bool getUserByNickname(User *user, std::string username))";
            std::cout << std::endl;
            return false;
        }

        while(fread(user, sizeof(User), 1, filePtr) != 0)
        {
            std::string helper;
            helper = user->username;

            if (username.compare(helper) == 0)
                return true;
        }

        fclose(filePtr);
        return false;
    }
}