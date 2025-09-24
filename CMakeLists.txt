cmake_minimum_required(VERSION 3.25)
project(CCDesignPatter LANGUAGES CXX VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE "Debug")

message("============== Welcome CCDesignPatter Demos Configurations =========")

add_subdirectory(Builder)

message("============== CCDesignPatter Demos Configuration End =========")







