#include "Menu.h"
#include <iostream>
#include <fstream>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;

Menu::Menu() :
    menuIsOpen{false},
    semesterOpen{false},
    setupThisRun{false},
    outFile{OUTPUT_FILE},
    trnFile{TRANSACTION_FILE}
{}

//class methods
// add one line to the Grades.trn transaction log
void Menu::writeTransaction(const std::string& message){
    trnFile << message << endl;
}

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
        cout << "Please enter the students ID number (1-9,999): ";
        cin >> studentNum;
        //checking if ID is available
        for(int i = 0; i < semester.getNumStu(); i++){
            if(semester.getStudent(i).getStuID() == studentNum){
                std::cout << "ID not available. exiting to the main menu." << std::endl;
                writeTransaction("A: rejected - ID " + to_string(studentNum) + " already in use");
                return;
            }
        }
        //checking input range. if in range, add student
        if(studentNum > 9999 || studentNum < 1){
            cout << "Invalid ID number. Exiting to main menu. " << endl;
            writeTransaction("A: rejected - invalid ID " + to_string(studentNum) + " for " + name);
        } else {
            semester.addStudent(name, studentNum);
            writeTransaction("A: added student " + name + ", ID " + to_string(studentNum));
        }
    //semester has not been setup yet. exit to the main screen.
    } else {
        cout << "Please set up the semester before you add students. Exiting to the main menu." << endl;
        writeTransaction("A: rejected - semester not set up or grade book full");
    }
}
void Menu::recordStudentProgramGrades(){
    if(!semesterOpen){
        cout << "Please setup a new semester before recording program grades. Exiting to the main menu" << endl;
        writeTransaction("P: rejected - semester not set up");
        return;
    } else {
        if(semester.getNumProg() == 0){
            cout << "There are no programs assigned to this semester. Exiting to the main menu." << endl;
            writeTransaction("P: rejected - no programs this semester");
            return;
        } else {
            int test;
            int grade;

            //getting program number from user
            cout << "Please enter the programming assignment number you would like to record (1 - " << semester.getNumProg() << "): ";
            cin >> test;
            if(test > semester.getNumProg() || test < 1){
                std::cout << "You entered an invalid number. Exiting to the main screen." << std::endl;
                writeTransaction("P: rejected - invalid program number " + to_string(test));
                return;
            }
            //keeping track of tests entered into the program
            if(!semester.isProgRecorded(test - 1)){
                semester.setProgRecorded(test - 1);
            } else {
                cout << "Program number " << test << " has already been recorded. Exiting to the main screen." << endl;
                writeTransaction("P: rejected - program " + to_string(test) + " already recorded");
                return;
            }
            writeTransaction("P: recorded program " + to_string(test) + " grades");
            //printing out students and asking for new student grade
            for(int i = 0; i < semester.getNumStu(); i++){
                std::cout << "Please enter a grade for student " << semester.getStudent(i).getName() << ": ";
                cin >> grade;
                if(grade <= 100 && grade >= 0){
                    semester.getStudent(i).setProgGrade(test-1, grade);
                    writeTransaction("   " + semester.getStudent(i).getName() + ": " + to_string(grade));
                } else {
                    writeTransaction("   " + semester.getStudent(i).getName() + ": invalid grade " + to_string(grade) + ", not recorded");
                }
            }
        }
    }
        

}
void Menu::recordStudentTestGrades(){
    if(!semesterOpen){
        cout << "Please setup a new semester before recording test grades. Exiting to the main menu..." << endl;
        writeTransaction("T: rejected - semester not set up");
        return;
    } else {
        if(semester.getNumTest() == 0){
            cout << "There are no tests assigned to this semester. Exiting to the main menu." << endl;
            writeTransaction("T: rejected - no tests this semester");
            return;
        } else {
            int test;
            int grade;

            //getting program number from user
            cout << "Please enter the test number you would like to record (1 - " << semester.getNumTest() << "): ";
            cin >> test;
            if(test > semester.getNumTest() || test < 1){
                std::cout << "You entered an invalid number. Exiting to the main screen." << std::endl;
                writeTransaction("T: rejected - invalid test number " + to_string(test));
                return;
            }
            //keeping track of tests entered into the program
            if(!semester.isTestRecorded(test - 1)){
                semester.setTestRecorded(test - 1);
            } else {
                cout << "Test number " << test << " has already been recorded. Exiting to the main screen." << endl;
                writeTransaction("T: rejected - test " + to_string(test) + " already recorded");
                return;
            }
            writeTransaction("T: recorded test " + to_string(test) + " grades");
            //printing out students and asking for new student grade
            for(int i = 0; i < semester.getNumStu(); i++){
                std::cout << "Please enter a grade for student " << semester.getStudent(i).getName() << ": ";
                cin >> grade;
                if(grade <= 100 && grade >= 0){
                    semester.getStudent(i).setTestGrade(test - 1, grade);
                    writeTransaction("   " + semester.getStudent(i).getName() + ": " + to_string(grade));
                } else {
                    writeTransaction("   " + semester.getStudent(i).getName() + ": invalid grade " + to_string(grade) + ", not recorded");
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
            writeTransaction("F: rejected - no final exam this semester");
            return;
        } else {
            if(!semester.isFinalRecorded()){
            writeTransaction("F: recorded final exam grades");
            for(int i = 0; i < semester.getNumStu(); i++){
                std::cout << "Please enter a grade for student " << semester.getStudent(i).getName() << ": ";
                cin >> grade;
                if(grade <= 100 && grade >= 0){
                    semester.getStudent(i).setFinExGrade(grade);
                    writeTransaction("   " + semester.getStudent(i).getName() + ": " + to_string(grade));
                } else {
                    writeTransaction("   " + semester.getStudent(i).getName() + ": invalid grade " + to_string(grade) + ", not recorded");
                }
            }
            semester.setFinalRecorded(true);
            } else {
                cout << "Final Exams have already been graded. Exiting to the main menu." << endl;
                writeTransaction("F: rejected - final exam already recorded");
                return;
            }
        }
    } else {
        cout << "Please create a semester before you record final exam grades. Exiting to the main menu." << endl;
        writeTransaction("F: rejected - semester not set up");
        return;
    }

}
void Menu::changeGrade(){
    bool studentFound;
    if(!semesterOpen){
        //semester not setup
        cout << "Please setup a new semester before changing student grades. Exiting to the main menu." << endl;
        writeTransaction("C: rejected - semester not set up");
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
                cout << "[P] = Program \t[T] = Test\t[F] = Final: ";
                
                char userInput;
                cin >> userInput;
                //check user choice
                if(toupper(userInput) == 'T'){
                    //check if there are tests assigned to the semester
                    if(semester.getNumTest() == 0){
                        cout << "There are no tests assigned to this semester. Exiting to main menu." << endl;
                        writeTransaction("C: rejected - no tests this semester");
                        return;
                    } else {
                    //there are tests assigned
                    cout << "What test number would you like to change? Enter a value between (1 - " << semester.getNumTest() << "): ";
                    int testToChange;
                    cin >> testToChange;
                    if(testToChange > semester.getNumTest() || testToChange < 1){
                        //invalid test number
                        cout << "You entered an invalid test number. Exiting to the main menu." << endl;
                        writeTransaction("C: rejected - invalid test number " + to_string(testToChange));
                        return;
                    } else {
                        //valid test number. prompt user for grade
                        cout << "What Grade would you like to assign to test number " << testToChange << ": ";
                        int grade;
                        cin >> grade;
                        if(grade > 100 || grade < 0){
                            cout << "Invalid test grade. Returning to main menu." << endl;
                            writeTransaction("C: rejected - invalid grade " + to_string(grade));
                            return;
                        } else {
                            int old = semester.getStudent(i).getTestGrade(testToChange - 1);
                            semester.getStudent(i).setTestGrade(testToChange - 1, grade);
                            writeTransaction("C: " + semester.getStudent(i).getName() + " (ID " + to_string(studentID) + ") test "
                                             + to_string(testToChange) + " changed from " + to_string(old) + " to " + to_string(grade));
                        }
                        
                    }
                }

                } else if (toupper(userInput) == 'P'){
                    if(semester.getNumProg() == 0){
                        cout << "There are no program assignents for the semester. Exiting to main menu." << endl;
                        writeTransaction("C: rejected - no programs this semester");
                        return;
                    } else {
                        cout << "What program number would you like to change? Enter a value between (1 - " << semester.getNumProg() << "): ";
                        int programToChange;
                        cin >> programToChange;
                        if(programToChange > semester.getNumProg() || programToChange < 1){
                            //invalid test number
                            cout << "You entered an invalid program number. Exiting to the main menu." << endl;
                            writeTransaction("C: rejected - invalid program number " + to_string(programToChange));
                            return;
                        } else {
                            //valid program number. prompt user for grade
                            cout << "What Grade would you like to assign to program number " << programToChange << ": ";
                            int pGrade;
                            cin >> pGrade;
                            if(pGrade > 100 || pGrade < 0){
                                cout << "Invalid program grade. Returning to main menu." << endl;
                                writeTransaction("C: rejected - invalid grade " + to_string(pGrade));
                                return;
                            } else {
                                int old = semester.getStudent(i).getProgGrade(programToChange - 1);
                                semester.getStudent(i).setProgGrade(programToChange - 1, pGrade);
                                writeTransaction("C: " + semester.getStudent(i).getName() + " (ID " + to_string(studentID) + ") program "
                                                 + to_string(programToChange) + " changed from " + to_string(old) + " to " + to_string(pGrade));
                            }
                            
                        }
                    }

                } else if(toupper(userInput) == 'F'){
                    //check if there is a final
                    if(semester.getNumFin() == 0){
                        cout << "There is no final this semester. Exiting to the main menu." << endl;
                        writeTransaction("C: rejected - no final exam this semester");
                        return;
                    } else {
                        int final;
                        cout << "What Grade would you like to assign to the final exam: ";
                        cin >> final;
                        if(final > 100 || final < 0){
                            cout << "Invalid final exam grade. Exiting to the main menu" << endl;
                            writeTransaction("C: rejected - invalid grade " + to_string(final));
                            return;
                        } else {
                            int old = semester.getStudent(i).getFinalExGrade();
                            semester.getStudent(i).setFinExGrade(final);
                            writeTransaction("C: " + semester.getStudent(i).getName() + " (ID " + to_string(studentID)
                                             + ") final exam changed from " + to_string(old) + " to " + to_string(final));
                        }
                    }
                    
                } else {
                    cout << "You have entered an invalid option. Exiting to the main menu." << endl;
                    writeTransaction("C: rejected - invalid grade type");
                    return;
                }
        } else {
            //student not found
            studentFound = false;
        }
        if(!studentFound){
            cout << "No student found using ID number: " << studentID << endl;
            writeTransaction("C: rejected - no student with ID " + to_string(studentID));
        }
        }
    }
    
}
void Menu::calculateFinalGrade(){
    if(!semesterOpen){
        cout << "Please setup a new semester before you calculate final grades. Exiting to main menu." << endl;
        writeTransaction("G: rejected - semester not set up");
        return;
    } else {
        writeTransaction("G: calculated averages for " + to_string(semester.getNumStu()) + " students");
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
        cout << "How would you like to display student grade data? Enter A for Alphabetically or N for Numerically: ";
        cin >> order;
        string orderName;
        if(std::toupper(order) == 'A'){
            semester.sortStudentsAlpha();
            orderName = "alphabetical";
        } else if (std::toupper(order) == 'N'){
            semester.sortStudentsNum();
            orderName = "student number";
        } else {
            cout << "you entered an invalid option. Exiting to the main screen." << endl;
            writeTransaction("O: rejected - invalid sort order");
            return;
        }
        // print to the screen, and write the same data to Grades.out
        semester.printStudentData(cout);
        outFile << "===== Grade data (" << orderName << " order) =====" << endl;
        semester.printStudentData(outFile);
        cout << "Grade data written to " << OUTPUT_FILE << "." << endl;
        writeTransaction("O: wrote " + to_string(semester.getNumStu()) + " students to " + OUTPUT_FILE
                         + " in " + orderName + " order");
    } else {
        cout << "You must setup the semester before you can view grades. exiting to the main menu." << endl;
        writeTransaction("O: rejected - semester not set up");
        return;
    }

}
void Menu::setNewSemester(){
    //check if semester has already been opened
    if(!setupThisRun){
        // a new semester ignores anything loaded from Grades.dat and starts empty
        semester.reset();
        semesterOpen = false;
        int numTests;
        int numProg;
        int numFinal;
        cout << "Welcome. To begin setting up the new semester's gradebook, please answer the following questions." << endl;
        //prompting for number of programming assignments
        cout << "How many programming assignments will you assign this semester? (0-6): ";
        cin >> numProg;
        if(numProg > MAX_PROG || numProg < 0){
            cout << "You entered an invalid number. Please enter a value between 0 and 6. Returning to main menu" << endl;
            writeTransaction("S: rejected - invalid number of programs " + to_string(numProg));
            return;
        } else {
            cout << "You entered " << numProg << " programs for the semester. Recording data now..." << endl;
            semester.setNumP(numProg);
        }
        //prompting for number of tests
        cout << "How many tests will you assign this semester? (0-4): ";
        cin >> numTests;
        if(numTests> MAX_TESTS || numTests < 0){
            cout << "You entered an invalid number. Please enter a value between 0 and 4. Returning to main menu" << endl;
            writeTransaction("S: rejected - invalid number of tests " + to_string(numTests));
            return;
        } else {
            cout << "You entered " << numTests << " tests for the semester. Recording data now..." << endl;
            semester.setNumT(numTests);
        }

        //prompting the user for number of finals
        cout << "How many finals will you assign this semester? (0-1): ";
        cin >> numFinal;
        if(numFinal > 1 || numFinal < 0){
            cout << "You entered an invalid number. Please enter a value between 0 and 1. Returning to main menu" << endl;
            writeTransaction("S: rejected - invalid number of finals " + to_string(numFinal));
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
            cout << "What weight do you want to assign to programming assignments? (0 - " << maxWeight << "): ";
            cin >> val1;
            //checking if input is in range
            if(val1 > maxWeight || val1 < 0){
                cout << "You entered an invalid option. Exiting to the main menu..." << endl;
                writeTransaction("S: rejected - invalid program weight " + to_string(val1));
                return;
            } else {
                maxWeight -= val1;
            }
        } else {
            val1 = 0;
        }

        if(semester.getNumTest() > 0){
            cout << "What weight do you want to assign to the test assignemnts (0 - " << maxWeight << "): ";
            cin >> val2;
            if(val2 > maxWeight || val2 < 0){
                cout << "You entered an invalid option. Exiting to the main menu..." << endl;
                writeTransaction("S: rejected - invalid test weight " + to_string(val2));
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
            setupThisRun = true;
            writeTransaction("S: new semester - " + to_string(numProg) + " programs (" + to_string(val1) + "%), "
                             + to_string(numTests) + " tests (" + to_string(val2) + "%), "
                             + to_string(numFinal) + " final (" + to_string(val3) + "%)");
        } else {
            cout << "The weighted sum does not equal 100. Exiting to the main menu." << endl;
            writeTransaction("S: rejected - weights add up to " + to_string(val1 + val2 + val3) + ", not 100");
            return;
        }

        

    } else {
        cout << "Semester has already been setup. Returning to main menu." << endl;
        writeTransaction("S: rejected - semester already set up this run");
        return;
    }
    

    
}
void Menu::quit(){
    // save the grade book, if there is one to save
    if(semesterOpen){
        semester.saveData(DATA_FILE);
        cout << "Grade book saved to " << DATA_FILE << "." << endl;
        writeTransaction("Q: saved " + to_string(semester.getNumStu()) + " students to " + DATA_FILE);
    } else {
        writeTransaction("Q: no semester set up, nothing saved");
    }
    cout << "Exiting the program." << endl;
    menuIsOpen = false;
}
void Menu::printMenu(){
    cout << endl;
    cout << "\t\t------Grade Book Menu-----" << endl;
    cout << "S: setup new semester \t\t\tA: Add new student" << endl;
    cout << "P: record program assignment grades\tT: record test grades for students" << endl;
    cout << "F: record final exam grades\t\tC: Change student grade" << endl;
    cout << "G: calculate final grades\t\tO: output student grade data" << endl;
    cout << "Q: save and quit" << endl;
}
void Menu::openMenu(){
    // load the grade book saved by the last run, if exists
    writeTransaction("===== Grade Book transaction log =====");
    if(semester.loadData(DATA_FILE)){
        semesterOpen = true;
        cout << "Loaded " << semester.getNumStu() << " students from " << DATA_FILE << "." << endl;
        writeTransaction("Loaded " + to_string(semester.getNumStu()) + " students from " + DATA_FILE);
    } else {
        cout << "No saved grade book found. Use S to set up a new semester." << endl;
        writeTransaction("No saved grade book found in " + DATA_FILE);
    }

    menuIsOpen = true;
    char userChoice;
    while(menuIsOpen){
        printMenu();
        cout << "Please select an option or press Q to save and quit: ";
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

