cmake_minimum_required(VERSION 3.10)
project(FinanceTracker)

set(CMAKE_CXX_STANDARD 17)

add_executable(FinanceTracker
    src/main.cpp
    src/Transaction.cpp
    src/TransactionManager.cpp
    src/FileManager.cpp
)

target_include_directories(FinanceTracker PRIVATE src)
