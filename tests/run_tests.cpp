// Test driver for the grade book program.
//
// Runs the grade book once per file in tests/inputs (in name order). The driver
// is linked with Menu, Semester and StudentRecord, and for each run it points cin
// at the input file and cout at screen.txt, so the menu reads the file as if it
// were typed. All runs share one working folder, so the Grades.dat saved by one
// run is loaded by the next, like running the program several times by hand.
// After each run, Grades.dat, Grades.out, Grades.trn and screen.txt are copied to
// test_runs/<run name>/, since the program rewrites them every run.
//
// Each run's Grades files are then compared with the known-good copies in
// tests/expected/<run name>/, and the run passes if they match. After checking a
// deliberate change by hand, run with --update to save the new output as expected.
//
// Every input file must end with Q: the menu does not stop at end of input, so a
// missing Q makes the driver hang.
//
// usage: run_tests [--update]
#include "Menu.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// PROJECT_ROOT is set by CMakeLists.txt to the Program4 folder
const fs::path ROOT = PROJECT_ROOT;
const fs::path INPUTS = ROOT / "tests" / "inputs";
const fs::path EXPECTED = ROOT / "tests" / "expected";
const fs::path OUT = ROOT / "test_runs";
const fs::path WORK = OUT / "work";
const std::vector<std::string> SAVED_FILES = {"Grades.dat", "Grades.out", "Grades.trn", "screen.txt"};
const std::vector<std::string> CHECKED_FILES = {"Grades.dat", "Grades.out", "Grades.trn"};

// run the grade book once, reading input from inputFile, inside the WORK folder
void runGradeBook(const fs::path& inputFile){
    std::ifstream in(inputFile);
    std::ofstream screen(WORK / "screen.txt");
    std::streambuf* realCin = std::cin.rdbuf(in.rdbuf());
    std::streambuf* realCout = std::cout.rdbuf(screen.rdbuf());
    fs::path realFolder = fs::current_path();
    fs::current_path(WORK);  // Menu opens the Grades files in the current folder
    {
        Menu menu;
        menu.openMenu();
    }  // menu is destroyed here, which closes and saves Grades.out and Grades.trn
    fs::current_path(realFolder);
    std::cout.rdbuf(realCout);
    std::cin.rdbuf(realCin);
    std::cin.clear();  // the run may have left cin at end of file
}

// read a file's lines, or return false if the file doesn't exist
bool readLines(const fs::path& path, std::vector<std::string>& lines){
    std::ifstream in(path);
    if(!in){
        return false;
    }
    std::string line;
    while(std::getline(in, line)){
        // ignore Windows line endings, so files compare equal on any system
        if(!line.empty() && line.back() == '\r'){
            line.pop_back();
        }
        lines.push_back(line);
    }
    return true;
}

// compare one run's files with the expected copies; returns the problems found
std::vector<std::string> compareRun(const std::string& name){
    std::vector<std::string> problems;
    for(const std::string& fileName : CHECKED_FILES){
        std::vector<std::string> expected;
        std::vector<std::string> actual;
        bool haveExpected = readLines(EXPECTED / name / fileName, expected);
        bool haveActual = readLines(OUT / name / fileName, actual);
        if(!haveExpected || !haveActual){
            if(haveExpected != haveActual){
                problems.push_back(fileName + (haveExpected ? ": not written" : ": no expected copy"));
            }
            continue;
        }
        // report the first line that differs
        size_t lineCount = std::max(expected.size(), actual.size());
        for(size_t i = 0; i < lineCount; i++){
            std::string want = i < expected.size() ? expected[i] : "(end of file)";
            std::string got = i < actual.size() ? actual[i] : "(end of file)";
            if(want != got){
                problems.push_back(fileName + " line " + std::to_string(i + 1) + ":\n    expected: "
                                   + want + "\n    got:      " + got);
                break;
            }
        }
    }
    return problems;
}

int main(int argc, char* argv[]){
    bool update = argc > 1 && std::string(argv[1]) == "--update";

    // start from a clean folder, with no Grades.dat from earlier test runs.
    // Windows (or Google Drive syncing) can keep an empty folder locked, so
    // leftover empty folders are reused rather than treated as an error.
    std::error_code ignored;
    fs::remove_all(OUT, ignored);
    fs::create_directories(WORK);

    std::vector<fs::path> inputs;
    for(const fs::directory_entry& entry : fs::directory_iterator(INPUTS)){
        if(entry.path().extension() == ".txt"){
            inputs.push_back(entry.path());
        }
    }
    std::sort(inputs.begin(), inputs.end());

    bool allPassed = true;
    for(const fs::path& input : inputs){
        std::string name = input.stem().string();
        runGradeBook(input);

        // keep a copy of this run's files before the next run rewrites them
        fs::path runFolder = OUT / name;
        fs::create_directories(runFolder);
        for(const std::string& fileName : SAVED_FILES){
            if(fs::exists(WORK / fileName)){
                fs::copy_file(WORK / fileName, runFolder / fileName, fs::copy_options::overwrite_existing);
            }
        }

        std::string label = name + std::string(name.size() < 28 ? 28 - name.size() : 1, ' ');
        if(update){
            fs::create_directories(EXPECTED / name);
            for(const std::string& fileName : CHECKED_FILES){
                if(fs::exists(runFolder / fileName)){
                    fs::copy_file(runFolder / fileName, EXPECTED / name / fileName,
                                  fs::copy_options::overwrite_existing);
                }
            }
            std::cout << label << "expected output updated" << std::endl;
            continue;
        }

        std::vector<std::string> problems = compareRun(name);
        std::cout << label << (problems.empty() ? "PASS" : "FAIL") << std::endl;
        for(const std::string& problem : problems){
            std::cout << "  " << problem << std::endl;
        }
        if(!problems.empty()){
            allPassed = false;
        }
    }

    fs::remove(WORK / "screen.txt", ignored);
    std::cout << "Output files for each run are in test_runs/." << std::endl;
    return allPassed ? 0 : 1;
}
