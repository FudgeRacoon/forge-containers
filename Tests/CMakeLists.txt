set(BUILD_GMOCK OFF CACHE BOOL "Disable building of Google Mock" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of Google Test" FORCE)
set(gtest_build_tests OFF CACHE BOOL "Disable building of Google Test tests" FORCE)
set(gtest_build_samples OFF CACHE BOOL "Disable building of Google Test samples" FORCE)

include(FetchContent)

if(NOT TARGET googletest)
	FetchContent_Declare(
		googletest
		URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
	)
	FetchContent_MakeAvailable(googletest)
endif()

add_executable(tests main.cpp)
target_link_libraries(tests PRIVATE gtest forge_containers)

include(GoogleTest)
gtest_discover_tests(tests)