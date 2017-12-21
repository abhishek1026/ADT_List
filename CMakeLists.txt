cmake_minimum_required(VERSION 3.8)
project(COP3530_Project_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp List.h PSLL.h SSLL.h SDAL.h CDAL.h CBL.h)
add_executable(COP3530_Project_1 ${SOURCE_FILES} main.cpp List.h SSLL.h PSLL.h SDAL.h CDAL.h CBL.h)
