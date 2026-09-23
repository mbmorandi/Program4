#pragma once
#include "Semester.h"
#include <string>
// #include "Semester.h"
class Menu{
    private:
        bool menuIsOpen;
        bool semesterOpen;
        Semester semester;
        int programsRecorded[MAX_PROG];
        int testsRecorded[MAX_TESTS];
        bool finalExamGraded;

    public:

        //constructor
        Menu();

        //getters
        int getProgRecord(int index);
        int getTestRecord(int index);
        bool finalIsGraded();
        
        //setters
        void recordProgram(int progNum);
        void recordTest(int testNum);
        void setFinalIsGraded(bool check);
        
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
