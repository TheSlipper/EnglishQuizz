////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "../UserManagement/UserManagement.hpp"
#include "../MiscellaneousUtilities/MiscUtils.hpp"
#include "../QuestionManagement/ManageQuestions.hpp"

////////////////////////////////////////////////////////////
/// \brief UI namespace to moduł zawierający funkcje interfejsu
///          użytkownika.
///
////////////////////////////////////////////////////////////
namespace UI
{
    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla błąd gdy użytkownik wybierze złą opcję
    ///
    ////////////////////////////////////////////////////////////
    void incorrectOptionEntered();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla główne menu użytkownika
    ///
    /// \param UserManagement::User* user Informacje nt. użytkownika
    ///
    ////////////////////////////////////////////////////////////
    void displayMainMenu(UserManagement::User *user);

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla dodatkowe opcje w menu dostępne tylko
    ///         dla administratorów
    ///
    ////////////////////////////////////////////////////////////
    void displayAdminOptions();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla panel zarządzania pytaniami
    ///
    ////////////////////////////////////////////////////////////
    void displayQuestionMgmtPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla panel dodawania pytania
    ///
    ////////////////////////////////////////////////////////////
    void addQuestionPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla panel edytowania pytania
    ///
    ////////////////////////////////////////////////////////////
    void editQuestionPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla panel usuwania pytania
    ///
    ////////////////////////////////////////////////////////////
    void deleteQuestionPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla panel importowania bazy danych z wskazanego
    ///         pliku
    ///
    ////////////////////////////////////////////////////////////
    void displayExportDBPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla panel eksportowania bazy danych do wskazanej
    ///         ścieżki
    ///
    ////////////////////////////////////////////////////////////
    void displayImportDBPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla panel zarządzania użytkownikami
    ///
    ////////////////////////////////////////////////////////////
    void displayUsrMgmtPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla oceny wszystkich uczniów
    ///
    ////////////////////////////////////////////////////////////
    void displayAllScores();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla oceny zalogowanego użytkownika
    ///
    /// \param UserManagement::User* user Informacje nt. użytkownika
    ///
    ////////////////////////////////////////////////////////////
    void displayScores(UserManagement::User *user);

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla panel do wpisania imienia oraz
    ///         nazwiska użytkownika
    ///
    ////////////////////////////////////////////////////////////
    void displayScoresPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla ustawienia programu (ustawienia są globalne)
    ///
    ////////////////////////////////////////////////////////////
    void displaySettingsPanel(UserManagement::User *user);

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla ekran logowania
    ///
    ////////////////////////////////////////////////////////////
    void displayLoginScreen();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla ekran dodawania nowego użytkownika
    ///
    ////////////////////////////////////////////////////////////
    void displayAddUserPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla ekran edytowania hasła użytkownika
    ///
    ////////////////////////////////////////////////////////////
    void displayEditPasswordPanel(UserManagement::User *user);

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla ekran usuwania użytkownika (część panelu
    ///         administracyjnego)
    ///
    ////////////////////////////////////////////////////////////
    void displayDeleteUserPanel();

    ////////////////////////////////////////////////////////////
    /// \brief Wyświetla ekran usuwania zalogowanego użytkownika
    ///         (część panelu studenta)
    ///
    ////////////////////////////////////////////////////////////
    void displayDeleteCurrentUser();

    ////////////////////////////////////////////////////////////
    /// \brief Wypisuje na ekran wszystkie pytania
    ///
    ////////////////////////////////////////////////////////////
    void printAllQuestions();

    ////////////////////////////////////////////////////////////
    /// \brief Wypisuje na ekran wszystkich użytkowników
    ///
    ////////////////////////////////////////////////////////////
    void printAllUsers();
}
