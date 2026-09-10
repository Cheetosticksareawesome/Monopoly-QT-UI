cmake_minimum_required(VERSION 3.16)

project(UIApp LANGUAGES CXX)

add_executable(UIApp Main/main.cpp)
target_compile_features(UIApp PRIVATE cxx_std_20)
