cmake_minimum_required(VERSION 3.15)
project(p6 C)

set(CMAKE_C_STANDARD 99)

add_executable(p6 main.c mapreduce.c mapreduce.h)