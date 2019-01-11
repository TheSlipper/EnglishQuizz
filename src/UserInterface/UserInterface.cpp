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
            std::cout << "5. Wróć do opcji administracyjnych" << std::endl;
            std::cout << ">";
            std::cin >> *choice;

            switch(*choice)
            {
                case 1:
                    printAllQuestions();
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
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
        auto *question = new DataManagement::QuestionEntry;
        // TODO: Finish this function
        for ()
        {

        }
    }
}