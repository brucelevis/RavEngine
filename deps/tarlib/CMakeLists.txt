cmake_minimum_required(VERSION 3.17)

project(tarlib)
add_library("${PROJECT_NAME}" "include/tarlib/tarball.hpp" "tarball.cpp")
target_include_directories("${PROJECT_NAME}" PUBLIC "include/tarlib/")