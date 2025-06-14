cmake_minimum_required(VERSION 3.29)
project(Task3)

set(CMAKE_CXX_STANDARD 26)

include_directories(include)

add_executable(skipList
        src/gameManager.h
        include/skipList.h
        src/SkipListMain.cpp
        lib/skipList.cpp)
add_executable(gameManagerMain src/GameManagerMain.cpp
src/GameManager.cpp
lib/skipList.cpp)