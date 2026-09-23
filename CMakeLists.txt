cmake_minimum_required(VERSION 3.10)
project(Program4 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Program4
    main.cpp
    Menu.cpp
    Semester.cpp
    StudentRecord.cpp
)

if(MSVC)
    target_compile_options(Program4 PRIVATE /W4)
else()
    target_compile_options(Program4 PRIVATE -Wall -Wextra)
endif()
