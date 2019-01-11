////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ManageData.hpp"

namespace DataManagement
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
            std::cerr << "Error creating file or accessing it! (bool deleteQuestionById(int id))" << std::endl;
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
        // TODO: Re-write previous questions (re-write function which returns FILE*)
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
        // TODO: Test if this works
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
    }

    ////////////////////////////////////////////////////////////
    void updateQuestion()
    {
        // TODO:
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
    void exportQuestions(std::string fileName)
    {
        // TODO: (Maybe just copy the file)
    }

    ////////////////////////////////////////////////////////////
    void importQuestions(std::string filePath)
    {
        // TODO:
    }

    ////////////////////////////////////////////////////////////
    bool readQuestion(QuestionEntry *entry)
    {
        FILE *filePtr = fopen("testFile.bin", "rb");
        if (filePtr == NULL)
        {
            std::cerr << "Error creating file or accessing it! (bool readQuestion(QuestionEntry *entry))" << std::endl;
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
}