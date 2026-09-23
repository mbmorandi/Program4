#include "Semester.h"
#include "Menu.h"
#include <fstream>
//constructors
Semester::Semester():
    numStudents{0},
    numProg{0},
    numTest{0},
    numFin{0},
    weighted{0},
    finalGradeCalculated{false},
    progRecorded{},
    testRecorded{},
    finalRecorded{false}
{}

//getters
int Semester::getNumStu(){
    return numStudents;
}
int Semester::getNumProg(){
    return numProg;
}
int Semester::getNumTest(){
    return numTest;
}
int Semester::getNumFin(){
    return numFin;
}
StudentRecord& Semester::getStudent(int index){
    return students[index];
}
bool Semester::getFinalGradeCalc(){
    return finalGradeCalculated;
}
int Semester::getWeight(int index){
    return weighted[index];
}
bool Semester::isProgRecorded(int index){
    return progRecorded[index];
}
bool Semester::isTestRecorded(int index){
    return testRecorded[index];
}
bool Semester::isFinalRecorded(){
    return finalRecorded;
}
//setters
void Semester::setNumStudents(int numStu){
    numStudents = numStu;
}
void Semester::setNumP(int numP){
    numProg = numP;
}
void Semester::setNumT(int numT){
    numTest = numT;
}
void Semester::setNumF(int numF){
    numFin = numF;
}
void Semester::setWeight(int a, int b, int c){
    weighted[0] = a;
    weighted[1] = b;
    weighted[2] = c;
    
}
void Semester::setFinalGradeCalc(bool tf){
    finalGradeCalculated = tf;
}
void Semester::setProgRecorded(int index){
    progRecorded[index] = true;
}
void Semester::setTestRecorded(int index){
    testRecorded[index] = true;
}
void Semester::setFinalRecorded(bool tf){
    finalRecorded = tf;
}

//class methods
void Semester::reset(){
    numStudents = 0;
    numProg = 0;
    numTest = 0;
    numFin = 0;
    for(int i = 0; i < NUM_DIFF_WORK; i++){
        weighted[i] = 0;
    }
    finalGradeCalculated = false;
    for(int i = 0; i < MAX_PROG; i++){
        progRecorded[i] = false;
    }
    for(int i = 0; i < MAX_TESTS; i++){
        testRecorded[i] = false;
    }
    finalRecorded = false;
}

void Semester::addStudent(std::string stuName, int stuNum){
    //create new student
    StudentRecord newStudent(stuName, stuNum);

    //add student to students
    students[numStudents] = newStudent;
    numStudents++;

}

void Semester::sortStudentsAlpha(){
    StudentRecord temp;
    if(numStudents == 0 || numStudents == 1){
        return;
    } else {
        //simple bubblesort
        for(int i = 0; i < numStudents - 1; i++){
            for(int j = 0; j < numStudents - i - 1; j++){
                if(std::toupper(students[j].getName()[0]) > std::toupper(students[j+1].getName()[0])){
                    temp = students[j+1];
                    students[j+1] = students[j];
                    students[j] = temp;
            }
        }

        }
    }
}
void Semester::sortStudentsNum(){
    StudentRecord temp;
    if(numStudents == 0 || numStudents == 1){
        return;
    } else {
        for(int i = 0; i < numStudents - 1; i++){
            for(int j = 0; j < numStudents - i - 1; j++){
                if(students[j].getStuID() > students[j+1].getStuID()){
                    temp = students[j+1];
                    students[j+1] = students[j];
                    students[j] = temp;
                }
            }

        }
    }

}

void Semester::printStudentData(){
    printStudentData(std::cout);
}

// same printout, sent to any stream (the screen or a file)
void Semester::printStudentData(std::ostream& out){
    for(int i = 0; i < numStudents; i++){
        //get student
        StudentRecord student = students[i];

        //print student name and ID
        student.printStudentInfo(out);

        //print student program grades
        if(numProg > 0){
            out << "Student Program Grades: ";
            for(int j = 0; j < numProg; j++){
                out << student.getProgGrade(j) << ", ";
            }
        }

        //print student test grades
        if(numTest > 0){
            out << "\nStudent Test Grades: ";
            for(int j = 0; j < numTest; j++){
                out << student.getTestGrade(j) << ", ";
            }
        }
        //print student final exam grade
        if(numFin > 0){
            out << "\nStudent Final Exam Grade: ";
            out << student.getFinalExGrade() << std::endl;
        }

        if(finalGradeCalculated){
            out << "\nStudent Average Program Grade: ";
            out << student.getProgAvg() << std::endl;

            out << "Student Average Test Grade: ";
            out << student.getTestAvg() << std::endl;

        }
        out << std::endl;

    }

}

// write to Grades.dat 
void Semester::saveData(const std::string& fileName){
    std::ofstream out(fileName);
    if(!out){
        std::cout << "Could not open " << fileName << " for saving." << std::endl;
        return;
    }

    // semester settings
    out << numProg << " " << numTest << " " << numFin << std::endl;
    out << weighted[0] << " " << weighted[1] << " " << weighted[2] << std::endl;

    // recorded flags
    for(int i = 0; i < numProg; i++){
        out << progRecorded[i] << " ";
    }
    out << std::endl;
    for(int i = 0; i < numTest; i++){
        out << testRecorded[i] << " ";
    }
    out << std::endl;
    out << finalRecorded << std::endl;
    out << finalGradeCalculated << std::endl;

    // students
    out << numStudents << std::endl;
    for(int i = 0; i < numStudents; i++){
        StudentRecord& student = students[i];
        out << student.getName() << std::endl;
        out << student.getStuID();
        for(int j = 0; j < numProg; j++){
            out << " " << student.getProgGrade(j);
        }
        for(int j = 0; j < numTest; j++){
            out << " " << student.getTestGrade(j);
        }
        out << " " << student.getFinalExGrade();
        out << " " << student.getProgAvg();
        out << " " << student.getTestAvg() << std::endl;
    }
}

bool Semester::loadData(const std::string& fileName){
    std::ifstream in(fileName);
    if(!in){
        return false;
    }
    reset();

    // semester settings
    in >> numProg >> numTest >> numFin;
    in >> weighted[0] >> weighted[1] >> weighted[2];
    if(!in || numProg < 0 || numProg > MAX_PROG || numTest < 0 || numTest > MAX_TESTS
       || numFin < 0 || numFin > 1){
        reset();
        return false;
    }

    // recorded flags
    for(int i = 0; i < numProg; i++){
        in >> progRecorded[i];
    }
    for(int i = 0; i < numTest; i++){
        in >> testRecorded[i];
    }
    in >> finalRecorded >> finalGradeCalculated;

    // students
    int count;
    in >> count;
    if(!in || count < 0 || count > MAX_STUDENTS){
        reset();
        return false;
    }
    for(int i = 0; i < count; i++){
        std::string name;
        int id;
        int grade;
        // skip the line break left after the numbers, then read the whole name line
        in >> std::ws;
        std::getline(in, name);
        in >> id;
        StudentRecord student(name, id);
        for(int j = 0; j < numProg; j++){
            in >> grade;
            student.setProgGrade(j, grade);
        }
        for(int j = 0; j < numTest; j++){
            in >> grade;
            student.setTestGrade(j, grade);
        }
        in >> grade;
        student.setFinExGrade(grade);
        in >> grade;
        student.setProgAvg(grade);
        in >> grade;
        student.setTestAvg(grade);
        if(!in){
            reset();
            return false;
        }
        students[numStudents] = student;
        numStudents++;
    }
    return true;
}
