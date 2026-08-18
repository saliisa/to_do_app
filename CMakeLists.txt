cmake_minimum_required(VERSION 3.16)

project(TodoApp VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TodoApp
    src/main.cpp

    src/core/task.cpp
    src/core/taskManager.cpp
    src/core/validators.cpp

    src/database/database.cpp
    
    src/third_party/sqlite3.c
)