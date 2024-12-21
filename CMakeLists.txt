cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)

project(forge_containers VERSION 0.4.0 LANGUAGES CXX)

include(FetchContent)

if(NOT TARGET forge_base)
	FetchContent_Declare(
		forge_base
		GIT_REPOSITORY https://github.com/FudgeRacoon/forge-base.git
		GIT_TAG        origin/master
	)
	FetchContent_MakeAvailable(forge_base)
endif()

if(NOT TARGET forge_memory)
	FetchContent_Declare(
		forge_memory
		GIT_REPOSITORY https://github.com/FudgeRacoon/forge-memory.git
		GIT_TAG        origin/master
	)
	FetchContent_MakeAvailable(forge_memory)
endif()

add_library(forge_containers INTERFACE)
target_link_libraries(forge_containers INTERFACE forge_base forge_memory)
target_include_directories(forge_containers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Source/Public)

enable_testing()

add_subdirectory(Tests)