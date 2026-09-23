#include "Semester.h"
#include "Menu.h"
//constructors
Semester::Semester():
    numStudents{0},
    numProg{0},
    numTest{0},
    numFin{0},
    weighted{0},
    finalGradeCalculated{false}

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
//class methods
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
    for(int i = 0; i < numStudents; i++){
        //get student
        StudentRecord student = students[i];

        //print student name and ID
        student.printStudentInfo();
        
        //print student program grades
        if(numProg > 0){
            std::cout << "Student Program Grades: ";
            for(int j = 0; j < numProg; j++){
                std::cout << student.getProgGrade(j) << ", ";
            }
        }

        //print student test grades
        if(numTest > 0){
            std::cout << "\nStudent Test Grades: ";
            for(int j = 0; j < numTest; j++){
                std::cout << student.getTestGrade(j) << ", ";
            }  
        }
        //print student final exam grade
        if(numFin > 0){
            std::cout << "\nStudent Final Exam Grade: ";
            std::cout << student.getFinalExGrade() << std::endl;   
        }

        if(finalGradeCalculated){
            std::cout << "\nStudent Average Program Grade: ";
            std::cout << student.getProgAvg() << std::endl;

            std::cout << "Student Average Test Grade: ";
            std::cout << student.getTestAvg() << std::endl;

        }
        std::cout << std::endl;
        
    } 

}
