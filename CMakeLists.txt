cmake_minimum_required(VERSION 3.23)
project(MyForwardList)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyForwardList
        MyForwardList.h
        main.cpp Core.h Node.h Iterator.h)
