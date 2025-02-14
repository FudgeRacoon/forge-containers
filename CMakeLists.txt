cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)

project(forge_containers VERSION 0.3.0 LANGUAGES CXX)

include(FetchContent)

set(FETCHCONTENT_SOURCE_DIR_forge_base "${CMAKE_SOURCE_DIR}/../forge-base")
set(FETCHCONTENT_BINARY_DIR_forge_base "${CMAKE_SOURCE_DIR}/../forge-base/build")

FetchContent_Declare(
	forge_base
	GIT_REPOSITORY https://github.com/FudgeRacoon/forge-base.git
	GIT_TAG        origin/master
)

set(FETCHCONTENT_SOURCE_DIR_forge_memory "${CMAKE_SOURCE_DIR}/../forge-memory")
set(FETCHCONTENT_BINARY_DIR_forge_memory "${CMAKE_SOURCE_DIR}/../forge-memory/build")

FetchContent_Declare(
	forge_memory
	GIT_REPOSITORY https://github.com/FudgeRacoon/forge-memory.git
	GIT_TAG        origin/master
)

FetchContent_MakeAvailable(forge_base)
FetchContent_MakeAvailable(forge_memory)

add_library(forge_containers INTERFACE)
target_link_libraries(forge_containers INTERFACE forge_base forge_memory)
target_include_directories(forge_containers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Source/Public)

enable_testing()

add_subdirectory(Tests)