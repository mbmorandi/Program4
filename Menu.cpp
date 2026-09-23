#include "Menu.h"
#include <iostream>
#include <fstream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

Menu::Menu() : 
    menuIsOpen{false},
    semesterOpen{false}
{}

//class methods
void Menu::addStudent(){
    if(semesterOpen && semester.getNumStu() != MAX_STUDENTS - 1){
        //temp variables
        std::string name;
        int studentNum;
        //prompting the user
        cin.clear();
        cin.ignore();
        cout << "Please enter the students name (last, first): ";
        std::getline(cin, name);
        cout << "Please enter the students ID number (1-9,999):  ";
        cin >> studentNum;
        //checking if ID is available
        for(int i = 0; i < semester.getNumStu(); i++){
            if(semester.getStudent(i).getStuID() == studentNum){
                std::cout << "ID not available. exiting to the main menu." << std::endl;
                return;
            }
        }
        //checking input range. if in range, add student
        if(studentNum > 9999 || studentNum < 1){
            cout << "Invalid ID number. Exiting to main menu. " << endl;
        } else {
            semester.addStudent(name, studentNum);
        }
    //semester has not been setup yet. exit to the main screen. 
    } else {
        cout << "Please set up the semester before you add students. Exiting to the main menu." << endl;
    }
}
void Menu::recordStudentProgramGrades(){
    if(!semesterOpen){
        cout << "Please setup a new semester before recording program grades. Exiting to the main menu" << endl;
        return;
    } else {
        if(semester.getNumProg() == 0){
            cout << "There are no programs assigned to this semester. Exiting to the main menu." << endl;
            return;
        } else {
            int test;
            int grade;

            //getting program number from user
            cout << "Please enter the programming assignment number you would like to record (1 - " << semester.getNumProg() << ")" << std::endl;
            cin >> test;
            if(test > semester.getNumProg() || test < 1){
                std::cout << "You entered an invalid number. Exiting to the main screen." << std::endl;
                return;
            }
            //keeping track of tests entered into the program
            if(!semester.isProgRecorded(test - 1)){
                semester.setProgRecorded(test - 1);
            } else {
                cout << "Program number " << test << " has already been recorded. Exiting to the main screen." << endl;
                return;
            }
            //printing out students and asking for new student grade
            for(int i = 0; i < semester.getNumStu(); i++){
                std::cout << "Please enter a grade for student: " << semester.getStudent(i).getName() << std::endl;
                cin >> grade;
                if(grade <= 100 && grade >= 0){
                    semester.getStudent(i).setProgGrade(test-1, grade);
                }
            }
        }
    }
        

}
void Menu::recordStudentTestGrades(){
    if(!semesterOpen){
        cout << "Please setup a new semester before recording test grades. Exiting to the main menu..." << endl;
        return;
    } else {
        if(semester.getNumTest() == 0){
            cout << "There are no tests assigned to this semester. Exiting to the main menu." << endl;
            return;
        } else {
            int test;
            int grade;

            //getting program number from user
            cout << "Please enter the test number you would like to record (1 - " << semester.getNumTest() << ")" << std::endl;
            cin >> test;
            if(test > semester.getNumTest() || test < 1){
                std::cout << "You entered an invalid number. Exiting to the main screen." << std::endl;
                return;
            }
            //keeping track of tests entered into the program
            if(!semester.isTestRecorded(test - 1)){
                semester.setTestRecorded(test - 1);
            } else {
                cout << "Test number " << test << " has already been recorded. Exiting to the main screen." << endl;
                return;
            }
            //printing out students and asking for new student grade
            for(int i = 0; i < semester.getNumStu(); i++){
                std::cout << "Please enter a grade for student: " << semester.getStudent(i).getName() << std::endl;
                cin >> grade;
                if(grade <= 100 && grade >= 0){
                    semester.getStudent(i).setTestGrade(test - 1, grade);
                }
            }
        }
    }
        
}
void Menu::recordFinalExamGrade(){
    int grade;
    if(semesterOpen){
        if(semester.getNumFin() == 0){
            cout << "There are no finals assigned to this semester. Exiting to the main menu." << endl;
            return;
        } else {
            if(!semester.isFinalRecorded()){
            for(int i = 0; i < semester.getNumStu(); i++){
                std::cout << "Please enter a grade for student: " << semester.getStudent(i).getName() << std::endl;
                cin >> grade;
                if(grade <= 100 && grade >= 0){
                    semester.getStudent(i).setFinExGrade(grade);
                }
            }
            semester.setFinalRecorded(true);
            } else {
                cout << "Final Exams have already been graded. Exiting to the main menu." << endl;
                return;
            }
        }
    } else {
        cout << "Please create a semester before you record final exam grades. Exiting to the main menu." << endl;
        return;
    }

}
void Menu::changeGrade(){
    bool studentFound;
    if(!semesterOpen){
        //semester not setup
        cout << "Please setup a new semester before changing student grades. Exiting to the main menu." << endl;
        return; 
    } else {
        //semester is setup
        int studentID;
        cout << "Please enter the students ID number: ";
        cin >> studentID;

        //find the student and prompt user for test number and grade
        for(int i = 0; i < semester.getNumStu(); i++){
            if(semester.getStudent(i).getStuID() == studentID){
                studentFound = true;
                //student is found
                cout << "Please enter the type of grade you would like to change." << endl;
                cout << "[P] = Program \t[T] = Test\t[F] = Final" << endl;
                
                char userInput;
                cin >> userInput;
                //check user choice
                if(toupper(userInput) == 'T'){
                    //check if there are tests assigned to the semester
                    if(semester.getNumTest() == 0){
                        cout << "There are no tests assigned to this semester. Exiting to main menu." << endl;
                        return;
                    } else {
                    //there are tests assigned
                    cout << "What test number would you like to change? Enter a value between (1 - " << semester.getNumTest() << ")";
                    int testToChange;
                    cin >> testToChange;
                    if(testToChange > semester.getNumTest() || testToChange < 1){
                        //invalid test number
                        cout << "You entered an invalid test number. Exiting to the main menu." << endl;
                        return;
                    } else {
                        //valid test number. prompt user for grade
                        cout << "What Grade would you like to assign to test number " << testToChange << ": ";
                        int grade;
                        cin >> grade;
                        if(grade > 100 || grade < 0){
                            cout << "Invalid test grade. Returning to main menu." << endl;
                            return;
                        } else {
                            semester.getStudent(i).setTestGrade(testToChange - 1, grade);
                        }
                        
                    }
                }

                } else if (toupper(userInput) == 'P'){
                    if(semester.getNumProg() == 0){
                        cout << "There are no program assignents for the semester. Exiting to main menu." << endl;
                        return;
                    } else {
                        cout << "What program number would you like to change? Enter a value between (1 - " << semester.getNumProg() << ")";
                        int programToChange;
                        cin >> programToChange;
                        if(programToChange > semester.getNumProg() || programToChange < 1){
                            //invalid test number
                            cout << "You entered an invalid program number. Exiting to the main menu." << endl;
                            return;
                        } else {
                            //valid program number. prompt user for grade
                            cout << "What Grade would you like to assign to program number " << programToChange << ": ";
                            int pGrade;
                            cin >> pGrade;
                            if(pGrade > 100 || pGrade < 0){
                                cout << "Invalid program grade. Returning to main menu." << endl;
                                return;
                            } else {
                                semester.getStudent(i).setProgGrade(programToChange - 1, pGrade);
                            }
                            
                        }
                    }

                } else if(toupper(userInput) == 'F'){
                    //check if there is a final
                    if(semester.getNumFin() == 0){
                        cout << "There is no final this semester. Exiting to the main menu." << endl;
                        return;
                    } else {
                        int final;
                        cout << "What Grade would you like to assign to the final exam: ";
                        cin >> final;
                        if(final > 100 || final < 0){
                            cout << "Invalid final exam grade. Exiting to the main menu" << endl;
                            return;
                        } else {
                            semester.getStudent(i).setFinExGrade(final);
                        }
                    }
                    
                } else {
                    cout << "You have entered an invalid option. Exiting to the main menu." << endl;
                    return;
                }
        } else {
            //student not found
            studentFound = false;
        }
        if(!studentFound){
            cout << "No student found using ID number: " << studentID << endl;
        }
        }
    }
    
}
void Menu::calculateFinalGrade(){
    if(!semesterOpen){
        cout << "Please setup a new semester before you calculate final grades. Exiting to main menu." << endl;
        return;
    } else {
        for(int i = 0; i < semester.getNumStu(); i++){
            //get student
            StudentRecord& student = semester.getStudent(i);
            //add values
            if(semester.getNumProg() > 0){
                double pAvg = 0;
                for(int j = 0; j < semester.getNumProg(); j++){
                    pAvg += student.getProgGrade(j);
                }
                student.setProgAvg(pAvg/semester.getNumProg());
            } else {
                //what to do when there are no programs to average
                return;
            }

            if(semester.getNumTest() > 0){
                double tAvg = 0;
                for(int j = 0; j < semester.getNumTest(); j++){
                    tAvg += student.getTestGrade(j);
                }
                student.setTestAvg(tAvg/semester.getNumTest());
            } else {
                //what to do when there are no tests to average
                return;
            }
            semester.setFinalGradeCalc(true);
        }
        
    }
}
void Menu::printGradeData(){

    if(semesterOpen){
        char order;
        cout << "How would you like to display student grade data? Enter A for Alphabetically or N for Numerically" << endl;
        cin >> order;
        if(std::toupper(order) == 'A'){
            semester.sortStudentsAlpha();
            semester.printStudentData();
        } else if (std::toupper(order) == 'N'){
            semester.sortStudentsNum();
            semester.printStudentData();
        } else {
            cout << "you entered an invalid option. Exiting to the main screen." << endl;
            return;
        }
    } else {
        cout << "You must setup the semester before you can view grades. exiting to the main menu." << endl;
        return;
    }

}
void Menu::setNewSemester(){
    //check if semester has already been opened
    if(!semesterOpen){
        int numTests;
        int numProg;
        int numFinal;
        cout << "Welcome. To begin setting up the new semester's gradebook, please answer the following questions." << endl;
        //prompting for number of programming assignments
        cout << "How many programming assignments will you assign this semester? (0-6)";
        cin >> numProg;
        if(numProg > MAX_PROG || numProg < 0){
            cout << "You entered an invalid number. Please enter a value between 0 and 6. Returning to main menu" << endl;
            return;
        } else {
            cout << "You entered " << numProg << " programs for the semester. Recording data now..." << endl;
            semester.setNumP(numProg);
        }
        //prompting for number of tests
        cout << "How many tests will you assign this semester? (0-4)";
        cin >> numTests;
        if(numTests> MAX_TESTS || numTests < 0){
            cout << "You entered an invalid number. Please enter a value between 0 and 4. Returning to main menu" << endl;
            return;
        } else {
            cout << "You entered " << numTests << " tests for the semester. Recording data now..." << endl;
            semester.setNumT(numTests);
        }

        //prompting the user for number of finals
        cout << "How many finals will you assign this semester? (0-1)";
        cin >> numFinal;
        if(numFinal > 1 || numFinal < 0){
            cout << "You entered an invalid number. Please enter a value between 0 and 1. Returning to main menu" << endl;
            return;
        } else {
            cout << "You entered " << numFinal << " finals for the semester. Recording data now..." << endl;
            semester.setNumF(numFinal);
        }

        //prompting user for weighted values
        int maxWeight = 100;
        int val1;
        int val2;
        int val3;
        cout << "We will now add the weighted values for your assignemnts, tests, and final." << endl;
        cout << "Your weighted values must have a sum of 100" << endl;
        if(semester.getNumProg() > 0){
            cout << "What weight do you want to assign to programming assignments? (0 - " << maxWeight << ") ";
            cin >> val1;
            //checking if input is in range
            if(val1 > maxWeight || val1 < 0){
                cout << "You entered an invalid option. Exiting to the main menu..." << endl;
                return;
            } else {
                maxWeight -= val1;
            }
        } else {
            val1 = 0;
        }

        if(semester.getNumTest() > 0){
            cout << "What weight do you want to assign to the test assignemnts (0 - " << maxWeight << ") ";
            cin >> val2;
            if(val2 > maxWeight || val2 < 0){
                cout << "You entered an invalid option. Exiting to the main menu..." << endl;
                return;
            } else {
                maxWeight -= val2;
            }
        } else {
            val2 = 0;
        }

        if(semester.getNumFin() > 0){
            cout << "Final will be assigned remaining weight of " << maxWeight << endl;
            val3 = maxWeight;
        } else {
            val3 = 0;
        } 

        if(val1+val2+val3 == 100){
            semester.setWeight(val1, val2, val3);
            semesterOpen = true;
        } else {
            cout << "The weighted sum does not equal 100. Exiting to the main menu." << endl;
            return;
        }

        

    } else {
        cout << "Semester has already been setup. Returning to main menu." << endl;
        return;
    }
    

    
}
void Menu::quit(){
    //FILE OUTPUT GOES HERE
    cout << "Exiting the program." << endl;
    menuIsOpen = false;
}
void Menu::printMenu(){
    cout << "\t\t------Grade Book Menu-----" << endl;
    cout << "S: setup new semester \t\t\tA: Add new student" << endl;
    cout << "P: record program assignment grades\tT: record test grades for students" << endl;
    cout << "F: record final exam grades\t\tC: Change student grade" << endl;
    cout << "G: calculate final grades\t\tO: output student grade data" << endl;
    cout << "Q: save and quit" << endl;
}
void Menu::openMenu(){
    menuIsOpen = true;
    char userChoice;
    while(menuIsOpen){
        printMenu();
        cout << "Please select an option or press Q to save and quit" << endl;
        cin >> userChoice;
        switch(std::toupper(userChoice)){
            case 'S':
                setNewSemester();
                break;
            case 'A':
                addStudent();
                break;
            case 'P':
                recordStudentProgramGrades();
                break;
            case 'T':
                recordStudentTestGrades();
                break;
            case 'F':
                recordFinalExamGrade();
                break;
            case 'C':
                changeGrade();
                break;
            case 'G':
                calculateFinalGrade();
                break;
            case 'O':
                printGradeData();
                break;
            case 'Q':
                quit();
                break;
        }
        

    }
    
}

