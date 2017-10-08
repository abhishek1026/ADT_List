cmake_minimum_required(VERSION 3.8)
project(COP3530_Project_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ADT_List.h PSLL.h SLL.h SDAL.h CDAL.h)
add_executable(COP3530_Project_1 ${SOURCE_FILES} main.cpp ADT_List.h SLL.h PSLL.h SDAL.h CDAL.h)