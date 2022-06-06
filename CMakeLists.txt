cmake_minimum_required(VERSION 3.21)
project(Blackjack)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Blackjack
        src/Card.cpp
        src/Card.h
        src/CardArray.cpp
        src/CardArray.h
        src/main.cpp)
