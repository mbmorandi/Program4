#include "StudentRecord.h"
using std::endl;
using std::cout;

//constructors

StudentRecord::StudentRecord() :
    name{""}, 
    student_ID{0}, 
    progGradeRec{}, 
    testGradeRec{}, 
    finalExGrade{0},
    progAvg{0},
    testAvg{0}
{}
StudentRecord::StudentRecord(std::string newName, int newID) : 
    name{newName}, 
    student_ID{newID}, 
    progGradeRec{}, 
    testGradeRec{}, 
    finalExGrade{0},
    progAvg{0},
    testAvg{0}
{}

//getters
std::string StudentRecord::getName(){
    return name;
}
int StudentRecord::getStuID(){
    return student_ID;
}
int StudentRecord::getProgGrade(int testNum){
    return progGradeRec[testNum];
}
int StudentRecord::getTestGrade(int testNum){
    return testGradeRec[testNum];
}
int StudentRecord::getFinalExGrade(){
    return finalExGrade;
}
int StudentRecord::getProgAvg(){
    return progAvg;
}
int StudentRecord::getTestAvg(){
    return testAvg;
}

//setters
void StudentRecord::setStuName(std::string newName){
    name = newName;
}
void StudentRecord::setStuID(int newID){
    student_ID = newID;
}
void StudentRecord::setFinExGrade(int newGrade){
    finalExGrade = newGrade;
}
void StudentRecord::setProgGrade(int testNum, int newGrade){
    progGradeRec[testNum] = newGrade;
}
void StudentRecord::setTestGrade(int testNum, int newGrade){
    testGradeRec[testNum] = newGrade;
}
void StudentRecord::setProgAvg(int avg){
    progAvg = avg;
}
void StudentRecord::setTestAvg(int avg){
    testAvg = avg;
}

//class methods
void StudentRecord::printStudentInfo(std::ostream& out){
    out << "Student Name: " << name << endl;
    out << "Student ID: " << student_ID << endl;
}
