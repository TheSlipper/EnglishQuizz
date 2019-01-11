////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////
#define USER_DB_FILE_PATH "user_db.bin"
#define USER_TEMP_DB_FILE_PATH "user_db.temp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "../DEFINITIONS.hpp"

////////////////////////////////////////////////////////////
/// \brief UserManagement namespace to moduł zawierający
///         funkcje zarządzające bazą danych użytkowników oraz
///         logowaniem i wylogowywaniem użytkowników
///
////////////////////////////////////////////////////////////
namespace UserManagement
{

    enum PrivilageGroup {unset, teacher, student}; ///< enum zawierający wszystkie grupy przywilejów

    ////////////////////////////////////////////////////////////
    /// \brief Zawiera informacje na temat użytkownika
    ///
    /// \memberof char username[50] login użytkownika
    ///
    /// \memberof char password[50] hasło użytkownika
    ///
    /// \memberof PrivilageGroup group przypisana do użytkownika grupa przywilejowa
    ///
    ////////////////////////////////////////////////////////////
    struct User
    {
        char username[50];
        char password[50];
        PrivilageGroup group;
    };

    ////////////////////////////////////////////////////////////
    /// \brief Funkcja z inną implementacją dla systemów UNIXowych
    ///         i windowsowych. Zmienia nazwę pliku z USER_DB_TEMP na
    ///         USER_TEMP_DB_FILE_PATH.
    ///
    ////////////////////////////////////////////////////////////
    void makeTempMainDb();

    ////////////////////////////////////////////////////////////
    /// \brief Sprawdza czy podane dane do logowania są poprawne i je
    ///         załadowuje do podanego structa
    ///
    /// \param std::string username wprowadzony login użytkownika
    ///
    /// \param std::string password wprowadzone hasło użytkownika
    ///
    /// \param User* user dane o użytkowniku
    ///
    /// \returns bool zwraca true jeżeli użytkownik został pomyślnie zalogowany
    ///
    ////////////////////////////////////////////////////////////
    bool logIn(std::string username, std::string password, User *user);

    ////////////////////////////////////////////////////////////
    /// \brief Wylogowuje użytkownika i wyczyszcza dane logowania po
    ///         poprzedniej sesji
    ///
    /// \param User* user dane po poprzedniej sesji
    ///
    ////////////////////////////////////////////////////////////
    void logOut(User *user);

    ////////////////////////////////////////////////////////////
    /// \brief Wylogowuje użytkownika i wyczyszcza dane logowania po
    ///
    /// \param std::string username username użytkownika
    ///
    /// \param std::string password hasło użytkownika
    ///
    /// \return bool jeżeli podane dane są poprawne to zwraca true
    ///
    ////////////////////////////////////////////////////////////
    bool changePasswd(std::string username, std::string password);

    ////////////////////////////////////////////////////////////
    /// \brief Przepisuje wszystkich użytkowników i zwraca wskaźnik do pliku
    ///
    /// \return FILE* wskaźnik do pliku
    ///
    ////////////////////////////////////////////////////////////
    FILE* reWriteUsers();

    ////////////////////////////////////////////////////////////
    /// \brief Dodaje nowego użytkownika
    ///
    /// \param std::string username nickname nowego użytkownika
    ///
    /// \param std::string password hasło nowego użytkownika
    ///
    /// \param PrivilageGroup group grupa przywilejów użytkownika
    ///
    /// \return zwraca true jeżeli operacja dodawania się powiedzie
    ///
    ////////////////////////////////////////////////////////////
    bool addUser(std::string username, std::string password, PrivilageGroup group);

    ////////////////////////////////////////////////////////////
    /// \brief Usuwa użytkownika
    ///
    /// \param std::string username nickname użytkownika
    ///
    /// \return zwraca true jeżeli operacja usuwania użytkownika się powiedzie
    ///
    ////////////////////////////////////////////////////////////
    bool removeUser(std::string username);

    ////////////////////////////////////////////////////////////
    /// \brief Usuwa wszystkich użytkowników
    ///
    /// \return zwraca true jeżeli pomyślnie usunie bazę danych użytkowników
    ///
    ////////////////////////////////////////////////////////////
    bool purgeUserDB();
}