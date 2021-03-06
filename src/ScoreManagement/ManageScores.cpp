////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ManageScores.hpp"

namespace ScoreManagement
{
    ////////////////////////////////////////////////////////////
    void makeTempMainDb()
    {
#ifdef __WINDOWS__
        std::string command = "mv ";
        command.append(SCORE_TEMP_DB_FILE_PATH);
        command.append(" ");
        command.append(SCORE_DB_FILE_PATH);
        system(command.c_str());
#endif
#ifdef __UNIX__
        std::string command = "mv ";
        command.append(SCORE_TEMP_DB_FILE_PATH);
        command.append(" ");
        command.append(SCORE_DB_FILE_PATH);
        system(command.c_str());
#endif
    }

    ////////////////////////////////////////////////////////////
    FILE* reWriteScores()
    {
        auto *score = new Score;
        FILE *filePtr = fopen(SCORE_DB_FILE_PATH, "rb");
        FILE *tmpPtr = fopen(SCORE_TEMP_DB_FILE_PATH, "wb");

        if (filePtr == NULL || tmpPtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (FILE* reWriteScores())" << std::endl;
            return nullptr;
        }

        while(fread(score, sizeof(Score), 1, filePtr) != 0)
            fwrite(score, sizeof(Score), 1, tmpPtr);

        fclose(filePtr);
        return tmpPtr;
    }

    ////////////////////////////////////////////////////////////
    bool addScore(std::string userName, int points)
    {
        auto score = new Score;

        FILE *filePtr = reWriteScores();
        if (filePtr == NULL)
            return false;

        std::copy(userName.begin(), userName.end(), score->username);
        score->id = getNewId();
        score->points = points;

        fwrite(score, sizeof(Score), 1, filePtr);
        fclose(filePtr);
        makeTempMainDb();

        return true;
    }

    ////////////////////////////////////////////////////////////
    bool removeScoreById(int id)
    {
        auto *score = new Score;
        FILE *filePtr = fopen(SCORE_DB_FILE_PATH, "rb");
        FILE *tmpPtr = fopen(SCORE_TEMP_DB_FILE_PATH, "wb");

        if (filePtr == NULL || tmpPtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (bool removeScoreById(int id))" << std::endl;
            return false;
        }

        while (fread(score, sizeof(Score), 1, filePtr) != 0)
        {
            if (score->id != id)
                fwrite(score, sizeof(Score), 1, tmpPtr);
        }

        fclose(filePtr);
        fclose(tmpPtr);
        makeTempMainDb();
        return true;
    }

    ////////////////////////////////////////////////////////////
    bool loadById(Score* score, int id)
    {
        FILE *filePtr = fopen(SCORE_DB_FILE_PATH, "rb");

        if (filePtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (bool loadById(Score* score, int id))" << std::endl;
            return false;
        }

        while (fread(score, sizeof(Score), 1, filePtr) != 0)
        {
            if (score->id == id)
            {
                fclose(filePtr);
                return true;
            }
        }

        fclose(filePtr);
        return false;
    }

    ////////////////////////////////////////////////////////////
    int getNewId()
    {
        int id = 1;
        auto *score = new Score;
        FILE *filePtr = fopen(SCORE_DB_FILE_PATH, "rb");

        if (filePtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (int getNewId())" << std::endl;
            return false;
        }

        while (fread(score, sizeof(Score), 1, filePtr) != 0)
        {
            if (score->id != id)
                return id;
            id++;
        }

        return id;
    }

    ////////////////////////////////////////////////////////////
    bool purgeScoreDb()
    {
#ifdef __WINDOWS__
        std::string command = "del ", command2 = "del ", command3 = "echo > ";
        command.append(SCORE_TEMP_DB_FILE_PATH);
        command2.append(SCORE_DB_FILE_PATH);
        command3.append(SCORE_DB_FILE_PATH);
        system(command.c_str());
        system(command2.c_str());
        system(command3.c_str());
#endif
#ifdef __UNIX__
        std::string command = "rm ", command2 = "rm ", command3 = "echo > ";
        command.append(SCORE_TEMP_DB_FILE_PATH);
        command2.append(SCORE_DB_FILE_PATH);
        command3.append(SCORE_DB_FILE_PATH);
        system(command.c_str());
        system(command2.c_str());
        system(command3.c_str());
#endif
        MiscUtils::clearScreen();
        return true;
    }
}
