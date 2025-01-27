include(FetchContent)

set(BUILD_GMOCK OFF CACHE BOOL "Disable building of Google Mock")
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of Google Test")
set(gtest_build_tests OFF CACHE BOOL "Disable building of Google Test tests")
set(gtest_build_samples OFF CACHE BOOL "Disable building of Google Test samples")

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(Tests main.cpp)

target_link_libraries(Tests gtest)
target_include_directories(Tests PRIVATE ${CMAKE_SOURCE_DIR}/Source/Public)

include(GoogleTest)
gtest_discover_tests(Tests)