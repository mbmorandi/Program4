#pragma once
#include "Semester.h"
#include <string>

class Menu{
    private:
        bool menuIsOpen;
        bool semesterOpen;
        Semester semester;

    public:

        //constructor
        Menu();

        //class methods
        void addStudent();
        void recordStudentProgramGrades();
        void recordStudentTestGrades();
        void recordFinalExamGrade();
        void changeGrade();
        void calculateFinalGrade();
        void printGradeData();
        void quit();
        void printMenu();
        void openMenu();
        void setNewSemester();
        void writeTransaction(const std::string& message); //need to implement
               

};
