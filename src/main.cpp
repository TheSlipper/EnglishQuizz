#include "UserInterface/UserInterface.hpp"

// TODO: Delete those
#include "DataManagement/ManageData.hpp"

int main()
{
    UI::displayLoginScreen();

    // TODO: Anything below is to be deleted in the final version
//    DataManagement::purgeQuestions();

//    auto *entry = new DataManagement::QuestionEntry;

    // declaring entry values
//    std::string test = "This is a question!";
//    std::string odpA = "Answer A!";
//    std::string odpB = "Answer B!";
//    std::string odpC = "Answer C!";
//    std::string odpD = "Answer D!";

    // Modifying entry
//    entry->question_id = 1;
//    entry->correctAnswer = DataManagement::CorrectAnswer::answerA;
//    std::copy(test.begin(), test.end(), entry->question);
//    std::copy(odpA.begin(), test.end(), entry->answerA);
//    std::copy(odpB.begin(), test.end(), entry->answerB);
//    std::copy(odpC.begin(), test.end(), entry->answerC);
//    std::copy(odpD.begin(), test.end(), entry->answerD);

    // add those damn questions
//    DataManagement::addQuestion(entry);
//    entry->question_id++;
//    DataManagement::addQuestion(entry);

    // try deleting the seond one (the one with id 2)
//    DataManagement::deleteQuestionById(2);

    return 0;
}