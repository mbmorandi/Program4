#pragma once
#include <string>
#include <iostream>

const int MAX_TESTS = 4;
const int MAX_PROG = 6;

class StudentRecord{
    private:
        std::string name;
        int student_ID;
        int progGradeRec[MAX_PROG];
        int testGradeRec[MAX_TESTS];
        int finalExGrade;
        int progAvg;
        int testAvg;
    public:
        //constructors
        StudentRecord();
        StudentRecord(std::string newName, int newID);

        //getters
        std::string getName();
        int getStuID();
        int getProgGrade(int testNum);
        int getTestGrade(int testNum);
        int getFinalExGrade();
        int getProgAvg();
        int getTestAvg();

        //setters
        void setStuName(std::string newName);
        void setStuID(int newID);
        void setFinExGrade(int newGrade);
        void setProgGrade(int testNum, int newGrade);
        void setTestGrade(int testNum, int newGrade);
        void setProgAvg(int avg);
        void setTestAvg(int avg);

        //class methods
        void printStudentInfo();
};
