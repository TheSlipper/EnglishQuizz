////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////
#define DB_FILE_PATH "question_db.bin"
#define TEMP_DB_FILE_PATH "question_db.temp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <stdio.h>
#include <iostream>
#include "../DEFINITIONS.hpp"


////////////////////////////////////////////////////////////
/// \brief DataManagement namespace to moduł zawierający
///          funkcje zarządzające bazą danych pytań.
///
////////////////////////////////////////////////////////////
namespace DataManagement
{

    enum CorrectAnswer {answerA, answerB, answerC, answerD}; ///< enum zawierający możliwe poprawne odpowiedzi

    ////////////////////////////////////////////////////////////
    /// \brief Zawiera informacje na temat pojedyńczego pytania
    ///
    /// \memberof int question_id unikatowy identyfikator pytania
    ///
    ///
    /// \memberof char question[200] treść pytania
    ///
    /// \memberof char answerA[100] treść odpowiedzi a
    ///
    /// \memberof char answerB[100] treść odpowiedzi b
    ///
    /// \memberof char answerC[100] treść odpowiedzi c
    ///
    /// \memberof char answerD[100] treść odpowiedzi d
    ///
    /// \memberof CorrectAnswer correctAnswer enum poprawnej odpowiedzi
    ///
    ////////////////////////////////////////////////////////////
    struct QuestionEntry
    {
        int question_id;
        char question[200];
        char answerA[100], answerB[100], answerC[100], answerD[100];
        CorrectAnswer correctAnswer;
    };

    ////////////////////////////////////////////////////////////
    /// \brief Funkcja z inną implementacją dla systemów UNIXowych
    ///         i windowsowych. Zmienia nazwę pliku z DB_FILE_PATH na
    ///         TEMP_DB_FILE_PATH.
    ///
    ////////////////////////////////////////////////////////////
    void makeTempMainDb();

    ////////////////////////////////////////////////////////////
    /// \brief Przepisuje pytania do pliku i zwraca wskaźnik do
    ///         pliku tymczasowego (po użyciu podmienić nazwę)
    ///
    ////////////////////////////////////////////////////////////
    FILE* reWriteQuestions();

    ////////////////////////////////////////////////////////////
    /// \brief Dodaje nowe pytanie do bazy danych
    ///
    /// \param QuestionEntry *entry pytanie które będzie dodawane
    ///
    ////////////////////////////////////////////////////////////
    bool addQuestion(QuestionEntry *entry);

    ////////////////////////////////////////////////////////////
    /// \brief Usuwa pytanie z bazy danych o podanym id
    ///
    /// \param int id id pytania do usunięcia
    ///
    ////////////////////////////////////////////////////////////
    bool deleteQuestionById(int id);

    ////////////////////////////////////////////////////////////
    /// \brief Uaktualnia pytanie o podanym id
    ///
    ////////////////////////////////////////////////////////////
    bool updateQuestion(int id);

    ////////////////////////////////////////////////////////////
    /// \brief Wyczyszcza całą bazę z danych pytań (usuwa je wszystkie)
    ///
    ////////////////////////////////////////////////////////////
    void purgeQuestions();

    ////////////////////////////////////////////////////////////
    /// \brief Eksportuje pytania do pliku o podanej nazwie
    ///
    /// \param std::string fileName nazwa pliku
    ///
    ////////////////////////////////////////////////////////////
    void exportQuestions(std::string fileName);

    ////////////////////////////////////////////////////////////
    /// \brief Importuje pytania do pliku o podanej nazwie
    ///
    /// \param std::string filePath ścieżka do pliku
    ///
    ////////////////////////////////////////////////////////////
    void importQuestions(std::string filePath);

    ////////////////////////////////////////////////////////////
    /// \brief Czyta pierwsze pytanie z bazy danych
    ///
    /// \param QuestionEntry *entry wskaźnik do miejsca zapisu pytania
    ///
    ////////////////////////////////////////////////////////////
    bool readQuestion(QuestionEntry *entry);

    ////////////////////////////////////////////////////////////
    /// \brief Czyta pierwsze pytanie z bazy danych
    ///
    /// \param QuestionEntry *entry wskaźnik do miejsca zapisu pytania
    ///
    /// \param int id id pytania do pozyskania
    ///
    ////////////////////////////////////////////////////////////
    bool getQuestionById(QuestionEntry *entry, int id);
}