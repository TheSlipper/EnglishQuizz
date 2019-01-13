////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ManageQuestions.hpp"

namespace QuestionManagement
{
    ////////////////////////////////////////////////////////////
    void makeTempMainDb()
    {
#ifdef __WINDOWS__
        // TODO: Implement moving files for windows
#endif
#ifdef __UNIX__
        std::string command = "mv ";
        command.append(TEMP_DB_FILE_PATH);
        command.append(" ");
        command.append(DB_FILE_PATH);
        system(command.c_str());
#endif
    }

    ////////////////////////////////////////////////////////////
    FILE* reWriteQuestions()
    {
        QuestionEntry *entry = new QuestionEntry;
        FILE *filePtr = fopen(DB_FILE_PATH, "rb");
        FILE *tmpPtr = fopen(TEMP_DB_FILE_PATH, "wb");

        if (filePtr == NULL || tmpPtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (FILE* reWriteQuestions())" << std::endl;
            return nullptr;
        }

        while(fread(entry, sizeof(QuestionEntry), 1, filePtr) != 0)
            fwrite(entry, sizeof(QuestionEntry), 1, tmpPtr);
        fclose(filePtr);

        return tmpPtr;
    }

    ////////////////////////////////////////////////////////////
    bool addQuestion(QuestionEntry *entry)
    {
        FILE *filePtr = reWriteQuestions();
        if (filePtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (bool addQuestion())" << std::endl;
            return false;
        }

        fwrite(entry, sizeof(QuestionEntry), 1, filePtr);
        fclose(filePtr);
        makeTempMainDb();

        return true;
    }

    ////////////////////////////////////////////////////////////
    bool deleteQuestionById(int id)
    {
        QuestionEntry *entry = new QuestionEntry;
        FILE *filePtr = fopen(DB_FILE_PATH, "rb");
        FILE *tmpPtr = fopen(TEMP_DB_FILE_PATH, "wb");

        if (filePtr == NULL || tmpPtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (bool deleteQuestionById(int id))" << std::endl;
            return false;
        }

        while(fread(entry, sizeof(QuestionEntry), 1, filePtr) != 0)
        {
            if (entry->question_id != id)
                fwrite(entry, sizeof(QuestionEntry), 1, tmpPtr);
        }

        fclose(filePtr);
        fclose(tmpPtr);
        // Zmiana nazwy jest o wiele szybsza niż pisanie pliku na nowo
        makeTempMainDb();
        return true;
    }

    ////////////////////////////////////////////////////////////
    void purgeQuestions()
    {
#ifdef __WINDOWS__
        // TODO: Implement moving files for windows
#endif
#ifdef __UNIX__
        std::string command1 = "rm ", command2 = "rm ", command3 = "echo > ", command4 = "echo > ";
        command1.append(TEMP_DB_FILE_PATH);
        command2.append(DB_FILE_PATH);
        command3.append(TEMP_DB_FILE_PATH);
        command4.append(DB_FILE_PATH);
        system(command1.c_str());
        system(command2.c_str());
        system(command3.c_str());
        system(command4.c_str());
#endif
    }

    ////////////////////////////////////////////////////////////
    void exportQuestions(std::string filePath)
    {
#ifdef __WINDOWS__
        // TODO: Implement exporting database for windows
#endif
#ifdef __UNIX__
        std::string command1 = "cp ";
        command1.append(DB_FILE_PATH);
        command1.append(" ");
        command1.append(filePath);
        system(command1.c_str());
#endif
    }

    ////////////////////////////////////////////////////////////
    void importQuestions(std::string filePath)
    {
#ifdef __WINDOWS__
        // TODO: Implement importing database for windows
#endif
#ifdef __UNIX__
        std::string command1 = "cp ";
        command1.append(filePath);
        command1.append(" ");
        command1.append(DB_FILE_PATH);
        system(command1.c_str());
#endif
    }

    ////////////////////////////////////////////////////////////
    bool getQuestion(QuestionEntry *entry)
    {
        FILE *filePtr = fopen("testFile.bin", "rb");
        if (filePtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (bool getQuestion(QuestionEntry *entry))" << std::endl;
            return false;
        }
        fread(entry, sizeof(QuestionEntry), 1, filePtr);
        fclose(filePtr);
        return true;
    }

    ////////////////////////////////////////////////////////////
    bool getQuestionById(QuestionEntry *entry, int id)
    {
        FILE *filePtr = fopen(DB_FILE_PATH, "rb");
        if (filePtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (bool getQuestionById(QuestionEntry *entry, int id))" << std::endl;
            return false;
        }

        while(fread(entry, sizeof(QuestionEntry), 1, filePtr) != 0)
        {
            if (entry->question_id == id)
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
        auto *entry = new QuestionEntry;
        int prev_val = 0;

        FILE *filePtr = fopen(DB_FILE_PATH, "rb");
        if (filePtr == NULL)
        {
            std::cerr << "Error accessing file! (int getNewId())" << std::endl;
            return NULL;
        }

        while(fread(entry, sizeof(QuestionEntry), 1, filePtr) != 0)
        {
            prev_val++;
        }
        fclose(filePtr);

        if (strcmp(entry->question, "") && prev_val == 0)
            return 1;

        prev_val++;
        return prev_val;
    }
}