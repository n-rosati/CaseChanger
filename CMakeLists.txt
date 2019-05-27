cmake_minimum_required(VERSION 3.7.10)
project(CaseChanger C)

set(CMAKE_C_STANDARD 11)

add_executable(CaseChanger main.c utilities.c utilities.h)