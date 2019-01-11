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
        FILE *filePtr = fopen(USER_DB_FILE_PATH, "rb");
        std::unique_ptr<std::string> tempUsername, tempPassword;

        if (filePtr == NULL)
        {
            std::cerr << "bool logIn(std::string username, std::string password, User *user)" << std::endl;
            return nullptr;
        }

        while(fread(user, sizeof(User), 1, filePtr) != 0)
        {
            tempUsername = std::make_unique<std::string>();
            strcpy(user->username, tempUsername->c_str());
            tempPassword = std::make_unique<std::string>();
            strcpy(user->password, tempUsername->c_str());

            if (username.compare(*tempUsername) && password.compare(*tempPassword))
                return true;
        }

        return false;
    }

    ////////////////////////////////////////////////////////////
    void logOut(User *user)
    {
        delete user;
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
        // TODO:
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
    bool removeUser(std::string username, std::string password)
    {
        // TODO:
        return true;
    }

    ////////////////////////////////////////////////////////////
    bool purgeUserDB()
    {
        // TODO:
        return true;
    }
}