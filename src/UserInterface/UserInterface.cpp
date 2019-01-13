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
            std::cout << "3. Ustawienia" << std::endl;
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
                        printMyScores(user);
                    break;
                case 2:
                    displayTestScreen(user);
                    break;
                case 3:
                    displaySettingsPanel(user);
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
            std::cout << "5. Wyczyść wszystkie oceny" << std::endl;
            std::cout << "6. Wróć do głównego menu" << std::endl;
            std::cout << ">";
            std::cin >> *choice;

            switch(*choice)
            {
                case 1:
                    displayUsrMgmtPanel();
                    break;
                case 2:
                    printAllScores();
                    break;
                case 3:
                    displaySpecificUserScorePanel();
                    // TODO:
                    break;
                case 4:
                    displayQuestionMgmtPanel();
                    break;
                case 5:
                    ScoreManagement::purgeScoreDb();
                    break;
                case 6:
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
                    editQuestionPanel();
                    break;
                case 4:
                    deleteQuestionPanel();
                    break;
                case 5:
                    QuestionManagement::purgeQuestions();
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
        auto entry = new QuestionManagement::QuestionEntry;
        char correct_answer;
        entry->question_id = QuestionManagement::getNewId();
        MiscUtils::clearScreen();
        std::cout << "===============================" << std::endl;
        std::cout << "====== Dodawanie pytania ======" << std::endl;
        std::cout << "Nowe nadane przez system ID: " << entry->question_id << std::endl; //id here
        std::cout << "1. Wprowadź pytanie: ";
        std::cin.ignore();
        std::cin.getline(entry->question, 200);

        std::cout << "2. Wprowadź odpowiedź A: ";
        std::cin.getline(entry->answerA, 100);
        std::cout << "3. Wprowadź odpowiedź B: ";
        std::cin.getline(entry->answerB, 100);
        std::cout << "4. Wprowadź odpowiedź C: ";
        std::cin.getline(entry->answerC, 100);
        std::cout << "5. Wprowadź odpowiedź D: ";
        std::cin.getline(entry->answerD, 100);

        std::cout << "5. Wprowadź poprawną odpowiedź (A/B/C/D): ";
        std::cin >> correct_answer;

        switch(tolower(correct_answer))
        {
            case 'a':
                entry->correctAnswer = QuestionManagement::CorrectAnswer::answerA;
                break;
            case 'b':
                entry->correctAnswer = QuestionManagement::CorrectAnswer::answerB;
                break;
            case 'c':
                entry->correctAnswer = QuestionManagement::CorrectAnswer::answerC;
                break;
            case 'd':
                entry->correctAnswer = QuestionManagement::CorrectAnswer::answerD;
                break;
            default:
                MiscUtils::clearScreen();
                std::cerr << "Zła podana wartość. Pytanie nie zostanie dodane" << std::endl;
                return;
        }

        MiscUtils::clearScreen();
        if (QuestionManagement::addQuestion(entry))
            std::cout << "Dodano pomyślnie nowe pytanie do bazy danych!" << std::endl;
        else
            std::cout << "Napotkany został błąd podczas dodawania pytania. Nie dodano pytania do bazy danych." << std::endl;

    }

    ////////////////////////////////////////////////////////////
    void editQuestionPanel()
    {
        int question_num;
        char odp;
        auto *question = new QuestionManagement::QuestionEntry;
        question->question_id = INT32_MAX;
        std::cout << "===============================" << std::endl;
        std::cout << "===== Edytowanie Pytania ======" << std::endl;
        std::cout << "Wprowadź numer id pytania: ";
        std::cin >> question_num;

        QuestionManagement::getQuestionById(question, question_num);
        if (question->question_id == INT32_MAX)
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

        std::cout << "Wprowadź pytanie: ";
        std::cin.ignore();
        std::cin.getline(question->question, 200);

        std::cout <<"Wprowadź odpowiedź A: ";
        std::cin.getline(question->answerA, 100);
        std::cout <<"Wprowadź odpowiedź B: ";
        std::cin.getline(question->answerB, 100);
        std::cout <<"Wprowadź odpowiedź C: ";
        std::cin.getline(question->answerC, 100);
        std::cout <<"Wprowadź odpowiedź D: ";
        std::cin.getline(question->answerD, 100);

        std::cout << "Która odpowiedź jest poprawna (A/B/C/D)? : ";
        std::cin >> odp;

        MiscUtils::clearScreen();
        switch (tolower(odp))
        {
            case 'a':
                question->correctAnswer = QuestionManagement::CorrectAnswer::answerA;
                break;
            case 'b':
                question->correctAnswer = QuestionManagement::CorrectAnswer::answerA;
                break;
            case 'c':
                question->correctAnswer = QuestionManagement::CorrectAnswer::answerA;
                break;
            case 'd':
                question->correctAnswer = QuestionManagement::CorrectAnswer::answerA;
                break;
            default:
                std::cerr << "Niepoprawna odpowiedź wpisana! Pytanie nie zostało nadpisane!" << std::endl;
                break;
        }

        QuestionManagement::deleteQuestionById(question_num);
        QuestionManagement::addQuestion(question);
        std::cout << "Pomyślnie zedytowano pytanie o ID " << question_num << std::endl;
        std::cin.clear();
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
        if(QuestionManagement::deleteQuestionById(id))
            std::cout << "Pytanie o ID " << id << " zostało usunięte pomyślnie";
        else
            std::cerr << "Nie udało się usunąć pytania o ID " << id << std::endl;
    }

    ////////////////////////////////////////////////////////////
    void displayExportDBPanel()
    {
        std::string relativePath;
        std::cout << "===============================" << std::endl;
        std::cout << "== Eksportowanie bazy danych ==" << std::endl;
        std::cout << "Podaj ścieżkę relatywną do której chcesz \r\nwyeksportować dane (uwzględnij na końcu nazwę pliku): ";
        std::cin >> relativePath;
        QuestionManagement::exportQuestions(relativePath);
    }

    ////////////////////////////////////////////////////////////
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
        QuestionManagement::importQuestions(relativePath);
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
            std::cout << "1. Pokaż wszystkich użytkowników" << std::endl;
            std::cout << "2. Dodaj użytkownika" << std::endl;
            std::cout << "3. Usuń użytkownika" << std::endl;
            std::cout << "4. Wróć do opcji administracyjnych" << std::endl;
            std::cout << ">";
            std::cin >> *choice;
            switch(*choice)
            {
                case 1:
                    printAllUsers();
                    break;
                case 2:
                    displayAddUserPanel();
                    break;
                case 3:
                    displayDeleteUserPanel();
                    break;
                case 4:
                    return;
                default:
                    incorrectOptionEntered();
                    break;
            }
        }
    }

    ////////////////////////////////////////////////////////////
    void printAllScores()
    {
        MiscUtils::clearScreen();
        auto *score = new ScoreManagement::Score;
        int id = 1;
        while (ScoreManagement::loadById(score, id))
        {
            std::cout << "ID oceny: " << id << std::endl;
            std::cout << "Nickname: " << score->username << std::endl;
            std::cout << "Punkty: [" << score->points << "/20]" << std::endl;
            std::cout << std::endl << std::endl;
            id++;
        }
    }

    ////////////////////////////////////////////////////////////
    void printMyScores(UserManagement::User *user)
    {
        MiscUtils::clearScreen();
        auto *score = new ScoreManagement::Score;
        int id = 1;
        while (ScoreManagement::loadById(score, id))
        {
            std::string helperUsername1 = score->username;
            std::string helperUsername2 = user->username;
            if (helperUsername1.compare(helperUsername2) == 0)
            {
                std::cout << "ID oceny: " << id << std::endl;
                std::cout << "Nickname: " << score->username << std::endl;
                std::cout << "Punkty: [" << score->points << "/20]" << std::endl;
                std::cout << std::endl << std::endl;
            }
            id++;
        }
    }

    ////////////////////////////////////////////////////////////
    void displaySpecificUserScorePanel()
    {
        MiscUtils::clearScreen();
        std::string username;
        auto *score = new ScoreManagement::Score;
        int index = 1;
        std::cout << "Podaj nickname użytkownika: ";
        std::cin >> username;

        MiscUtils::clearScreen();
        while (ScoreManagement::loadById(score, index))
        {
            std::string tempUsername = score->username;
            if (tempUsername.compare(username) == 0)
            {
                std::cout << "ID: " << score->id << std::endl;
                std::cout << "Ocena: [" << score->points << "/20]" << std::endl;
            }
            index++;
        }
    }

    ////////////////////////////////////////////////////////////
    void displaySettingsPanel(UserManagement::User *user)
    {
        MiscUtils::clearScreen();
        while (true)
        {
            std::unique_ptr<int> choice = std::make_unique<int>();
            std::cout << "===============================" << std::endl;
            std::cout << "========== Ustawienia =========" << std::endl;
            std::cout << "1. Zmień hasło zalogowanego użytkownika" << std::endl;
            std::cout << "2. Wróć do głównego menu" << std::endl;
            std::cout << ">";
            std::cin >> *choice;

            MiscUtils::clearScreen();
            switch(*choice)
            {
                case 1:
                    displayEditPasswordPanel(user);
                    break;
                case 2:
                    return;
                default:
                    incorrectOptionEntered();
                    break;
            }
        }
    }

    ////////////////////////////////////////////////////////////
    void displayLoginScreen()
    {
        while(true)
        {
            auto *user = new UserManagement::User;
            MiscUtils::clearScreen();
            std::cout << "===============================" << std::endl;
            std::cout << "========= Zaloguj się =========" << std::endl;
            std::cout << "= Login: ";
            std::cin >> user->username;
            std::cout << "= Password: ";
            std::cin >> user->password;

            if (UserManagement::logIn(user->username, user->password, user))
                displayMainMenu(user);
            else
            {
                char decision;
                std::cout << "Niepoprawne dane logowania!" << std::endl;
                std::cout << "Spróbować się zalogować jeszcze raz? (t/n): ";
                std::cin >> decision;
                if (tolower(decision) != 't')
                    exit(0);
            }
        }
    }

    ////////////////////////////////////////////////////////////
    void displayAddUserPanel()
    {
        MiscUtils::clearScreen();
        std::string name, password;
        int group;
        std::cout << "Wprowadź nowy login: ";
        std::cin >> name;
        std::cout << "Wprowadź nowe hasło: ";
        std::cin >> password;
        std::cout << "Wybierz grupę przywilejów (1. Teacher, 2. Student): ";
        std::cin >> group;


        MiscUtils::clearScreen();
        if(UserManagement::addUser(name, password, (UserManagement::PrivilageGroup)group))
            std::cout << "Pomyślnie dodano użytkownika" << std::endl;
        else
            std::cerr << "Błąd przy dodawaniu użytkownika" << std::endl;
    }

    ////////////////////////////////////////////////////////////
    void displayEditPasswordPanel(UserManagement::User *user)
    {
        MiscUtils::clearScreen();
        std::string login, newPasswd;
        login = user->username;

        if (!UserManagement::getUserByNickname(user, login))
        {
            std::cerr << "Nie znaleziono użytkownika o podanym nickname'ie!" << std::endl;
            return;
        }

        MiscUtils::clearScreen();
        std::cout << "Podaj nowe hasło: ";
        std::cin >> newPasswd;

        MiscUtils::clearScreen();
        std::copy(newPasswd.begin(), newPasswd.end(), user->password);
        UserManagement::removeUser(login);
        UserManagement::addUser(login, newPasswd, user->group);
        std::cout << "Pomyślnie zmieniono hasło!" << std::endl;
    }

    ////////////////////////////////////////////////////////////
    void displayDeleteUserPanel()
    {
        MiscUtils::clearScreen();
        std::string username;
        char final_decision;

        std::cout << "Wprowadź login użytkownika do skasowania: ";
        std::cin >> username;
        std::cout << "Czy na pewno chcesz skasować użytkownika?\r\nNie da się tego później cofnąć (T/N):";
        std::cin >> final_decision;

        MiscUtils::clearScreen();
        if (tolower(final_decision) == 'N')
        {
            std::cout << "Nie skasowano użytkownika " << username << std::endl;
            return;
        }
        else
        {
            if (UserManagement::removeUser(username))
                std::cout << "Pomyślnie skasowano użytkownika " << username << std::endl;
            else
                std::cerr << "Błąd podczas usuwania użytkownika!" << std::endl;
        }
    }

    ////////////////////////////////////////////////////////////
    void displayDeleteCurrentUser()
    {
        // TODO:
    }

    ////////////////////////////////////////////////////////////
    void displayTestScreen(UserManagement::User *user)
    {
        MiscUtils::clearScreen();
        char readyOrNot;
        int points = 0;
        int askedQuestions[20];
        std::string username = user->username;

        std::cout << "===============================" << std::endl;
        std::cout << "============= Test ============" << std::endl;
        std::cout << "Przed tobą dwadzieścia pytań z angielskiego" << std::endl;
        std::cout << "Masz nieograniczony czas na ich rozwiązanie ale możesz tylko" << std::endl;
        std::cout << "raz podać odpowiedź - nie możesz wrócić do poprzedniego pytania" << std::endl;
        std::cout << "Jest to test wielokrotnego wyboru (A/B/C/D) z tylko jedną" << std::endl;
        std::cout << "poprawną odpowiedzią. Powodzenia!" << std::endl;
        std::cout << "(Gdy będziesz gotów wpisz 'R' i kliknij enter" << std::endl;
        std::cout << ">";
        std::cin >> readyOrNot;

        for (int i = 0; i < 20; i++)
        {
            if (displayQuestionPanel(askedQuestions, i))
                points ++;
        }

        MiscUtils::clearScreen();
        std::cout << "Podsumowanie testu i ocena: " << std::endl;
        std::cout << "Nickname: " << username << std::endl;
        std::cout << "Ocena: [" << points << "/20]" << std::endl;
        std::cout << "Wpisz 'k' by kontynuować" << std::endl;
        std::cin >> readyOrNot;
        ScoreManagement::addScore(username, points);
    }

    ////////////////////////////////////////////////////////////
    bool displayQuestionPanel(int* askedQuestions, int currentId)
    {
        srand(time(NULL));
        MiscUtils::clearScreen();
        int randomNum = 0;
        auto* question = new QuestionManagement::QuestionEntry;
        char answer;

        // Losuj dopóki nie ma nowego pytania (unikanie duplikatów)
        while (true)
        {
            bool hasTheRandNum = false;
            randomNum = std::rand()%100+1;
            for (int i = 0; i < currentId; i++)
            {
                if (randomNum == askedQuestions[i])
                    hasTheRandNum = true;
            }

            if (!hasTheRandNum)
                break;
        }
        askedQuestions[currentId] = randomNum;

        QuestionManagement::getQuestionById(question, randomNum);
        std::cout << question->question_id << ". " << question->question << std::endl;
        std::cout << "A. " << question->answerA << std::endl;
        std::cout << "B. " << question->answerB << std::endl;
        std::cout << "C. " << question->answerC << std::endl;
        std::cout << "D. " << question->answerD << std::endl;
        std::cout << ">";
        std::cin >> answer;

        int someCharval = tolower(answer) - 97;
        int blabla = (int)question->correctAnswer;
        bool some_value =  someCharval == blabla;
        return some_value;
    }

    ////////////////////////////////////////////////////////////
    void printAllQuestions()
    {
        std::cout << "\r\n\r\n\r\n" << std::endl;
        auto *question = new QuestionManagement::QuestionEntry;
        // TODO: Finish this function
        for (int i = 1; ; i++)
        {
            if (QuestionManagement::getQuestionById(question, i))
            {
                std::cout << "ID: " << question->question_id << "\r\nPytanie: " << question->question;
                std::cout << "\r\n\r\nOdpowiedź A: " << question->answerA << "\r\nOdpowiedź B: " << question->answerB;
                std::cout << "\r\nOdpowiedź C: " << question->answerC << "\r\nOdpowiedź D: " << question->answerD;
                std::cout << "\r\n\r\nPoprawna odpowiedź: " << question->correctAnswer << std::endl << std::endl;
            }
            else if (QuestionManagement::getQuestionById(question, i++))
                continue;
            else
                break;
        }
    }

    void printAllUsers()
    {
        std::cout << "\r\n\r\n\r\n" << std::endl;
        auto *user = new UserManagement::User;
        int i = 1;

        while (UserManagement::loadNthUsr(user, i))
        {
            std::cout << "Użytkownik: " << user->username << "; Grupa przywilejów: ";
            switch (user->group)
            {
                case UserManagement::PrivilageGroup::teacher :
                    std::cout << "nauczyciel";
                    break;
                case UserManagement::PrivilageGroup::student :
                    std::cout << "student";
                    break;
                case UserManagement::PrivilageGroup::unset :
                    std::cout << "unset";
                    break;
                default:
                    std::cout << "Nieprawidłowa grupa! Błąd programu!";
                    break;
            }
            std::cout << std::endl;
            i++;
        }
    }
}