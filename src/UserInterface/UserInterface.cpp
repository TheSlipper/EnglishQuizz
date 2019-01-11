////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "UserInterface.hpp"

namespace UI
{
    ////////////////////////////////////////////////////////////
    void incorrectOptionEntered()
    {
        MiscUtils::clearScreen();
        std::cerr << "Niepoprawna opcja! Spróbuj jeszcze raz!" << std::endl;
    }

    ////////////////////////////////////////////////////////////
    void displayMainMenu(UserManagement::User *user)
    {
        MiscUtils::clearScreen();
        while (true)
        {
            std::unique_ptr<int> choice = std::make_unique<int>();
            std::cout << "===============================" << std::endl;
            std::cout << "========= Menu Główne =========" << std::endl;
            if (user->group == UserManagement::PrivilageGroup::teacher)
                std::cout << "1. Panel administracyjny (nauczyciela)" << std::endl;
            else
                std::cout << "1. Zobacz wyniki poprzednich testów" << std::endl;
            std::cout << "2. Napisz test" << std::endl;
            std::cout << "3. Ustawienia programu" << std::endl;
            std::cout << "4. Wyloguj się" << std::endl;
            std::cout << "5. Wyłącz program" << std::endl;
            std::cout << ">";
            std::cin >> *choice;

            switch (*choice)
            {
                case 1:
                    if (user->group == UserManagement::PrivilageGroup::teacher)
                        displayAdminOptions();
                    else
                        displayScores(user);
                    break;
                case 2:
                    // TODO:
                    break;
                case 3:
                    displaySettings();
                    break;
                case 4:
                    UserManagement::logOut(user);
                    return;
                case 5:
                    exit(0);
                default:
                    incorrectOptionEntered();
            }
        }
    }

    ////////////////////////////////////////////////////////////
    void displayAdminOptions()
    {
        MiscUtils::clearScreen();
        while (true)
        {
            std::unique_ptr<int> choice = std::make_unique<int>();
            std::cout << "===============================" << std::endl;
            std::cout << "==== Opcje Administracyjne ====" << std::endl;
            std::cout << "1. Zarządzaj użytkownikami" << std::endl;
            std::cout << "2. Wyświetl oceny wszystkich studentów" << std::endl;
            std::cout << "3. Wyświetl oceny konkretnego studenta" << std::endl;
            std::cout << "4. Wyświetl panel zarządzania pytaniami" << std::endl;
            std::cout << "5. Wróć do głównego menu" << std::endl;
            std::cout << ">";
            std::cin >> *choice;

            switch(*choice)
            {
                case 1:
                    displayUsrMgmtPanel();
                    break;
                case 2:
                    displayAllScores();
                    break;
                case 3:
                    displayScoresPanel();
                    break;
                case 4:
                    displayQuestionMgmtPanel();
                    break;
                case 5:
                    return;
                default:
                    incorrectOptionEntered();
                    break;
            }

        }
    }

    ////////////////////////////////////////////////////////////
    void displayQuestionMgmtPanel()
    {
        MiscUtils::clearScreen();
        while (true)
        {
            std::unique_ptr<int> choice = std::make_unique<int>();
            std::cout << "===============================" << std::endl;
            std::cout << "==== Zarządzanie pytaniami ====" << std::endl;
            std::cout << "1. Wyświetl wszystkie pytania" << std::endl;
            std::cout << "2. Dodaj pytanie" << std::endl;
            std::cout << "3. Edytuj pytanie" << std::endl;
            std::cout << "4. Usuń pytanie" << std::endl;
            std::cout << "5. Usuń wszystkie pytania" << std::endl;
            std::cout << "6. Eksportuj bazę pytań" << std::endl;
            std::cout << "7. Importuj bazę pytań" << std::endl;
            std::cout << "8. Wróć do opcji administracyjnych" << std::endl;
            std::cout << ">";
            std::cin >> *choice;

            switch(*choice)
            {
                case 1:
                    printAllQuestions();
                    break;
                case 2:
                    addQuestionPanel();
                    break;
                case 3:
                    // TODO:
                    break;
                case 4:
                    deleteQuestionPanel();
                    break;
                case 5:
                    DataManagement::purgeQuestions();
                    break;
                case 6:
                    displayExportDBPanel();
                    break;
                case 7:
                    displayImportDBPanel();
                    break;
                case 8:
                    return;
                default:
                    incorrectOptionEntered();
                    break;
            }
        }
    }

    ////////////////////////////////////////////////////////////
    void addQuestionPanel()
    {
        auto entry = new DataManagement::QuestionEntry;
        char correct_answer;
        entry->question_id = DataManagement::getNewId();
        MiscUtils::clearScreen();
        std::cout << "===============================" << std::endl;
        std::cout << "====== Dodawanie pytania ======" << std::endl;
        std::cout << "Nowe nadane przez system ID: " << entry->question_id << std::endl; //id here
        std::cout << "1. Wprowadź pytanie: ";
        std::cin >> entry->question; // TODO: getline() bo tutaj jak będzie spacja to lipa iirc

        std::cout << "2. Wprowadź odpowiedź A: ";
        std::cin >> entry->answerA;
        std::cout << "3. Wprowadź odpowiedź B: ";
        std::cin >> entry->answerB;
        std::cout << "4. Wprowadź odpowiedź C: ";
        std::cin >> entry->answerC;
        std::cout << "5. Wprowadź odpowiedź D: ";
        std::cin >> entry->answerD;

        std::cout << "5. Wprowadź poprawną odpowiedź (A/B/C/D): ";
        std::cin >> correct_answer;

        switch(tolower(correct_answer))
        {
            case 'a':
                entry->correctAnswer = DataManagement::CorrectAnswer::answerA;
                break;
            case 'b':
                entry->correctAnswer = DataManagement::CorrectAnswer::answerB;
                break;
            case 'c':
                entry->correctAnswer = DataManagement::CorrectAnswer::answerC;
                break;
            case 'd':
                entry->correctAnswer = DataManagement::CorrectAnswer::answerD;
                break;
            default:
                MiscUtils::clearScreen();
                std::cerr << "Zła podana wartość. Pytanie nie zostanie dodane" << std::endl;
                return;
        }

        MiscUtils::clearScreen();
        if (DataManagement::addQuestion(entry))
            std::cout << "Dodano pomyślnie nowe pytanie do bazy danych!" << std::endl;
        else
            std::cout << "Napotkany został błąd podczas dodawania pytania. Nie dodano pytania do bazy danych." << std::endl;

    }

    ////////////////////////////////////////////////////////////
    void editQuestionPanel()
    {
        int question_num, decision;
        auto *question = new DataManagement::QuestionEntry;
        std::cout << "===============================" << std::endl;
        std::cout << "===== Edytowanie Pytania ======" << std::endl;
        std::cout << "Wprowadź numer id pytania: ";
        std::cin >> question_num;

        DataManagement::getQuestionById(question, question_num);
        if (question == NULL)
        {
            MiscUtils::clearScreen();
            std::cerr << "Podany niepoprawny numer ID!" << std::endl;
            return;
        }

        std::cout << "===============================" << std::endl;
        std::cout << "===== Edytowanie Pytania ======" << std::endl;
        std::cout << "ID: " << question->question_id << "\r\nPytanie: " << question->question;
        std::cout << "\r\n\r\nOdpowiedź A: " << question->answerA << "\r\nOdpowiedź B: " << question->answerB;
        std::cout << "\r\nOdpowiedź C: " << question->answerC << "\r\nOdpowiedź D: " << question->answerD;
        std::cout << "\r\n\r\nPoprawna odpowiedź: " << question->correctAnswer << std::endl << std::endl;
        std::cout << "Co chcesz zedytować?(1. Pytanie, 2. Odpowiedź A, 3. Odpowiedź B, 4. Odpowiedź C, 5. Odpowiedź D" ;
        std::cout << ", 6. Poprawna odpowiedź)" << std::endl << ">";
        std::cin >> decision;

//        switch (decision)
//        {
//            case 1:
//
//        }

    }

    ////////////////////////////////////////////////////////////
    void deleteQuestionPanel()
    {
        int id;
        std::cout << "===============================" << std::endl;
        std::cout << "====== Usuwanie Pytania =======" << std::endl;
        std::cout << "Wprowadź ID pytania do usunięcia: " << std::endl;
        std::cin >> id;
        MiscUtils::clearScreen();
        if(DataManagement::deleteQuestionById(id))
            std::cout << "Pytanie o ID " << id << " zostało usunięte pomyślnie";
        else
            std::cerr << "Nie udało się usunąć pytania o ID " << id << std::endl;
    }

    void displayExportDBPanel()
    {
        std::string relativePath;
        std::cout << "===============================" << std::endl;
        std::cout << "== Eksportowanie bazy danych ==" << std::endl;
        std::cout << "Podaj ścieżkę relatywną do której chcesz \r\nwyeksportować dane (uwzględnij na końcu nazwę pliku): ";
        std::cin >> relativePath;
        DataManagement::exportQuestions(relativePath);
    }

    void displayImportDBPanel()
    {
        std::string relativePath;
        char decision;
        std::cout << "===============================" << std::endl;
        std::cout << "== Importowanie bazy danych ==" << std::endl;
        std::cout << "Czy na pewno chcesz zaimportować bazę danych?\r\nZastąpi to twoją aktualną bazę danych (T/N):";
        std::cin >> decision;
        if (tolower(decision)== 'n')
            return;
        MiscUtils::clearScreen();
        std::cout << "===============================" << std::endl;
        std::cout << "== Importowanie bazy danych ==" << std::endl;
        std::cout << "Podaj ścieżkę relatywną z której chcesz \r\nzaimportować dane (uwzględnij na końcu nazwę pliku): ";
        std::cin >> relativePath;
        DataManagement::importQuestions(relativePath);
    }

    ////////////////////////////////////////////////////////////
    void displayUsrMgmtPanel()
    {
        MiscUtils::clearScreen();
        while (true)
        {
            std::unique_ptr<int> choice = std::make_unique<int>();
            std::cout << "===============================" << std::endl;
            std::cout << "== Zarządzanie użytkownikami ==" << std::endl;
            std::cout << "1. Dodaj użytkownika" << std::endl;
            std::cout << "2. Edytuj użytkownika" << std::endl;
            std::cout << "3. Usuń użytkownika" << std::endl;
            std::cout << "4. Wróć do opcji administracyjnych" << std::endl;
            std::cout << ">";
            std::cin >> *choice;
            switch(*choice)
            {
                case 1:
                    displayAddUserPanel();
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    return;
                default:
                    incorrectOptionEntered();
                    break;
            }
            break;
        }
    }

    ////////////////////////////////////////////////////////////
    void displayAllScores()
    {
        // TODO:
    }

    ////////////////////////////////////////////////////////////
    void displayScores(UserManagement::User *user)
    {
        // TODO:
    }

    ////////////////////////////////////////////////////////////
    void displayScoresPanel()
    {
        // TODO:
    }

    ////////////////////////////////////////////////////////////
    void displaySettings()
    {
        // TODO:
    }

    ////////////////////////////////////////////////////////////
    void displayLoginScreen()
    {
        auto *user = new UserManagement::User;

        while(true)
        {
            MiscUtils::clearScreen();
            std::cout << "===============================" << std::endl;
            std::cout << "========= Zaloguj się =========" << std::endl;
            std::cout << "= Login: ";
            std::cin >> user->username;
            std::cout << "= Password: ";
            std::cin >> user->password;

            if (UserManagement::logIn(user->username, user->password))
                displayMainMenu(user);
            else
            {
                std::cout << "Niepoprawne dane logowania!" << std::endl;
                std::cout << "Spróbować się zalogować jeszcze raz? (t/n): ";
                if (getchar() == 't')
                    return;
                else
                    exit(0);
            }
        }
    }

    ////////////////////////////////////////////////////////////
    void displayAddUserPanel()
    {
        std::string name, surname;
        std::cout << "Wprowadź imię: " << std::endl;
        std::cin >> name;
        std::cout << "Wprowadź nazwisko: " << std::endl;
        std::cin >> surname;

        if(UserManagement::addUser(name, surname))
            std::cout << "Pomyślnie dodano użytkownika" << std::endl;
        else
            std::cerr << "Błąd przy dodawaniu użytkownika" << std::endl;
    }

    ////////////////////////////////////////////////////////////
    void displayEditUserPanel()
    {
        UserManagement::User *user;
        // TODO:
    }

    ////////////////////////////////////////////////////////////
    void displayDeleteUserPanel()
    {
        // TODO:
    }

    ////////////////////////////////////////////////////////////
    void printAllQuestions()
    {
        std::cout << "\r\n\r\n\r\n" << std::endl;
        auto *question = new DataManagement::QuestionEntry;
        // TODO: Finish this function
        for (int i=1; ; i++)
        {
            if (DataManagement::getQuestionById(question, i))
            {
                std::cout << "ID: " << question->question_id << "\r\nPytanie: " << question->question;
                std::cout << "\r\n\r\nOdpowiedź A: " << question->answerA << "\r\nOdpowiedź B: " << question->answerB;
                std::cout << "\r\nOdpowiedź C: " << question->answerC << "\r\nOdpowiedź D: " << question->answerD;
                std::cout << "\r\n\r\nPoprawna odpowiedź: " << question->correctAnswer << std::endl << std::endl;
            }
            else if (DataManagement::getQuestionById(question, i++))
                continue;
            else
                break;
        }
    }
}