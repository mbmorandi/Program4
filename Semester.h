#pragma once
#include "StudentRecord.h"
const int NUM_DIFF_WORK = 3;
const int MAX_STUDENTS = 500;
class Semester{
    private:
        StudentRecord students[MAX_STUDENTS];
        int numStudents;
        int numProg;
        int numTest;
        int numFin;
        int weighted[NUM_DIFF_WORK];
        bool finalGradeCalculated;
        bool progRecorded[MAX_PROG];
        bool testRecorded[MAX_TESTS];
        bool finalRecorded;

    public:
        //constructors
        Semester();
        
        //getters
        int getNumStu();
        int getNumProg();
        int getNumTest();
        int getNumFin();
        StudentRecord& getStudent(int index);
        bool getFinalGradeCalc();
        int getWeight(int index);
        bool isProgRecorded(int index);
        bool isTestRecorded(int index);
        bool isFinalRecorded();

        //setters
        void setNumStudents(int numStu);
        void setNumP(int numP);
        void setNumT(int numT);
        void setNumF(int numF);
        void setWeight(int a, int b, int c);
        void setFinalGradeCalc(bool tf);
        void setProgRecorded(int index);
        void setTestRecorded(int index);
        void setFinalRecorded(bool tf);

        //class methods
        void addStudent(std::string stuName, int stuNum);
        void sortStudentsAlpha();
        void sortStudentsNum();
        void printStudentData();
        void saveData(const std::string& fileName); //need imp
        bool loadData(const std::string& fileName); // need imp
        void printStudentData(std::ostream& out); //need imp
};
