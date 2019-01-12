cmake_minimum_required(VERSION 3.12)
project(English_Quizz)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES
        "src/*.cpp"
        "src/QuestionManagement/*.cpp"
        "src/MiscellaneousUtilities/*.cpp"
        "src/UserInterface/*.cpp"
        "src/UserManagement/*.cpp"
        "src/ScoreManagement/*.cpp")

include_directories("src")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})