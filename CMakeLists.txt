cmake_minimum_required(VERSION 3.16)
project(CashierWorkplace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(${PROJECT_NAME}
    Main.cpp
    src/CashBox.cpp
    src/CashierWorkplace.cpp
    src/Cheque.cpp
    src/ProductDatabase.cpp
    src/Shift.cpp
)