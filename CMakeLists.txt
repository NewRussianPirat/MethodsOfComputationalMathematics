cmake_minimum_required(VERSION 3.26)
project(MethodsOfComputationalMathematics)

# GoogleTest требует как минимум C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем поддиректории с исходным кодом и тестами
add_subdirectory(src)
add_subdirectory(test)
