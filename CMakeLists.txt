cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)

project(ForgeContainers VERSION 0.3.0 LANGUAGES CXX)

enable_testing()

add_subdirectory(Tests)