#pragma once
#include "Semester.h"
#include <string>

const std::string DATA_FILE = "Grades.dat";

class Menu{
    private:
        bool menuIsOpen;
        bool semesterOpen;
        bool setupThisRun; // S already used in this run of the program
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
